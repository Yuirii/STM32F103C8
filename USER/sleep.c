
#include "sleep.h"
#include "led.h"

extern int RTC_flag; 

void Enter_sleepmode()
{

	
}

void RTC_Init(void)
{
	//uint16_t flash_str = BKP_ReadBackupRegister(BKP_DR1);
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR, ENABLE);	
	PWR_BackupAccessCmd(ENABLE);
		
	//BKP_ClearFlag();
	//BKP_DeInit(); //reset
	RCC_LSEConfig(RCC_LSE_ON);//lse set
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{		}
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); //choose LSE as RTCCLK
	RCC_RTCCLKCmd(ENABLE);
	
	RTC_WaitForLastTask();
	RTC_WaitForSynchro();
	RTC_ITConfig(RTC_IT_ALR, ENABLE); //rtc
	RTC_WaitForLastTask();

	RTC_SetPrescaler(32767);
	RTC_WaitForLastTask();
	
	RTCALR_Set(); //报警时间设置

}

void RTC_IRQHandler(void)
{
//	RTC_WaitForSynchro();
//	RTC_flag = 1;
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
	RTC_SetAlarm(10); 
	RTC_WaitForLastTask();  
	RTC_WaitForSynchro();
}