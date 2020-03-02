#ifndef __UART_H
#define	__UART_H

#include "stm32f10x.h"

void UART_Init(void);
void USART_SendByte(uint8_t Data);
void USART_SendString(char *str);

#endif /* __UART_H */