/******************************************************************************
*						文件名：	helper.c	
*                       文件描述：	本文件为系统的功能小函数 
*                       作者：		程敏
*						创建时间： 	2013-8-1
******************************************************************************/
#include "..\Include\helper.h"

void delay_us(INT16U time)
{   
	INT32U TEMP;  
	do
	{
		time--;
		for(TEMP = 7 ;TEMP > 1; TEMP--)
		{
			;
		}
	}	
	while (time>1);
}

void delay_ms(INT16U time)
{     
	INT32U TEMP;
	do
	{
		time--;
		for(TEMP = 0; TEMP < 5570; TEMP++)
		{
			;
		}
	}	
	while (time>1);
}		
void delay_ns(INT16U time)
{
	for(;time!=0;time--);
}

void myitoa(unsigned char * buffer,unsigned char num)
{
	unsigned char temp,i;
	unsigned char buf[3];
	temp = num;
	for(i = 3;i != 0;i--)
	{
		buf[i-1] = temp%10;
		temp = temp/10;
	}
	for(i = 0; i < 3;i++)
	{
		buffer[i] = buf[i] + '0';
	}
	
}

