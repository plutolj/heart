#include "usart.h"
#include "stdio.h"
void Usart1_Init( u32 fck,u32 brr)
{
	uint16_t Mantissa,Fraction;
	float USARTDIV;
	RCC->APB2ENR |=(1<<2)|(1<<14);
	GPIOA->CRH &=~(0xff<<4);
	GPIOA->CRH  |=(0xB<<4);
	GPIOA->CRH  |=(0x4<<8);
	USARTDIV = (fck*1000000.0f)/(16*brr);
	Mantissa=USARTDIV;
	Fraction= (USARTDIV-Mantissa)*16;
	USART1->BRR = (Mantissa<<4)|Fraction;
	USART1->CR1= 0;
	USART1->CR1|=(0x3<<2);
	USART1->CR2 &=~(0x3<<12);
	USART1->CR1|=(1<<13);
}
 
u8 Usart1_RX(void)//½ÓÊÕ
{
  while((USART1->SR &(1<<5))==0);
	return USART1->DR;
}
void Usart1_TX(u8 ch)//·¢ËÍ
{
  while((USART1->SR &(1<<6))==0);
	USART1->DR = ch;
}


int fputc(int c,FILE*stream)
{
  Usart1_TX(c);
	return c;
}
