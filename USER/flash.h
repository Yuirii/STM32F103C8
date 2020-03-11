#ifndef __FLASH_H
#define	__FLASH_H

#include "stm32f10x.h"
#include "uart.h"

typedef uint32_t TestStatus;

#define PASSED 1
#define FAILED 0

#define FLASH_PAGE_SIZE  ((uint16_t)0x400) //1024  �ֽ�

#define WRITE_START_ADDR ((uint32_t)0x08008000)
#define WRITE_END_ADDR 	 ((uint32_t)0x08008800)

int Inter_Flash_Test(void); //����flash��д
void WriteProtect_Toggle(void);//д������ת
void ReadProtect_Toggle(void);

#endif /* __FLASH_H */