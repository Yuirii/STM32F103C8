#include "timer.h"

extern int TIM2_flag; 
extern int TIM3_flag; 

void Timer2_Init()
{
	TIM_TimeBaseInitTypeDef TIMBSINT;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
	
	TIMBSINT.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMBSINT.TIM_CounterMode = TIM_CounterMode_Up;
	TIMBSINT.TIM_Period = 9999;//tout = (period+1)(prescaler+1)/tclk
	TIMBSINT.TIM_Prescaler = 7199;//tclk=72MHZ
	TIM_TimeBaseInit(TIM2, &TIMBSINT);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStrue);//设置中断分组	
	
	TIM_Cmd(TIM2, ENABLE);
}


void Timer3_Init()
{
	TIM_TimeBaseInitTypeDef TIMBSINT;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
	
	TIMBSINT.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMBSINT.TIM_CounterMode = TIM_CounterMode_Up;
	TIMBSINT.TIM_Period = 999;//tout = (period+1)(prescaler+1)/tclk
	TIMBSINT.TIM_Prescaler = 7199;//tclk=72MHZ
	TIM_TimeBaseInit(TIM3, &TIMBSINT);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStrue);//设置中断分组	
	
	TIM_Cmd(TIM3, ENABLE);
}

void TIM2_IRQHandler()
{
	TIM2_flag = 1;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void TIM3_IRQHandler()
{
	TIM3_flag = 1;
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}