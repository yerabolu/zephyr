/*
 * Copyright (c) 2019 Benjamin Valentin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <drivers/pinmux.h>
#include <soc.h>

static int board_pinmux_init(struct device *dev)
{
	struct device *muxa = device_get_binding("PINMUX_A");
	struct device *muxb = device_get_binding("PINMUX_B");
	struct device *muxc = device_get_binding("PINMUX_C");
	struct device *muxd = device_get_binding("PINMUX_D");

	ARG_UNUSED(dev);
	ARG_UNUSED(muxa);
	ARG_UNUSED(muxb);
	ARG_UNUSED(muxc);
	ARG_UNUSED(muxd);

#if ATMEL_SAM0_DT_SERCOM_CHECK(0, atmel_sam0_uart)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(1, atmel_sam0_uart)
	/* NOTE: SERCOM1 UART is used by the UART driver tests */
	/* SERCOM1 ON RX=PC22, TX=PC23 */
	pinmux_pin_set(muxc, 22, PINMUX_FUNC_C);
	pinmux_pin_set(muxc, 23, PINMUX_FUNC_C);
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(2, atmel_sam0_uart)
	/* SERCOM2 ON RX=PB24, TX=PB25 */
	pinmux_pin_set(muxb, 24, PINMUX_FUNC_D);
	pinmux_pin_set(muxb, 25, PINMUX_FUNC_D);
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
#if ATMEL_SAM0_DT_SERCOM_CHECK(6, atmel_sam0_uart)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(7, atmel_sam0_uart)
#warning Pin mapping may not be configured
#endif

#if ATMEL_SAM0_DT_SERCOM_CHECK(0, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(1, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(2, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(3, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(4, atmel_sam0_spi)
	/* SERCOM4 ON MOSI=PB27, MISO=PB29, SCK=PB26 */
	pinmux_pin_set(muxb, 26, PINMUX_FUNC_D);
	pinmux_pin_set(muxb, 27, PINMUX_FUNC_D);
	pinmux_pin_set(muxb, 29, PINMUX_FUNC_D);
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(5, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(6, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(7, atmel_sam0_spi)
#warning Pin mapping may not be configured
#endif

#if ATMEL_SAM0_DT_SERCOM_CHECK(0, atmel_sam0_i2c)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(1, atmel_sam0_i2c)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(2, atmel_sam0_i2c)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(3, atmel_sam0_i2c)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(4, atmel_sam0_i2c)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(5, atmel_sam0_i2c)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(6, atmel_sam0_i2c)
#warning Pin mapping may not be configured
#endif
#if ATMEL_SAM0_DT_SERCOM_CHECK(7, atmel_sam0_i2c)
	pinmux_pin_set(muxd, 8, PINMUX_FUNC_C);
	pinmux_pin_set(muxd, 9, PINMUX_FUNC_C);
#endif

#ifdef CONFIG_USB_DC_SAM0
	/* USB DP on PA25, USB DM on PA24 */
	pinmux_pin_set(muxa, 25, PINMUX_FUNC_H);
	pinmux_pin_set(muxa, 24, PINMUX_FUNC_H);
#endif

#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(gmac))
	pinmux_pin_set(muxa, 14, PINMUX_FUNC_L);	/* PA14 = GTXCK */
	pinmux_pin_set(muxa, 17, PINMUX_FUNC_L);	/* PA17 = GTXEN */
	pinmux_pin_set(muxa, 18, PINMUX_FUNC_L);	/* PA18 = GTX0 */
	pinmux_pin_set(muxa, 19, PINMUX_FUNC_L);	/* PA19 = GTX1 */
	pinmux_pin_set(muxc, 20, PINMUX_FUNC_L);	/* PC20 = GRXDV */
	pinmux_pin_set(muxa, 13, PINMUX_FUNC_L);	/* PA13 = GRX0 */
	pinmux_pin_set(muxa, 12, PINMUX_FUNC_L);	/* PA12 = GRX1 */
	pinmux_pin_set(muxa, 15, PINMUX_FUNC_L);	/* PA15 = GRXER */
	pinmux_pin_set(muxc, 11, PINMUX_FUNC_L);	/* PC11 = GMDC */
	pinmux_pin_set(muxc, 12, PINMUX_FUNC_L);	/* PC12 = GMDIO */
#endif

	return 0;
}

SYS_INIT(board_pinmux_init, PRE_KERNEL_1, CONFIG_PINMUX_INIT_PRIORITY);
