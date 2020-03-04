
#include "sleep.h"
#include "led.h"

extern int RTC_flag; 

void Enter_sleepmode()
{

	
}

uint8_t RTC_Init(void)
{
	uint8_t temp = 0;
	//uint16_t flash_str = BKP_ReadBackupRegister(BKP_DR1);
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR, ENABLE);	
	PWR_BackupAccessCmd(ENABLE);
		
//	if(BKP_ReadBackupRegister(BKP_DR1) != 0xC0B4)//not judgment!????
//	{
//		BKP_ClearFlag();
//		BKP_DeInit(); //reset
		RCC_LSEConfig(RCC_LSE_ON);//lse set
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
		{		}
//		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	
//			{
//			    temp++;
//			    Delayms(10);
//			}

//		if(temp>=250) return 1;  
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); //choose LSE as RTCCLK
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForLastTask();
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_ALR, ENABLE); //rtc
		RTC_WaitForLastTask();

		RTC_SetPrescaler(32767);
		RTC_WaitForLastTask();
		
		RTCALR_Set(); //报警时间设置
		
//		BKP_WriteBackupRegister(BKP_DR1, 0XC0B4);
		PWR_BackupAccessCmd(DISABLE);   
//	}
//	else
//	{
//		PWR_BackupAccessCmd(DISABLE);

//		RTC_WaitForSynchro();

//		RTC_ITConfig(RTC_IT_ALR,ENABLE); //??RTC?????????	

//		RTC_WaitForLastTask();
//		 
//	}
//	RTC_NVIC_Init();
	return 0;
}

void RTC_IRQHandler(void)
{
	RTC_WaitForSynchro();
//	RTC_flag = 1;
//	PWR_BackupAccessCmd(ENABLE);
//	RTC_SetAlarm(10+RTC_GetCounter());
//	PWR_BackupAccessCmd(DISABLE);
	RTC_ClearITPendingBit(RTC_IT_ALR);
}

void RTC_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStrue;
	
	NVIC_InitStrue.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStrue);//设置中断分组	
}

void RTCALR_Set()
{
	RTC_SetCounter(0);
	RTC_WaitForLastTask();
	RTC_SetAlarm(9); 
	RTC_WaitForLastTask();  
	RTC_WaitForSynchro();
}