//////////////////////////////////////////////////////////////////////////////////	 

//  功能描述   : OLED 4接口
//
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P1.5（SCL）
//              D1   P1.4（SDA）
//              ----------------------------------------------------------------
//******************************************************************************/
#include <msp430.h>
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  
#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0


//sbit OLED_SCL=P1^0;//时钟 D0（SCLK�
//#define
//sbit OLED_SDIN=P1^1;//D1（MOSI） 数据


//#define OLED_CS_Clr()  OLED_CS=0
//#define OLED_CS_Set()  OLED_CS=1
//
//#define OLED_RST_Clr() OLED_RST=0
//#define OLED_RST_Set() OLED_RST=1
//
//#define OLED_DC_Clr() OLED_DC=0
//#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() P1DIR |= BIT5;P1OUT &= ~BIT5
#define OLED_SCLK_Set() P1DIR |= BIT5;P1OUT |= BIT5

#define OLED_SDIN_Clr() P1DIR |= BIT4;P1OUT &= ~BIT4
#define OLED_SDIN_Set() P1DIR |= BIT4;P1OUT |= BIT4





//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
//-----------------OLED端口定义----------------

void delay_ms(unsigned int ms);


//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void dis_bmp(unsigned int high, unsigned int width, unsigned int *p,char value);
void Delay_50ms(unsigned int Del_50ms);

void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack();
#endif  
	 



