#include "gpio.h"
#include "delay.h"
 
void Led_Init(void)
{
	//LED
 RCC->APB2ENR |=(1<<3);//开时钟
 GPIOB->CRL &= ~(0xf<<24);
 GPIOB->CRL |=(0x3<<24);
 GPIOB->ODR |=(1<<6);
}
void Key_Init(void)
{
  RCC->APB2ENR |=(1<<0)|(1<<3)|(1<<2);//开AFIO和GPIOA,GPIOB时钟
	AFIO->MAPR &=~(0x7 <<24);
	AFIO->MAPR |=(0x4 <<24);//关闭JTAG-DP和SW-DP
	GPIOB->CRL &=~(0xfff<<12);
	GPIOB->CRL |=(0x444<<12);
	GPIOA->CRL &=~(0xf<<0);
	GPIOA->CRL |=(0x4<<0);
}



u8 Get_KeyValue(void)   
{
	 u8 key_value = 0xff;
	static  u8 count4 = 0;
	static  u8 count2 = 0;
	static  u8 count5 = 0;
	static  u8 count3 = 0;
	if(KEY_STATE(KEY4_PORT,KEY4_PIN))

	{
	  count4++;
	}
	else if(count4 >=10)
	{
	  key_value = 4;
		count4 = 0;
	}
	else
	{
	count4 = 0;
	}
//	 return key_value;

	if(KEY_STATE(KEY3_PORT,KEY3_PIN))
	{
	  count3++;
	}
	else if(count3 >=10)
	{
	  key_value = 3;
		count3 = 0;
	}
	else
	{
	count3 = 0;
	}
	if(KEY_STATE(KEY5_PORT,KEY5_PIN))
	{
	  count5++;
	}
	else if(count5 >=10)
	{
	  key_value = 5;
		count5 = 0;
	}
	else
	{
	count5 = 0;
	}
	if(KEY_STATE(KEY2_PORT,KEY2_PIN))
	{
	  count2++;
	}
	else if(count2 >=10)
	{
	  key_value = 2;
		count2 = 0;
	}
	else
	{
	count2 = 0;
	}
	 return key_value;
		  
}
//int max_time = 3000;   //呼吸灯
//void led_breath(int speed)
//{
//  int i=0;
//	while(1)
//	{
//	 for(i=0;i<max_time;i+=speed)
//		 {
//	   LED(0);
//     Delay_ms(i);
//	   LED(1);
//	   Delay_ms(max_time-i);
//	   } 
//	}
//	while(1)
//	{
//	 for(i=0;i<max_time;i+=speed)
//		 {
//	   LED(1);
//     Delay_ms(i);
//	   LED(0);
//	   Delay_ms(max_time-i);
//	   } 
//	}
//}

 
