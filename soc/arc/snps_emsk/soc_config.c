/*
 * Copyright (c) 2018 Synopsys, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <init.h>
#include "soc.h"


#ifdef CONFIG_UART_NS16550

static int uart_ns16550_init(struct device *dev)
{
	ARG_UNUSED(dev);

	/* On ARC EM Starter kit board,
	 * send the UART the command to clear the interrupt
	 */
#if DT_HAS_NODE_STATUS_OKAY(DT_INST(0, ns16550))
	sys_write32(0, DT_REG_ADDR(DT_INST(0, ns16550))+0x4);
	sys_write32(0, DT_REG_ADDR(DT_INST(0, ns16550))+0x10);
#endif /* DT_HAS_NODE_STATUS_OKAY(DT_INST(0, ns16550)) */
#if DT_HAS_NODE_STATUS_OKAY(DT_INST(1, ns16550))
	sys_write32(0, DT_REG_ADDR(DT_INST(1, ns16550))+0x4);
	sys_write32(0, DT_REG_ADDR(DT_INST(1, ns16550))+0x10);
#endif /* DT_HAS_NODE_STATUS_OKAY(DT_INST(1, ns16550)) */

	return 0;
}

SYS_INIT(uart_ns16550_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);

#endif /* CONFIG_UART_NS16550 */
