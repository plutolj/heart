#include "delay.h"
 
void SysTick_Init(u32 reload)
{
	SysTick->CTRL |=(1<<2);//选择时钟
	SysTick->CTRL |=(1<<1);//中断使能
	SysTick->LOAD = reload - 1;//配置重装载值1ms
	SysTick->CTRL |=(1<<0);  
 
}
vu32 Led_Run[2]={0,200};
vu32 RunTime = 0;
vu32 Key_Run[2]= {0,1};
vu32 Max_Run[2]= {0,10};
vu32 UI_Run[2]= {0,1};
void SysTick_Handler(void)
 {
 RunTime++;
 Led_Run[0]++;
 Key_Run[0]++;
 Max_Run[0]++;
	UI_Run[0]++;
 }



void Delay_Init(void)
{
	SysTick->CTRL |= (1<<2);
	SysTick->LOAD = 72000;
	SysTick->CTRL |=(1<<0);
}


void Delay_1us(void)
{
	
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
__NOP();__NOP();	
}
void Delay_us(u32 us)
{	
	while(us--)
	{
		Delay_1us();
	}
}
void Delay_ms(u32 ms)
{
	u32 Time = ms*1000;
	while(Time--)
	{
		Delay_1us();
	}
}

void Delay_nms(u32 ms)
{
   u32 Time = RunTime;
	 while(RunTime < Time + ms);
}
