//¹¤³ÌÄ£°æ

#include "stm32f10x.h"
#include "led.h"
#include "exit.h"
#include "uart.h"
#include "sleep.h"
#include "timer.h"
#include "flash.h"
#include "dma.h"

#define SENDBUFFSIZE 100

int EXTI_flag = 0; 
int RTC_flag = 0; 
int TIM2_flag = 0; 
int TIM3_flag = 0; 


char sendbuff[SENDBUFFSIZE]= "HELLO WORLD.";
//uint32_t sendbuff[SENDBUFFSIZE];
uint16_t temp = 1;
uint16_t num_echo = 48;
int i;

int main(void)
{	
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	RTC_Init();	
	LED_GPIO_Config();	
//	Timer3_Init();
//	Timer2_Init();		
//	EXIT_Init();
	UART_Init();
	USART_SendString("USART initialization success.\n");
	DMAInit(DMA1_Channel4, USART1_BASE+0X04, (uint32_t)sendbuff, SENDBUFFSIZE);
	//DMACmd(DMA1_Channel4);
//	for(i = 0; i<1000; i++)
//	{
//		sendbuff[i]= 'p';
//	}
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
//	LED_On();
//	Delayms(1000);
//	LED_Off();
//	Delayms(1000);
//	LED_On();
//	Delayms(1000);
	
	/**read and write protection experiment**/
//	USART_SendString("READ PROTECTION FLAG:");
//	USART_SendByte(FLASH_GetReadOutProtectionStatus());
//	ReadProtect_Toggle();
//	USART_SendString("WRITE PROTECTION FLAG:");
//	USART_SendByte(FLASH_GetWriteProtectionOptionByte());
//	WriteProtect_Toggle();
	
	/***********flash test************/	
//	if(Inter_Flash_Test() == PASSED)
//	{
//		USART_SendString("Success.\n");
//	}
//	else
//	{
//		USART_SendString("Fail.\n");
//	}

//	PWR_EnterSTANDBYMode();	
	while(1){
				
		if(EXTI_flag == 1)
		{
			//EXTI Handler			
			LED_On();
			Delayms(500);
			LED_Off();
			Delayms(500);
			LED_On();
			Delayms(500);
			LED_Off();
			Delayms(500);
			EXTI_flag = 0;
		}
		if(TIM3_flag == 1)
		{
			USART_SendData(USART1,num_echo++);
			TIM3_flag = 0;					
		}		
		if(TIM2_flag == 1)
		{
			//TIM2 Handler			
			
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);			
			TIM2_flag = 0;				
			if(temp == 2)
			{
				USART_SendString("Time to STANDBY.");
				//PWR_EnterSTANDBYMode();
			}
			temp++;
			//PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI|PWR_STOPEntry_WFE);
		}	
	}
}
	

