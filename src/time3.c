#include "time3.h"
#include "gpio.h"
#include "MAX30100_PulseOximeter.h"
void TIM3_IRQHandler(void)
{
  TIM3->SR &=~(1<<0);
	POupdate();
}

void Time3_Init( u32 psc,u32 reload)
{
	RCC->APB1ENR |=(1<<1);
	TIM3->CR1 = 0;
	TIM3->CR1 |=(1<<7);
	TIM3->DIER |=(1<<0);
	TIM3->CNT = 0;
	TIM3->PSC = psc-1;
	TIM3->ARR = reload;
	TIM3->CR1 |=(1<<0);
	NVIC_EnableIRQ(TIM3_IRQn);
}
