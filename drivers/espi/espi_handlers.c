/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <drivers/espi.h>
#include <syscall_handler.h>


static inline int z_vrfy_espi_config(struct device *dev, struct espi_cfg *cfg)
{
	struct  espi_cfg cfg_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, config));
	Z_OOPS(z_user_from_copy(&cfg_copy, cfg,
				sizeof(struct espi_cfg)));

	return z_impl_espi_config(dev, &cfg_copy);
}
#include <syscalls/espi_config_mrsh.c>

static inline bool z_vrfy_espi_get_channel_status(struct device *dev,
						  enum espi_channel ch)
{
	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, get_channel_status));

	return z_impl_espi_get_channel_status(dev, ch);
}
#include <syscalls/espi_get_channel_status_mrsh.c>

static inline int z_vrfy_espi_read_lpc_request(struct device *dev,
					       enum lpc_peripheral_opcode op,
					       u32_t *data)
{
	int ret;
	u32_t data_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, read_lpc_request));

	ret = z_impl_espi_read_lpc_request(dev, op, &data_copy);
	Z_OOPS(z_user_to_copy(data, &data_copy, sizeof(u8_t)));

	return ret;
}
#include <syscalls/espi_read_lpc_request_mrsh.c>

static inline int z_vrfy_espi_write_lpc_request(struct device *dev,
						enum lpc_peripheral_opcode op,
						u32_t *data)
{
	u32_t data_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, write_lpc_request));
	Z_OOPS(z_user_from_copy(&data_copy, data, sizeof(*data)));

	return z_impl_espi_write_lpc_request(dev, op, data_copy);
}
#include <syscalls/espi_write_lpc_request_mrsh.c>

static inline int z_vrfy_espi_send_vwire(struct device *dev,
					 enum espi_vwire_signal signal,
					 u8_t level)
{
	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, send_vwire));

	return z_impl_espi_send_vwire(dev, signal, level);
}
#include <syscalls/espi_send_vwire_mrsh.c>

static inline int z_vrfy_espi_receive_vwire(struct device *dev,
					    enum espi_vwire_signal signal,
					    u8_t *level)
{
	int ret;
	u8_t level_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, receive_vwire));

	ret = z_impl_espi_receive_vwire(dev, signal, &level_copy);
	Z_OOPS(z_user_to_copy(level, &level_copy, sizeof(u8_t)));

	return ret;
}
#include <syscalls/espi_receive_vwire_mrsh.c>

static inline int z_vrfy_espi_read_request(struct device *dev,
					   struct espi_request_packet *req)
{
	int ret;
	struct  espi_request_packet req_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, read_request));
	Z_OOPS(z_user_from_copy(&req_copy, req,
				sizeof(struct espi_request_packet)));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(req_copy.data, req_copy.len));

	ret = z_impl_espi_read_request(dev, &req_copy);

	Z_OOPS(z_user_to_copy(req, &req_copy,
			      sizeof(struct espi_request_packet)));

	return ret;
}
#include <syscalls/espi_read_request_mrsh.c>

static inline int z_vrfy_espi_write_request(struct device *dev,
					    struct espi_request_packet *req)
{
	int ret;
	struct  espi_request_packet req_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, write_request));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(req->data, req->len));
	Z_OOPS(z_user_from_copy(&req_copy, req,
				sizeof(struct espi_request_packet)));

	ret = z_impl_espi_write_request(dev, &req_copy);

	return ret;
}
#include <syscalls/espi_write_request_mrsh.c>

static inline int z_vrfy_espi_send_oob(struct device *dev,
				       struct espi_oob_packet *pckt)
{
	int ret;
	struct  espi_oob_packet pckt_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, send_oob));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(pckt->buf, pckt->len));
	Z_OOPS(z_user_from_copy(&pckt_copy, pckt,
				sizeof(struct espi_oob_packet)));

	ret = z_impl_espi_send_oob(dev, &pckt_copy);

	return ret;
}
#include <syscalls/espi_send_oob_mrsh.c>

static inline int z_vrfy_espi_receive_oob(struct device *dev,
					  struct espi_oob_packet *pckt)
{
	int ret;
	struct  espi_oob_packet pckt_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, receive_oob));
	Z_OOPS(z_user_from_copy(&pckt_copy, pckt,
				sizeof(struct espi_oob_packet)));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pckt->buf, pckt->len));

	ret = z_impl_espi_receive_oob(dev, &pckt_copy);
	Z_OOPS(z_user_to_copy(pckt, &pckt_copy,
			      sizeof(struct espi_oob_packet)));

	return ret;
}
#include <syscalls/espi_receive_oob_mrsh.c>

static inline int z_vrfy_espi_read_flash(struct device *dev,
					 struct espi_flash_packet *pckt)
{
	int ret;
	struct  espi_flash_packet pckt_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, read_flash));
	Z_OOPS(z_user_from_copy(&pckt_copy, pckt,
				sizeof(struct espi_flash_packet)));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pckt->buf, pckt->len));

	ret = z_impl_espi_read_flash(dev, pckt);
	Z_OOPS(z_user_to_copy(pckt, &pckt_copy,
			      sizeof(struct espi_flash_packet)));

	return ret;
}
#include <syscalls/espi_read_flash_mrsh.c>

static inline int z_vrfy_espi_write_flash(struct device *dev,
					  struct espi_flash_packet *pckt)
{
	int ret;
	struct  espi_flash_packet pckt_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, write_flash));
	Z_OOPS(z_user_from_copy(&pckt_copy, pckt,
				sizeof(struct espi_flash_packet)));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(pckt->buf, pckt->len));

	ret = z_impl_espi_write_flash(dev, &pckt_copy);

	return ret;
}
#include <syscalls/espi_write_flash_mrsh.c>

static inline int z_vrfy_espi_flash_erase(struct device *dev,
					  struct espi_flash_packet *pckt)
{
	int ret;
	struct  espi_flash_packet pckt_copy;

	Z_OOPS(Z_SYSCALL_DRIVER_ESPI(dev, write_flash));
	Z_OOPS(z_user_from_copy(&pckt_copy, pckt,
				sizeof(struct espi_flash_packet)));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(pckt->buf, pckt->len));

	ret = z_impl_espi_flash_erase(dev, &pckt_copy);

	return ret;
}
#include <syscalls/espi_flash_erase_mrsh.c>
