//¹¤³ÌÄ£°æ

#include "stm32f10x.h"
#include "led.h"
#include "exit.h"
#include "uart.h"
#include "sleep.h"
#include "timer.h"

int EXTI_flag = 0; 
int RTC_flag = 0; 
int TIM2_flag = 0; 
int TIM3_flag = 0; 

uint16_t temp = 1;

int main(void)
{	
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RTC_Init();	
	LED_GPIO_Config();	
	Timer2_Init();	
	Timer3_Init();
	EXIT_Init();
	UART_Init();
	LED_On();
	Delayms(1000);
	LED_Off();
	Delayms(1000);
	LED_On();
	Delayms(1000);

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
			USART_SendByte('a');
			TIM3_flag = 0;
			
			if(TIM2_flag == 1)
			{
				//TIM2 Handler			
				USART_SendByte('B');
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);			
				TIM2_flag = 0;
				PWR_EnterSTANDBYMode();
				//PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI|PWR_STOPEntry_WFE);
			}			
		}
	}
}
	

