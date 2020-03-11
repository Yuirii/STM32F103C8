
#include "flash.h"


int Inter_Flash_Test(void)
{
	uint32_t EraseCounter = 0x00; //Erase xx pages.
	uint32_t Address = 0x00;			//
	uint32_t Data = 0x00470048;		//Write down xx param.
	uint32_t NBRofPage = 0x00;		//
	uint16_t num;
	
	FLASH_Status FLASHStatus = FLASH_COMPLETE; //Recoed the consequence that have been erased.
	TestStatus MemoryProgramStatus = PASSED;
	
	FLASH_Unlock();
	
	//calculate the num of pages that need to be erased.
	NBRofPage = (WRITE_END_ADDR - WRITE_START_ADDR)/FLASH_PAGE_SIZE;
	
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	
	//erase by pages.
	for(EraseCounter = 0; (EraseCounter < NBRofPage)&&(FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
		FLASHStatus = FLASH_ErasePage(WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
	}

	//WRITE DATA.
	Address = WRITE_START_ADDR;
	while((Address < WRITE_END_ADDR)&&(FLASHStatus == FLASH_COMPLETE))
	{
		FLASHStatus = FLASH_ProgramWord(Address, Data);
		Address += 4;
	}

	FLASH_Lock();

	//CHECK THE CONSEQUNENCE.
	Address = WRITE_START_ADDR;
	while((Address < WRITE_END_ADDR)&&(MemoryProgramStatus != FAILED))
	{
		if ((*(__IO uint32_t*)Address)!=Data)
		{
			/* code */
			MemoryProgramStatus = FAILED;
		}
		for(num=1; num<5; num++)
		{
			USART_SendByte(*(uint8_t*)(Address+num));//(*(uint32_t*)Address);
		}
//		USART_SendString((__IO uint8_t*)Address);//(*(uint32_t*)Address);
		Address += 4;
	}
	return MemoryProgramStatus;	
}

void WriteProtect_Toggle(void)
{
	/****protect:0 unprotect:1****/
	if (FLASH_GetWriteProtectionOptionByte() != 0xffffffff)
	{
		/* code */
		USART_SendString("Write protect.");
		FLASH_Unlock();
		FLASH_EraseOptionBytes();
		FLASH_EnableWriteProtection(0x00000000);
		USART_SendString("FINISH. RESET enter write unprotect.");

		//NVIC_SystemReset();
	}
	else
	{
		USART_SendString("Write unprotect.");
		FLASH_Unlock();
		FLASH_EraseOptionBytes();
		FLASH_EnableWriteProtection(FLASH_WRProt_AllPages);

		USART_SendString("FINISH. RESET enter write protect.");
		//NVIC_SystemReset();
	}
}

void ReadProtect_Toggle(void)
{
	if (FLASH_GetReadOutProtectionStatus() != RESET)
	{
		/* code */
		USART_SendString("Read protect.");
		FLASH_Unlock();
		USART_SendString("Data will be erased.");
		FLASH_ReadOutProtection(DISABLE);
		USART_SendString("Read unprotect.");//no data.
	}
	else
	{
		USART_SendString("Read unprotect.");
		FLASH_Unlock();
		FLASH_ReadOutProtection(ENABLE);
		USART_SendString("Voltage reset, then enter protect.");//Voltage reset.
	}
}