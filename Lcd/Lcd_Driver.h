#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_


/******************************************************************************
//������������STM32F103CB
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PA3
//              DC    ��PA4
//              CS    ��PB1
//							BL    ��PA2
*******************************************************************************/

#include "stm32f10x.h"
#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111

#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ 


#define LCD_CTRLA   	  	GPIOA		//����TFT���ݶ˿�
#define LCD_CTRLB   	  	GPIOB		//����TFT���ݶ˿�

#define LCD_SCL        	GPIO_Pin_5	//SCL/SCK
#define LCD_SDA        	GPIO_Pin_7	//MOSI--->>TFT --SDA/DIN
#define LCD_CS        	GPIO_Pin_1  //TFT --CS/CE

#define LCD_LED        	GPIO_Pin_2  //TFT --BL
#define LCD_RS         	GPIO_Pin_4	//TFT --RS/DC
#define LCD_RST     		GPIO_Pin_3	//TFT --RST

//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)

//Һ�����ƿ���1�������궨��
#define	LCD_SCL_SET  	LCD_CTRLA->BSRR=LCD_SCL    
#define	LCD_SDA_SET  	LCD_CTRLA->BSRR=LCD_SDA   
#define	LCD_CS_SET  	LCD_CTRLB->BSRR=LCD_CS  

    
#define	LCD_LED_SET  	LCD_CTRLA->BSRR=LCD_LED   
#define	LCD_RS_SET  	LCD_CTRLA->BSRR=LCD_RS 
#define	LCD_RST_SET  	LCD_CTRLA->BSRR=LCD_RST 
//Һ�����ƿ���0�������궨��
#define	LCD_SCL_CLR  	LCD_CTRLA->BRR=LCD_SCL  
#define	LCD_SDA_CLR  	LCD_CTRLA->BRR=LCD_SDA 
#define	LCD_CS_CLR  	LCD_CTRLB->BRR=LCD_CS 
    
#define	LCD_LED_CLR  	LCD_CTRLA->BRR=LCD_LED 
#define	LCD_RST_CLR  	LCD_CTRLA->BRR=LCD_RST
#define	LCD_RS_CLR  	LCD_CTRLA->BRR=LCD_RS 

#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //�������
#define LCD_DATAIN     LCD_DATA->IDR;   //��������

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 

//LCD��������
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);

//LCD���ܺ���
u16 LCD_BGR2RGB(u16 c);
void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc); 
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);  
void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void Lcd_Fill(u16 x0, u16 y0, u16 width, u16 height,u16 Color);
void Lcd_Show_Photo(u16 x0, u16 y0, u16 width, u16 height,const unsigned char * photo);



#endif
