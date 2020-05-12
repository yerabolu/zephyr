/*
 * Copyright (c) 2019 Song Qiang <songqiang1304521@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DMA_STM32_H_
#define DMA_STM32_H_

/* Maximum data sent in single transfer (Bytes) */
#define DMA_STM32_MAX_DATA_ITEMS	0xffff

struct dma_stm32_stream {
	u32_t direction;
#ifdef CONFIG_DMAMUX_STM32
	int mux_channel; /* stores the dmamux channel */
#endif /* CONFIG_DMAMUX_STM32 */
	bool source_periph;
	bool busy;
	u32_t src_size;
	u32_t dst_size;
	void *callback_arg; /* holds the client data */
	void (*dma_callback)(void *arg, u32_t id,
			     int error_code);
};

struct dma_stm32_data {
	int max_streams;
	struct dma_stm32_stream *streams;
};

struct dma_stm32_config {
	struct stm32_pclken pclken;
	void (*config_irq)(struct device *dev);
	bool support_m2m;
	u32_t base;
};

#ifdef CONFIG_DMA_STM32_V1
/* from DTS the dma stream id is in range 0..<dma-requests>-1 */
#define STREAM_OFFSET 0
#else
/* from DTS the dma stream id is in range 1..<dma-requests> */
/* so decrease to set range from 0 from now on */
#define STREAM_OFFSET 1
#endif /* CONFIG_DMA_STM32_V1 */

extern u32_t table_ll_stream[];
extern u32_t (*func_ll_is_active_tc[])(DMA_TypeDef *DMAx);
extern void (*func_ll_clear_tc[])(DMA_TypeDef *DMAx);
extern u32_t (*func_ll_is_active_ht[])(DMA_TypeDef *DMAx);
extern void (*func_ll_clear_ht[])(DMA_TypeDef *DMAx);
#ifdef CONFIG_DMA_STM32_V2
extern u32_t (*func_ll_is_active_gi[])(DMA_TypeDef *DMAx);
extern void (*func_ll_clear_gi[])(DMA_TypeDef *DMAx);
#endif
#ifdef CONFIG_DMA_STM32_V1
extern u32_t table_ll_channel[];
#endif

void stm32_dma_dump_stream_irq(DMA_TypeDef *dma, u32_t id);
void stm32_dma_clear_stream_irq(DMA_TypeDef *dma, u32_t id);
bool stm32_dma_is_irq_happened(DMA_TypeDef *dma, u32_t id);
bool stm32_dma_is_unexpected_irq_happened(DMA_TypeDef *dma, u32_t id);
void stm32_dma_enable_stream(DMA_TypeDef *dma, u32_t id);
int stm32_dma_disable_stream(DMA_TypeDef *dma, u32_t id);
void stm32_dma_config_channel_function(DMA_TypeDef *dma, u32_t id, u32_t slot);

#ifdef CONFIG_DMA_STM32_V1
void stm32_dma_disable_fifo_irq(DMA_TypeDef *dma, u32_t id);
bool stm32_dma_check_fifo_mburst(LL_DMA_InitTypeDef *DMAx);
u32_t stm32_dma_get_fifo_threshold(u16_t fifo_mode_control);
u32_t stm32_dma_get_mburst(struct dma_config *config, bool source_periph);
u32_t stm32_dma_get_pburst(struct dma_config *config, bool source_periph);
#endif

#ifdef CONFIG_DMAMUX_STM32
/* dma_stm32_ api functions are exported to the dmamux_stm32 */
int dma_stm32_configure(struct device *dev, u32_t id,
			       struct dma_config *config);
int dma_stm32_reload(struct device *dev, u32_t id,
			    u32_t src, u32_t dst, size_t size);
int dma_stm32_start(struct device *dev, u32_t id);
int dma_stm32_stop(struct device *dev, u32_t id);
#endif /* CONFIG_DMAMUX_STM32 */

#endif /* DMA_STM32_H_*/
