
#include "dma.h"

uint16_t DMA1_MEM_LEN;

/**
*	cpar:peipheral address.
*	cmar:memory data address.
*	cndtr:sendbuffer size.
*/
void DMAInit(DMA_Channel_TypeDef* DMA_CHx, uint32_t cpar, uint32_t cmar, uint16_t cndtr)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA_CHx);
	
	DMA_InitStruct.DMA_BufferSize = cndtr;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr = cmar;	//memory data address
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr = cpar; //peipheral address
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;

	DMA_Init(DMA_CHx, &DMA_InitStruct);
	DMA_Cmd(DMA_CHx,ENABLE);
}

void DMACmd(DMA_Channel_TypeDef* DMA_CHx)
{
	DMA_Cmd(DMA_CHx, DISABLE);
	DMA_SetCurrDataCounter(DMA_CHx, DMA1_MEM_LEN);
	DMA_Cmd(DMA_CHx, ENABLE);
}