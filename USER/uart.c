
#include "uart.h"

#define UART_RX GPIO_Pin_10
#define UART_TX GPIO_Pin_9

void UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //
	USART_InitTypeDef UART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //全双工，推挽复用输出模式
	GPIO_InitStructure.GPIO_Pin = UART_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空上拉都可
	GPIO_InitStructure.GPIO_Pin = UART_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	UART_InitStructure.USART_BaudRate = 115200;
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	UART_InitStructure.USART_Parity = USART_Parity_No;
	UART_InitStructure.USART_StopBits = USART_StopBits_1;
	UART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &UART_InitStructure);
	USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStrue);//设置中断分组
}

void USART1_IRQHandler()
{
	uint8_t res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		res = USART_ReceiveData(USART1);
		USART_SendData(USART1, res);
	}	
}

void USART_SendByte(uint8_t Data)
{
	USART_SendData(USART1, Data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void USART_SendString(char *str)
{
	uint16_t k = 0;
	do{
		USART_SendByte(*(str+k));
		k++;
	}while(*(str + k) != '\0');
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}