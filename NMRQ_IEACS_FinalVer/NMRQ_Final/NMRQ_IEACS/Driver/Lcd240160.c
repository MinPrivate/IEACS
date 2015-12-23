#include <lpc2103.h>
#include "..\Include\helper.h"
#include "..\Include\LCD240160.h"


void LCD_Init(void)
{
	PINSEL0 = PINSEL0&0xFFFFFF00;
	IODIR |= (0x1<<24)|(0x1<<25)|(0x1<<26)|(0xF<<16)|(0x3F<<2);
	H_LCD_RES;
}
void  LCD_CheckBusy(void)
{
	INT8U ret;
	INT32U TEMP;
	do
	{
		ret = 0x00;

		IOCLR |= LCD_DATA;

		IODIR &= ~LCD_DATA;
		IOSET |= LCD_WR; 
		IOCLR = (LCD_RD | LCD_CS | LCD_A0);
		delay_ns(2);
		TEMP = IOPIN;
		H_LCD_RD;
		IOSET |= LCD_CS;
		H_LCD_RD;
		IODIR |= LCD_DATA;			
		TEMP = (((TEMP&0x3F)<<2)|((((TEMP>>6)&0x3)<<25)));;
		ret	= TEMP & 0x000000ff;
	}
	while((ret&0x40) != 0);
}
void Lcd_WriteCMD(unsigned char cmd)
{
	unsigned long command;
	command = (unsigned long)cmd;
	command = ((command&0x3F)<<2)|((((command>>6)&0x3)<<25));
	IOCLR = LCD_DATA;
	IOSET = command;
	H_LCD_A0;
	L_LCD_CS;
	H_LCD_RD;
	L_LCD_WR;
	delay_ns(2); 
	H_LCD_WR;
	H_LCD_A0;
	H_LCD_CS;
	
}

void LCD_WriteData(unsigned char data)
{
	unsigned long a;
	a = (unsigned long)data;
	a = (((data&0x3F)<<2)|((((data>>6)&0x3)<<25)));
	IOCLR = LCD_DATA;
	IOSET = a;
	//LCD_CheckBusy();
	L_LCD_A0;
	L_LCD_CS;
	H_LCD_RD;
	L_LCD_WR;
	delay_ns(2);
	H_LCD_WR;
	H_LCD_A0;
	H_LCD_CS;
}

unsigned char  LCD_ReadData(void)
{
	unsigned long temp;
	unsigned char ret;
	IOCLR = LCD_DATA;
	IODIR &= ~LCD_DATA;
	H_LCD_A0;
	L_LCD_CS;
	L_LCD_RD;
	H_LCD_WR;
	delay_ns(1);
	temp = IOPIN;
	H_LCD_RD;
	H_LCD_CS;
	IODIR |= ((0x3<<25)|(0x3F<<2));
	temp = (((temp>>25)&0x3)<<6)|((temp>>2)&0x3F);
	ret = (unsigned char)temp;
	return ret;
}

void LCD_SetCursor(unsigned char  x,unsigned char  y)
{
	Lcd_WriteCMD(0x46);
	LCD_WriteData(x);
	LCD_WriteData(y);
}

void LCD_Reset(void)
{

	H_LCD_RES;
	delay_ms(3);
	L_LCD_A0;
	H_LCD_WR;
	H_LCD_RD;
	H_LCD_CS;
	L_LCD_RES;
	delay_ms(200);
	H_LCD_RES;
	delay_ms(500);
	
}



