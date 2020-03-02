#include "exit.h"
#include "led.h"

#define EXIT1 GPIO_Pin_7

extern int EXTI_flag; 

void EXIT_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //
	EXTI_InitTypeDef EXTI_InitStrue; //
	NVIC_InitTypeDef NVIC_InitStrue; //
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能端口时钟 
  GPIO_InitStructure.GPIO_Pin = EXIT1;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_Init(GPIOA, &GPIO_InitStructure);//
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //开启IO复用时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7); //io 4 映射 到 4
	
	
	EXTI_InitStrue.EXTI_Line = EXTI_Line7;
	EXTI_InitStrue.EXTI_LineCmd = ENABLE;
	EXTI_InitStrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger =EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStrue); //初始化线上中断，设置触发条件
	
	NVIC_InitStrue.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStrue);//设置中断分组
}

void EXTI9_5_IRQHandler()
{
//	Delayms(10);
	EXTI_flag=1;
//	Delayms(10);
	
	EXTI_ClearITPendingBit(EXTI_Line7);
}