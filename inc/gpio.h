#ifndef  _GPIO_H_

#define  _GPIO_H_


#include "stm32f10x.h"


#define LED_PORT GPIOB
#define LED_PIN 6
#define LED_T() (LED_PORT->ODR ^=(1<<LED_PIN))
#define LED(x) x?(LED_PORT->ODR &=~(1<<LED_PIN)):(LED_PORT->ODR |=(1<<LED_PIN))

void led_breath(int speed);

#define LED_TOGGLE(x,y)  (x->ODR ^=(1<<y)) 


#define KEY3_PORT GPIOB
#define KEY4_PORT GPIOB
#define KEY5_PORT GPIOB
#define KEY2_PORT GPIOA
#define KEY3_PIN 3
#define KEY4_PIN 4
#define KEY5_PIN 5
#define KEY2_PIN 0

#define KEY_STATE(x,y) (!(x->IDR & (1<<y)))

void Key_Init(void);
void Led_Init(void);
u8 Get_KeyValue(void);


#endif







