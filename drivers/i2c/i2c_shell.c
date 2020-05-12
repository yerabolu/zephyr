/*
 * Copyright (c) 2018 Prevas A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <shell/shell.h>
#include <stdlib.h>
#include <drivers/i2c.h>
#include <string.h>
#include <sys/util.h>
#include <stdlib.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(i2c_shell, CONFIG_LOG_DEFAULT_LEVEL);

#define I2C_DEVICE_PREFIX "I2C_"

extern struct device __device_start[];
extern struct device __device_end[];

/* Maximum bytes we can write or read at once */
#define MAX_I2C_BYTES	16

static int cmd_i2c_scan(const struct shell *shell,
			size_t argc, char **argv)
{
	struct device *dev;
	u8_t cnt = 0, first = 0x04, last = 0x77;

	dev = device_get_binding(argv[1]);

	if (!dev) {
		shell_error(shell, "I2C: Device driver %s not found.",
			    argv[1]);
		return -ENODEV;
	}

	shell_print(shell,
		    "     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
	for (u8_t i = 0; i <= last; i += 16) {
		shell_fprintf(shell, SHELL_NORMAL, "%02x: ", i);
		for (u8_t j = 0; j < 16; j++) {
			if (i + j < first || i + j > last) {
				shell_fprintf(shell, SHELL_NORMAL, "   ");
				continue;
			}

			struct i2c_msg msgs[1];
			u8_t dst;

			/* Send the address to read from */
			msgs[0].buf = &dst;
			msgs[0].len = 0U;
			msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;
			if (i2c_transfer(dev, &msgs[0], 1, i + j) == 0) {
				shell_fprintf(shell, SHELL_NORMAL,
					      "%02x ", i + j);
				++cnt;
			} else {
				shell_fprintf(shell, SHELL_NORMAL, "-- ");
			}
		}
		shell_print(shell, "");
	}

	shell_print(shell, "%u devices found on %s",
		    cnt, argv[1]);

	return 0;
}

static int cmd_i2c_recover(const struct shell *shell,
			   size_t argc, char **argv)
{
	struct device *dev;
	int err;

	dev = device_get_binding(argv[1]);
	if (!dev) {
		shell_error(shell, "I2C: Device driver %s not found.", argv[1]);
		return -ENODEV;
	}

	err = i2c_recover_bus(dev);
	if (err) {
		shell_error(shell, "I2C: Bus recovery failed (err %d)", err);
		return err;
	}

	return 0;
}

/* i2c write <device> <dev_addr> [<byte1>, ...] */
static int cmd_i2c_write(const struct shell *shell, size_t argc, char **argv)
{
	u8_t buf[MAX_I2C_BYTES];
	struct device *dev;
	int num_bytes;
	int reg_addr;
	int dev_addr;
	int i;

	dev = device_get_binding(argv[1]);
	if (!dev) {
		shell_error(shell, "I2C: Device driver %s not found.", argv[1]);
		return -ENODEV;
	}

	dev_addr = strtol(argv[2], NULL, 16);
	reg_addr = strtol(argv[3], NULL, 16);
	num_bytes = argc - 4;
	if (num_bytes < 0) {
		return 0;
	}
	if (num_bytes > MAX_I2C_BYTES) {
		num_bytes = MAX_I2C_BYTES;
	}
	for (i = 0; i < num_bytes; i++) {
		buf[i] = (uint8_t)strtol(argv[4 + i], NULL, 16);
	}

	if (i2c_burst_write(dev, dev_addr, reg_addr, buf, num_bytes) < 0) {
		shell_error(shell, "Failed to write to device: %s", argv[1]);
		return -EIO;
	}

	return 0;
}

static int cmd_i2c_write_byte(const struct shell *shell,
			      size_t argc, char **argv)
{
	struct device *dev;
	int reg_addr;
	int dev_addr;
	int out_byte;

	dev = device_get_binding(argv[1]);
	if (!dev) {
		shell_error(shell, "I2C: Device driver %s not found.",
			    argv[1]);
		return -ENODEV;
	}

	dev_addr = strtol(argv[2], NULL, 16);
	reg_addr = strtol(argv[3], NULL, 16);
	out_byte = strtol(argv[4], NULL, 16);

	if (i2c_reg_write_byte(dev, dev_addr, reg_addr, out_byte) < 0) {
		shell_error(shell, "Failed to write to device: %s", argv[1]);
		return -EIO;
	}

	return 0;
}

static int cmd_i2c_read_byte(const struct shell *shell,
			     size_t argc, char **argv)
{
	struct device *dev;
	int reg_addr;
	int dev_addr;
	u8_t out;

	dev = device_get_binding(argv[1]);
	if (!dev) {
		shell_error(shell, "I2C: Device driver %s not found.",
			    argv[1]);
		return -ENODEV;
	}

	dev_addr = strtol(argv[2], NULL, 16);
	reg_addr = strtol(argv[3], NULL, 16);

	if (i2c_reg_read_byte(dev, dev_addr, reg_addr, &out) < 0) {
		shell_error(shell, "Failed to read from device: %s", argv[1]);
		return -EIO;
	}

	shell_print(shell, "Output: 0x%x", out);

	return 0;
}

/* i2c read <device> <dev_addr> [<numbytes>] */
static int cmd_i2c_read(const struct shell *shell, size_t argc, char **argv)
{
	u8_t buf[MAX_I2C_BYTES];
	struct device *dev;
	int num_bytes;
	int reg_addr;
	int dev_addr;

	dev = device_get_binding(argv[1]);
	if (!dev) {
		shell_error(shell, "I2C: Device driver %s not found.", argv[1]);
		return -ENODEV;
	}

	dev_addr = strtol(argv[2], NULL, 16);
	reg_addr = strtol(argv[3], NULL, 16);
	if (argc > 4) {
		num_bytes = strtol(argv[4], NULL, 16);
		if (num_bytes > MAX_I2C_BYTES)
			num_bytes = MAX_I2C_BYTES;
	} else {
		num_bytes = MAX_I2C_BYTES;
	}

	if (i2c_burst_read(dev, dev_addr, reg_addr, buf, num_bytes) < 0) {
		shell_error(shell, "Failed to read from device: %s", argv[1]);
		return -EIO;
	}

	shell_hexdump(shell, buf, num_bytes);

	return 0;
}

static void device_name_get(size_t idx, struct shell_static_entry *entry);

SHELL_DYNAMIC_CMD_CREATE(dsub_device_name, device_name_get);

static void device_name_get(size_t idx, struct shell_static_entry *entry)
{
	int device_idx = 0;
	struct device *dev;

	entry->syntax = NULL;
	entry->handler = NULL;
	entry->help = NULL;
	entry->subcmd = &dsub_device_name;

	for (dev = __device_start; dev != __device_end; dev++) {
		if ((dev->driver_api != NULL) &&
		    strstr(dev->name, I2C_DEVICE_PREFIX) != NULL &&
		    strcmp(dev->name, "") && (dev->name != NULL)) {
			if (idx == device_idx) {
				entry->syntax = dev->name;
				break;
			}
			device_idx++;
		}
	}
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_i2c_cmds,
			       SHELL_CMD(scan, &dsub_device_name,
					 "Scan I2C devices", cmd_i2c_scan),
			       SHELL_CMD(recover, &dsub_device_name,
					 "Recover I2C bus", cmd_i2c_recover),
			       SHELL_CMD_ARG(read, &dsub_device_name,
					     "Read bytes from an I2C device",
					     cmd_i2c_read, 3, MAX_I2C_BYTES),
			       SHELL_CMD_ARG(read_byte, &dsub_device_name,
					     "Read a byte from an I2C device",
					     cmd_i2c_read_byte, 3, 1),
			       SHELL_CMD_ARG(write, &dsub_device_name,
					     "Write bytes to an I2C device",
					     cmd_i2c_write, 3, MAX_I2C_BYTES),
			       SHELL_CMD_ARG(write_byte, &dsub_device_name,
					     "Write a byte to an I2C device",
					     cmd_i2c_write_byte, 4, 1),
			       SHELL_SUBCMD_SET_END     /* Array terminated. */
			       );

SHELL_CMD_REGISTER(i2c, &sub_i2c_cmds, "I2C commands", NULL);
