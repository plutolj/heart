#include "main.h"
#include "gpio.h"
#include "Delay.h"
#include "time3.h"
#include "usart.h"
#include "Lcd_Driver.h"
#include "stdio.h"
#include "photo.h"
#include "MAX30100_PulseOximeter.h"
#include "MAX30100.h"
int main(void)
{
	
	unsigned char x0=8;
	unsigned char x1;
	float value;
	float value2;
	u8 Sum_Count = 0;
	char dif =0;
	char Sum[10]={0};
	u8 flag;
	float a;
	char buf[20] = {0};
	Led_Init();
	Key_Init();
	SysTick_Init(72000);
	SPO2_Init();
	Usart1_Init(72,115200);
	Time3_Init(72,115200);//定时器10ms
	Lcd_Init();
	Gui_DrawFont_GBK16(0,5, RED, WHITE,(u8*)"S2 心率波形图 ");
	Gui_DrawFont_GBK16(0,30, RED, WHITE,(u8*)"S3 心率血氧值 ");
	while(1)
	{
		if( Key_Run[0]> Key_Run[1])  //按键控制
	 {
			Key_Run[0]= 0;
		 Sum[Sum_Count] =rawIRValue;
		 Sum_Count++;
		 Sum_Count %= 10;
		 a = (Sum[0]+Sum[1]+Sum[2]+Sum[3]+Sum[4]+Sum[5]+Sum[6]+Sum[7]+Sum[8]+Sum[9]);
		 if(rawIRValue<a)
			 dif =a-rawIRValue;
		 else
			 dif = rawIRValue-a;
		 dif= dif*0.35 +0.5;
	 
			switch(Get_KeyValue())
			{
				case 2:flag=0,Lcd_Clear(WHITE);break;
				case 3:flag=1,Lcd_Clear(WHITE);break;
				case 4:flag=2;Lcd_Clear(WHITE);break;
			}
		
	
		if(Max_Run[0]>Max_Run[1]&&flag==0)
		{
				Max_Run[0]=0;
				Gui_DrawFont_GBK16(30,142, RED, WHITE,(u8*)"心率波形图 ");
				sprintf(buf,"IR_AD,%05d",rawIRValue);
				Gui_DrawFont_GBK16(10,5, RED, WHITE,(u8*)buf);
				Gui_DrawLine (8,140, 120, 140,BLACK);
				Gui_DrawLine (8,140, 8, 20,BLACK);
				if(x0<120)
				{
					x1=x0+4;
				}
				else
				{
					x0=8;
					x1=x0+4;
				}
				Gui_DrawLine (x1+3,140,x1+3, 20,WHITE);
				Gui_DrawLine (x1+2,140,x1+2, 20,WHITE);
				Gui_DrawLine (x1+1,140,x1+1, 20,WHITE);
				Gui_DrawLine (x1,140,x1, 20,WHITE);
				value2 = 140 - dif;
				Gui_DrawLine (x0,value, x1 , value2,BLACK);
				x0+=4;
				value=value2;

			}
		if(UI_Run[0]>UI_Run[1]&&flag==1)
		{
				UI_Run[0]=0;
				sprintf(buf,"心率,%03dbpm",HeartRate);
				Gui_DrawFont_GBK16(10,30,RED,WHITE,(u8*)buf);
				sprintf(buf,"血氧,%03d%%",SPO2);
				Gui_DrawFont_GBK16(10,60,RED,WHITE,(u8*)buf);
				sprintf(buf,"IR_AD,%05d",rawIRValue);
				Gui_DrawFont_GBK16(10,90,RED,WHITE,(u8*)buf);
				printf ("%d\r\n",rawIRValue);
		}
	}
			
		}
	}

			
					
//				
//				
//				sprintf(buf,"心率,%03dbpm",HeartRate);
//				Gui_DrawFont_GBK16(10,30,RED,WHITE,(u8*)buf);
//				sprintf(buf,"血氧,%03d%%",SPO2);
//				Gui_DrawFont_GBK16(10,60,RED,WHITE,(u8*)buf);
//				sprintf(buf,"IR_AD,%05d",rawIRValue);
//				Gui_DrawFont_GBK16(10,90,RED,WHITE,(u8*)buf);
//				printf ("%d\r\n",rawIRValue);
//				
//			}
//		}
		
	

		


// while(1)  //串口
//	{
//	 Usart1_RX();
//	 Usart1_TX(USART1->DR);
//	} 
//		if( Key_Run[0]> Key_Run[1])  //按键控制
//	 {
//	  Key_Run[0]= 0;
//		switch(Get_KeyValue())
//		{
//		  case 4:LED_T();break;
//			case 3:Lcd_Show_Photo(0,40,100,100,gImage_photo);break;
//			case 5:LED_T();break;
//			case 2:Gui_DrawFont_GBK16(0,0,RED,WHITE,(u8*)"李佳");break;
//		}
//	 }
 
	
	
	

//		switch (Get_KeyValue())
//		{
//			case 0:Gui_DrawFont_GBK16(6,20,RED,BLACK,"李佳") ;break;
//			case 3:Lcd_Show_Photo(0, 0, 1920, 1200,"gImage_lijia[4506] ");break;
//			
//		}
		
//		if( Key_Run[0]> Key_Run[1])
//		{
//			Key_Run[0]= 0;
//			switch (Get_KeyValue())
//			{
//	    case 2:LED_T();break;
//	    case 3:LED_T();break;
//			case 4:LED_T();break;
//			case 5:LED_T();break;
//			}   
//	 

//		}
//	}
	
			
//	switch (Get_KeyValue())
//		{
//			case 0: led_breath(3000,10);break;
//			case 3: led_breath(3000,20);break;
//			case 4: led_breath(3000,30);break;
//			case 5: led_breath(3000,100);break;
//		default: led_breath(3000,200);break;
//		}
		
		
		
		
//		if(Led_Run[0] > Led_Run[1])
//		{
//			Led_Run[0] = 0;
//			LED_T();
//		}
	



