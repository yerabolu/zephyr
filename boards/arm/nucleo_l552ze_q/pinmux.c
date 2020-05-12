/*
 * Copyright (c) 2020 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-L552ZE-Q board */
static const struct pin_config pinconf[] = {
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(lpuart1))
	{STM32_PIN_PG7, STM32L5X_PINMUX_FUNC_PG7_LPUART1_TX},
	{STM32_PIN_PG8, STM32L5X_PINMUX_FUNC_PG8_LPUART1_RX},
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
