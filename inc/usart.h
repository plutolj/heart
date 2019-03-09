#ifndef  _USART_H_

#define  _USART_H_


#include "stm32f10x.h"
void Usart1_Init( u32 fck,u32 brr);
u8 Usart1_RX(void);
void Usart1_TX(u8 ch);



#endif

