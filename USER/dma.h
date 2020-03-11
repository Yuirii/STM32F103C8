#ifndef __DMA_H
#define	__DMA_H

#include "stm32f10x.h"
#include "uart.h"



void DMAInit(DMA_Channel_TypeDef* DMA_CHx, uint32_t cpar, uint32_t cmar, uint16_t cndtr);
void DMACmd(DMA_Channel_TypeDef* DMA_CHx);

#endif /* __DMA_H */