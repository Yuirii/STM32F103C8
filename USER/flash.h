#ifndef __FLASH_H
#define	__FLASH_H

#include "stm32f10x.h"
#include "uart.h"

typedef uint32_t TestStatus;

#define PASSED 1
#define FAILED 0

#define FLASH_PAGE_SIZE  ((uint16_t)0x400) //1024  字节

#define WRITE_START_ADDR ((uint32_t)0x08008000)
#define WRITE_END_ADDR 	 ((uint32_t)0x08008800)

int Inter_Flash_Test(void); //测试flash读写
void WriteProtect_Toggle(void);//写保护反转
void ReadProtect_Toggle(void);

#endif /* __FLASH_H */