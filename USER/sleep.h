#ifndef __SLEEP_H
#define	__SLEEP_H

#include "stm32f10x.h"


void Enter_sleepmode(void);
void RTC_Init(void);
void RTC_NVIC_Init(void);
void RTCALR_Set();

#endif /* __SLEEP_H */
