/*
 * Copyright (c) 2018 Google LLC.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <drivers/pinmux.h>
#include <soc.h>

static int board_pinmux_init(struct device *dev)
{
	struct device *muxa = device_get_binding(DT_LABEL(DT_NODELABEL(pinmux_a)));

	ARG_UNUSED(dev);

#if ATMEL_SAM0_DT_SERCOM_CHECK(0, atmel_sam0_uart)
	/* SERCOM0 on RX=PA7/pad 3, TX=PA6/pad 2 */
	pinmux_pin_set(muxa, 7, PINMUX_FUNC_D);
	pinmux_pin_set(muxa, 6, PINMUX_FUNC_D);
#endif

#if ATMEL_SAM0_DT_SERCOM_CHECK(2, atmel_sam0_uart)
	/* SERCOM2 on RX=PA9/pad 1, TX=PA8/pad 0 */
	pinmux_pin_set(muxa, 9, PINMUX_FUNC_D);
	pinmux_pin_set(muxa, 8, PINMUX_FUNC_D);
#endif

#if ATMEL_SAM0_DT_SERCOM_CHECK(1, atmel_sam0_uart)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(3, atmel_sam0_uart)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(4, atmel_sam0_uart)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(5, atmel_sam0_uart)
#warning Pin mapping may not be configured
#endif

#if ATMEL_SAM0_DT_SERCOM_CHECK(0, atmel_sam0_spi)
	/* SPI SERCOM0 on MISO=PA9/pad 1, MOSI=PA6/pad 2, SCK=PA7/pad 3 */
	pinmux_pin_set(muxa, 9, PINMUX_FUNC_D);
	pinmux_pin_set(muxa, 6, PINMUX_FUNC_D);
	pinmux_pin_set(muxa, 7, PINMUX_FUNC_D);
#endif

#if ATMEL_SAM0_DT_SERCOM_CHECK(1, atmel_sam0_spi)
	/* SPI SERCOM1 on MOSI=PA0/pad 0, SCK=PA1/pad 1 */
	pinmux_pin_set(muxa, 0, PINMUX_FUNC_D);
	pinmux_pin_set(muxa, 1, PINMUX_FUNC_D);
#endif

#if ATMEL_SAM0_DT_SERCOM_CHECK(2, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(3, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(4, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(5, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif

#ifdef CONFIG_USB_DC_SAM0
	/* USB DP on PA25, USB DM on PA24 */
	pinmux_pin_set(muxa, 25, PINMUX_FUNC_G);
	pinmux_pin_set(muxa, 24, PINMUX_FUNC_G);
#endif

	return 0;
}

SYS_INIT(board_pinmux_init, PRE_KERNEL_1, CONFIG_PINMUX_INIT_PRIORITY);
