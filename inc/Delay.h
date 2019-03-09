#ifndef _Delay_H_
#define _Delay_H_

#include "stm32f10x.h"

extern vu32 RunTime;
extern vu32 Led_Run[2];
extern vu32 Key_Run[2];
extern vu32 Max_Run[2];
extern vu32 UI_Run[2];
void Delay_1us(void);
void Delay(u32 nTimer);
void Delay_Init(void);
void SysTick_Init(u32 reload);
void Delay_ms(u32 ms);

#endif
