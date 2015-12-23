/******************************************************************************
*						文件名：	helper.h	
*                       文件描述：	本文件为系统的功能小函数 
*                       作者：		程敏
*						创建时间： 	2013-8-1
******************************************************************************/

#ifndef __HELPER_H__
#define __HELPER_H__

//#include "config.h"
#include "..\Include\OS_CPU.H"



void delay_us(INT16U time);
void delay_ms(INT16U time);
void delay_ns(INT16U time);
void myitoa(unsigned char * buffer,unsigned char num);


#endif

