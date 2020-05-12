/*
 * Copyright (c) 2019 The Chromium OS Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

static const struct pin_config pinconf[] = {
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(usart1))
	{STM32_PIN_PA9, STM32F0_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32F0_PINMUX_FUNC_PA10_USART1_RX},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(i2c1))
	{STM32_PIN_PB8, STM32F0_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB9, STM32F0_PINMUX_FUNC_PB9_I2C1_SDA},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(i2c2))
	{STM32_PIN_PA11, STM32F0_PINMUX_FUNC_PA11_I2C2_SCL},
	{STM32_PIN_PA12, STM32F0_PINMUX_FUNC_PA12_I2C2_SDA},
#endif
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
