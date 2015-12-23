#include <lpc2103.h>
#include "helper.h"
#include "config.h"
#include "zimo.h"

#define LCD_A0 (0x1<<18)
#define LCD_WR (0x1<<16)
#define LCD_CS (0x1<<24)
#define LCD_RD (0x1<<17)
#define LCD_RES (0x1<<19)
#define LCD_DATA ((0x3<<25)|(0x3F<<2))

#define H_LCD_A0 (IOSET = LCD_A0)
#define L_LCD_A0 (IOCLR = LCD_A0)
#define H_LCD_WR (IOSET = LCD_WR)
#define L_LCD_WR (IOCLR = LCD_WR)
#define H_LCD_CS (IOSET = LCD_CS)
#define L_LCD_CS (IOCLR = LCD_CS)
#define H_LCD_RD (IOSET = LCD_RD)
#define L_LCD_RD (IOCLR = LCD_RD)
#define H_LCD_RES (IOSET = LCD_RES)
#define L_LCD_RES (IOCLR = LCD_RES)
#define Dis_X_MAX 239
#define Dis_Y_MAX 159
#define	PARAP9	  0x1e
#define SUCCESS   1
#define FAULT     0

void LCD_WriteCommand(INT8U cmd);
void LCD_WriteData(INT8U data);
INT8U  LCD_ReadData(void);
void LCD_Init(void);
void LCD_SetCursor(INT8U  x,INT8U  y);
void LCD_Clear(void);
void LCD_Displaybmp(const INT8U  *putbmp);
void LCD_WriteLine(INT8U s_x,INT8U s_y,INT8U e_x,INT8U e_y);
void LCD_WriteDot(INT8U dot_x,INT8U dot_y);
void LCD_WriteRectangle(INT8U left, INT8U top, INT8U right, INT8U bottom,INT8U Mode);
void LCD_PutHZ(INT8U col,INT8U row,INT8U HZcode);
void LCD_Locatexy(INT8U x,INT8U y);
//========================================================================
// 函数: void LCD_Init(void)
// 描述: LCD初始化函数
// 参数: 无
// 返回: 无
// 版本:
//========================================================================
void LCD_Init(void)
{
	PINSEL0 = PINSEL0&0xFFFFFF00;
	IODIR |= (0x1<<24)|(0x1<<25)|(0x1<<26)|(0xF<<16)|(0x3F<<2);
	H_LCD_RES;
	//system set
	LCD_WriteCommand(0x40);
	LCD_WriteData(0x10); //p1
	LCD_WriteData(0x07);  //p2
	LCD_WriteData(0x07); //p3
	LCD_WriteData(29);   //p4
	LCD_WriteData(90);  //p5
	LCD_WriteData(159);  //p6
	LCD_WriteData(30);  //p7
	LCD_WriteData(0);  //p8
	//scroll set
	LCD_WriteCommand(0x44);  
	LCD_WriteData(0x0);   //p1 sad1l
	LCD_WriteData(0x0);   //p2 sad1h
	LCD_WriteData(160);  //p3 sl1
	LCD_WriteData(0x58);  //p4 sad2l
	LCD_WriteData(0x02);  //p5 sad2h
	LCD_WriteData(160);  //p6 sl2
	LCD_WriteData(0x0);   //p7
	LCD_WriteData(0x0);   //p8
	LCD_WriteData(0x0);   //p9
	LCD_WriteData(0x0);   //p10
	//H D O T  S C R
	LCD_WriteCommand(0x5A);
	LCD_WriteData(0x0);
	//ovly set
	LCD_WriteCommand(0x5b);
	LCD_WriteData(0x0c);  //p1  默认00
	//display off
	LCD_WriteCommand(0x58);
	LCD_WriteData(0x06);
	//display on 
	LCD_WriteCommand(0x59);
}
//========================================================================
// 函数: void LCD_Clear(void)
// 描述: LCD清屏函数
// 参数: 无
// 返回: 无
// 版本:
//========================================================================
void LCD_Clear(void)
{
	INT32U i = 32765;
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
	for(;i>0;i--)
	{
	LCD_WriteCommand(0x42);
	LCD_WriteData(0x00);	
	}
	LCD_WriteCommand(0x40);
	LCD_WriteData(0x10); //p1
	LCD_WriteData(0x07);  //p2
	LCD_WriteData(0x07); //p3
	LCD_WriteData(29);   //p4
	LCD_WriteData(90);  //p5
	LCD_WriteData(159);  //p6
	LCD_WriteData(30);  //p7
	LCD_WriteData(0);  //p8
	//scroll set
	LCD_WriteCommand(0x44);  
	LCD_WriteData(0x0);   //p1 sad1l
	LCD_WriteData(0x0);   //p2 sad1h
	LCD_WriteData(160);  //p3 sl1
	LCD_WriteData(0x58);  //p4 sad2l
	LCD_WriteData(0x02);  //p5 sad2h
	LCD_WriteData(160);  //p6 sl2
	LCD_WriteData(0x0);   //p7
	LCD_WriteData(0x0);   //p8
	LCD_WriteData(0x0);   //p9
	LCD_WriteData(0x0);   //p10
	//H D O T  S C R
	LCD_WriteCommand(0x5A);
	LCD_WriteData(0x0);
	//ovly set
	LCD_WriteCommand(0x5b);
	LCD_WriteData(0x0c);  //p1  默认00
	//display off
	LCD_WriteCommand(0x58);
	LCD_WriteData(0x06);
	//display on 
	LCD_WriteCommand(0x59);
}


//========================================================================
// 函数: void LCD_Locatexy(INT8U x,INT8U y)
// 描述: 定位一个点,将LCD坐标中的点转换为显存中的对应的值
// 参数: x X 轴坐标 y Y 轴坐标  
// 返回: 无
// 版本:
//========================================================================
void LCD_Locatexy(INT8U x,INT8U y)
{
	INT32U  temp;
	temp = (INT32U )y*PARAP9+x;
	LCD_WriteCommand(0x46);
	LCD_WriteData( (INT8U)(temp & 0xff) );
	LCD_WriteData( (INT8U)(temp /256 ) );
}
//========================================================================
// 函数: void LCD_CheckBusy(void)
// 描述: 检查LCD忙函数
// 参数: 无
// 返回: 无
// 版本:
//========================================================================
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
//========================================================================
// 函数: void LCD_WriteCommand(INT8U cmd)
// 描述: 向LCD寄存器中写入值
// 参数: cmd 写入寄存器的值
// 返回: 无
// 版本:
//========================================================================
void LCD_WriteCommand(INT8U cmd)
{
	INT32U command;
	command = (INT32U)cmd;
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
//========================================================================
// 函数: void LCD_WriteData(INT8U data)
// 描述: 向LCD缓冲区RAM中写入一个自己的数据
// 参数: date 写入RAM的值
// 返回: 无
// 版本:
//========================================================================
void LCD_WriteData(INT8U data)
{
	INT32U a;
	a = (INT32U)data;
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
//========================================================================
// 函数: INT8U  LCD_ReadData(void)
// 描述: 从LCD显示存储器RAM中读出值
// 参数: 无
// 返回: ret  从显示存储器RAM中读出的一个字节的数据
// 版本:
//========================================================================
INT8U  LCD_ReadData(void)
{
	INT32U temp;
	INT8U ret;
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
	ret = (INT8U)temp;
	return ret;
}
//========================================================================
// 函数: void LCD_SetCursor(INT8U  x,INT8U  y)
// 描述: 设置光标的地址
// 参数: x 光标指针低8位  y 光标指针高8位
// 返回: 无
// 版本:
//========================================================================
void LCD_SetCursor(INT8U  x,INT8U  y)
{
	LCD_WriteCommand(0x46);
	LCD_WriteData(x);
	LCD_WriteData(y);
}

//========================================================================
// 函数: void LCD_WriteDot(INT8U dot_x,INT8U dot_y)
// 描述: 在LCD 的真实坐标系上的X、Y 点绘点
// 参数: x X 轴坐标
// 		 y Y 轴坐标
// 返回: 无
// 版本:
//========================================================================
void LCD_WriteDot(INT8U dot_x,INT8U dot_y)
{
	INT8U i,j,m,n;
	m = dot_x;
	n = dot_y;
	LCD_WriteCommand(0x4c);
	LCD_WriteCommand(0x46);
	LCD_WriteData(0);
	LCD_WriteData(0);
	LCD_WriteCommand(0x42);
	for(i=0;i<160/n;i++)
	{
		for(j=0;j<30*n;j++) LCD_WriteData(m);
		m=~m;
	}
}
//========================================================================
// 函数: void LCD_Displaybmp (INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张240X160图片
// 参数: *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Displaybmp (const INT8U  *putbmp)
{
	INT8U X;
	INT8U i,j;
	X=0;
	LCD_WriteCommand(0x4c);
	LCD_WriteCommand(0x46);
	LCD_WriteData(0);
	LCD_WriteData(0);
	LCD_WriteCommand(0x42);
	for(i=0;i<160;i++)
	{
		for(j=0;j<30;j++)
		{
			LCD_WriteData(putbmp[X]);
			X++;
		}
	}
}
//========================================================================
// 函数: void LCD_Display72bmp (INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张72X16图片
// 参数: *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display72bmp (INT8U row,INT8U col,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(row,col);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<9;j++)
		{
			LCD_WriteData(putbmp[m]);
			m++;
		}
		col++;
	}
}
//========================================================================
// 函数: void LCD_Display64bmp (INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张64X16图片
// 参数: *putbmp 图片数组地址指针 uirow  横坐标  uicol 纵坐标
// 返回: 无
// 版本:
//========================================================================
void LCD_Display64bmp (INT8U row,INT8U col,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(row,col);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(putbmp[m]);
			m++;
		}
		col++;
	}
}
//========================================================================
// 函数: void LCD_Display64bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张64X16图片取反
// 参数: uirow  横坐标  uicol 纵坐标
//		 *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display64bmpf (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(~putbmp[m]);
			m++;
		}
		uicol++;
	}
}
//========================================================================
// 函数: void LCD_Display80bmp (INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张80X16图片
// 参数: *putbmp 图片数组地址指针 uirow  横坐标  uicol 纵坐标
// 返回: 无
// 版本:
//========================================================================
void LCD_Display80bmp (INT8U row,INT8U col,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(row,col);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<10;j++)
		{
			LCD_WriteData(putbmp[m]);
			m++;
		}
		col++;
	}
}
//========================================================================
// 函数: void LCD_Display80bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张80X16图片的取反图片
// 参数: *putbmp 图片数组地址指针 uirow  横坐标  uicol 纵坐标
// 返回: 无
// 版本:
//========================================================================
void LCD_Display80bmpf (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<10;j++)
		{
			LCD_WriteData(~putbmp[m]);
			m++;
		}
		uicol++;
	}
}
//========================================================================
// 函数: void LCD_Display48bmp (INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张48X16图片
// 参数: *putbmp 图片数组地址指针 uirow  横坐标  uicol 纵坐标
// 返回: 无
// 版本:
//========================================================================
void LCD_Display48bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<6;j++)
		{
			LCD_WriteData(putbmp[m]);
			m++;
		}
		uicol++;
	}
}
//========================================================================
// 函数: void LCD_Display48bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张48X16图片的取反图片
// 参数: *putbmp 图片数组地址指针 uirow  横坐标  uicol 纵坐标
// 返回: 无
// 版本:
//========================================================================
void LCD_Display48bmpf (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<6;j++)
		{
			LCD_WriteData(~putbmp[m]);
			m++;
		}
		uicol++;
	}
}
//========================================================================
// 函数: void LCD_Display32bmp (INT8U row,INT8U col,const INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张32X16图片
// 参数: *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display32bmp (INT8U row,INT8U col,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(row,col);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<4;j++)
		{
			LCD_WriteData(putbmp[m]);
			m++;
		}
		col++;
	}
}
//========================================================================
// 函数: void LCD_Display32bmpf (INT8U row,INT8U col,const INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张32X16图片的取反
// 参数: *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display32bmpf (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<4;j++)
		{
			LCD_WriteData(~putbmp[m]);
			m++;
		}
		uicol++;
	}
}
//========================================================================
// 函数: void LCD_Display16bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张40X21图片	   专门用于显示返回加框按钮
// 参数: uirow  图片起始地址横坐标
//		 uicol  图片起始地址纵坐标
//		 *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display40bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<21;i++)
	{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<5;j++)
		{
			LCD_WriteData(putbmp[m]);
			m++;
		}
		uicol++;
	}
}
//========================================================================
// 函数: void LCD_Display16bmpf (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张40X21图片的取反	专门用于显示返回加框按钮
// 参数: uirow  图片起始地址横坐标
//		 uicol  图片起始地址纵坐标
//		 *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display40bmpf (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<21;i++)
	{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<5;j++)
		{
			LCD_WriteData(~putbmp[m]);
			m++;
		}
		uicol++;
	}
}
//========================================================================
// 函数: void LCD_Display16bmp (INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张16X16图片
// 参数: *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display16bmp (INT8U row,INT8U col,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(row,col);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(putbmp[m]);
			m++;
		}
		col++;
	}
}
//========================================================================
// 函数: void LCD_Display16bmpf (INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张16X16图片取反
// 参数: *putbmp 图片数组地址指针
// 返回: 无
// 版本:
//========================================================================
void LCD_Display16bmpf (INT8U row,INT8U col,const INT8U  *putbmp)
{
	INT8U m;
	INT8U i,j;
	m=0;
	for(i=0;i<16;i++)
	{
		LCD_Locatexy(row,col);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(~putbmp[m]);
			m++;
		}
		col++;
	}
}
//==============================================================================
// 函数: void LCD_PutHZ(INT8U col,INT8U row,INT8U HZcode)
// 描述: 以横坐标为col,纵坐标为row的点为起点显示一个汉字 汉字大小为22X22
// 参数: col X 轴坐标 row Y 轴坐标  HZcode 字符在字符库中的偏移量
// 返回: 无
// 版本:
//========================================================================
void LCD_PutHZ(INT8U uicol,INT8U uirow,const INT8U uiHZcode)
{
	INT8U i,j;
	INT32U  x;
	x = 0x42*uiHZcode;
	LCD_WriteCommand(0x4c);
	for(i=0;i<22;i++)
	{
		LCD_Locatexy(uicol,uirow);
		LCD_WriteCommand(0x42);
		for(j=0;j<3;j++)
		{
			LCD_WriteData(bmp_HZTableKG[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// 函数: void LCD_PutSHZ(INT8U col,INT8U row,INT8U Hzcode)
// 描述: 以横坐标为col,纵坐标为row的点为起点显示一个汉字 汉字大小为14X12
// 参数: col X 轴坐标 row Y 轴坐标  HZcode 字符在字符库中的偏移量
// 返回: 无
// 版本:
//========================================================================
void LCD_PutSHZ(INT8U uicol,INT8U uirow,const INT8U uiHzcode)
{
	INT8U i,j;
	INT32U  x;
	x = 0x42*uiHzcode;
	LCD_WriteCommand(0x4c);
	for(i=0;i<22;i++)
	{
		LCD_Locatexy(uicol,uirow);
		LCD_WriteCommand(0x42);
		for(j=0;j<3;j++)
		{
			LCD_WriteData(bmp_HZTable[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// 函数: void LCD_PutNumberOnMS(INT8U uicol,INT8U uirow,INT8U NumberOnMS)
// 描述: 在主界面显示时间块放入一个数字
// 参数: col X 轴坐标 row Y 轴坐标   NumberOnMS 字符在字符库中的偏移量
// 返回: 无
// 版本:
//========================================================================
void LCD_PutNumberOnMS(INT8U uicol,INT8U uirow,const INT8U uinumberonMS)
{
	INT8U i,j;
	INT32U  x;
	x = 0x3a*uinumberonMS;
	for(i=0;i<29;i++)
	{
		LCD_Locatexy(uicol,uirow);
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_zds[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// 函数: void LCD_PutWeek(INT8U col,INT8U row,INT8U uiweek)
// 描述: 在主界面显示星期块放入一个中文数字
// 参数: col X 轴坐标 row Y 轴坐标  uiweek 字符在字符库中的偏移量
// 返回: 无
// 版本:
//========================================================================
void LCD_PutWeek(INT8U uicol,INT8U uirow,const INT8U uiweek)
{
	INT8U i,j;
	INT32U  x;
	x = 0x18*uiweek;				 //计算出week在数组中起始位置
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //定位起始地址
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_week[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// 函数: void LCD_PutNumberOnData(INT8U uicol,INT8U uirow,INT8U uinumberondata)
// 描述: 放一个8X16的数字
// 参数: uicol X 轴坐标 uirow Y 轴坐标   uinumberondata 字符在字符库中的偏移量
// 返回: 无
// 版本:
//========================================================================
void LCD_PutNumberOnData(INT8U uicol,INT8U uirow,const INT8U uinumberondata)
{
	INT8U i,j;
	INT32U  x;
	x = 0x0c*uinumberondata;				 //计算出uinumberondata在数组中起始位置
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //定位起始地址
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<1;j++)
		{
			LCD_WriteData(bmp_zsr[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// 函数: void LCD_PutNumberOnDataf(INT8U uicol,INT8U uirow,INT8U uinumberondata)
// 描述: 放一个8X16的数字的取反
// 参数: uicol X 轴坐标 uirow Y 轴坐标   uinumberondata 字符在字符库中的偏移量
// 返回: 无
// 版本:
//========================================================================
void LCD_PutNumberOnDataf(INT8U uicol,INT8U uirow,const INT8U uinumberondata)
{
	INT8U i,j;
	INT32U  x;
	x = 0x0c*uinumberondata;				 //计算出uinumberondata在数组中起始位置
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //定位起始地址
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<1;j++)
		{
			LCD_WriteData(~bmp_zsr[x]);
			x++;
		}
		uirow++;
	}
}
////==============================================================================
//// 函数: void LCD_PutBlkOnScreen(INT8U uicol,INT8U uirow)
//// 描述: 放一个8X16的黑块
//// 参数: uicol X 轴坐标 uirow Y 轴坐标   
//// 返回: 无
//// 版本:
////========================================================================
//void LCD_PutBlockOnScreen(INT8U uicol,INT8U uirow)
//{
//	INT8U i,j;
//	INT32U  x;
//	x=0;				 //计算出uinumberondata在数组中起始位置
//	for(i=0;i<16;i++)
//	{
//		LCD_Locatexy(uicol,uirow);   //定位起始地址
//		LCD_WriteCommand(0x4c);
//		LCD_WriteCommand(0x42);
//		for(j=0;j<1;j++)
//		{
//			LCD_WriteData(bmp_hk[x]);
//			x++;
//		}
//		uirow++;
//	}

//========================================================================
// 函数: INT16U LCD_PowerOn()
// 描述: 开机显示画面
// 参数: 无  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
INT8U LCD_PowerOn()
{
	LCD_PutHZ(3,48,0); //显示智
	LCD_PutHZ(6,48,1); //显示能
	LCD_PutHZ(9,48,2); //显示家
	LCD_PutHZ(12,48,3);//显示电
	LCD_PutHZ(15,48,4);//显示控
	LCD_PutHZ(18,48,5);//显示制
	LCD_PutHZ(21,48,6);//显示系
	LCD_PutHZ(24,48,7);//显示统
	LCD_PutHZ(9,71,8); //显示欢
	LCD_PutHZ(12,71,9);//显示迎
	LCD_PutHZ(15,71,10);//显示您
	LCD_PutHZ(18,71,15);//显示！
	return 1;
}
//========================================================================
// 函数: INT8U LCD_PowerOff()
// 描述: 显示关机页面
// 参数: 无
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
INT8U LCD_PowerOff()
{
	LCD_PutHZ(3,48,0); //显示智
	LCD_PutHZ(6,48,1); //显示能
	LCD_PutHZ(9,48,2);//显示家
	LCD_PutHZ(12,48,3);//显示电
	LCD_PutHZ(15,48,4);//显示控
	LCD_PutHZ(18,48,5);//显示制
	LCD_PutHZ(21,48,6);//显示系
	LCD_PutHZ(24,48,7);//显示统
	LCD_PutHZ(3,71,8); //显示欢
	LCD_PutHZ(6,71,9); //显示迎
	LCD_PutHZ(9,71,10);//显示您
	LCD_PutHZ(12,71,11);//显示下
	LCD_PutHZ(15,71,12);//显示次
	LCD_PutHZ(18,71,13);//显示使
	LCD_PutHZ(21,71,14);//显示用
	LCD_PutHZ(24,71,15);//显示！
	return 1;	
}
//========================================================================
// 函数: INT8U LCD_DispalyMainScreen()
// 描述: 显示下位机端主界面
// 参数: 无
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DispalyMainScreen()
 {
 	INT8U m;
	INT8U i,j,col;
	////////////////还缺显示时间相关的函数//////////////////
	m=0;
	col=12;
	for(i=0;i<26;i++)				  //  显示分号分号分号分号分号分号分号分号分号分号分号分号
	{
		LCD_Locatexy(6,col);		  //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<1;j++)
		{
			LCD_WriteData(bmp_zf[m]);
			m++;
		}
		col++;
	}

	m=0;
	col=41;
	for(i=0;i<12;i++)				  //显示星期星期星期星期星期星期星期星期星期星期星期星期
	{
		LCD_Locatexy(4,col);		  //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<3;j++)
		{
			LCD_WriteData(bmp_xq[m]);
			m++;
		}
		col++;
	}
	m=0;
	col=55;
	for(i=0;i<12;i++)				  //显示年年年年年年
	{
		LCD_Locatexy(5,col);		  //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_n[m]);
			m++;
		}
		col++;
	}
	m=0;
	col=55;
	for(i=0;i<12;i++)				  //显示月月月月月月月月月
	{
		LCD_Locatexy(9,col);		  //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_y[m]);
			m++;
		}
		col++;
	}
	m=0;
	col=55;
	for(i=0;i<12;i++)				  //显示日日日日日日日日日日日
	{
		LCD_Locatexy(13,col);		  //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_r[m]);
			m++;
		}
		col++;
	}	
   ///////////////////////////////////////////////////////////
	m=0;
	col=16;
	for(i=0;i<19;i++)				  //显示主界面智能家电控制系统
	{
		LCD_Locatexy(13,col);		  //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<16;j++)
		{
			LCD_WriteData(bmp_znz[m]);
			m++;
		}
		col++;
	}
	
	m=0;
	col=38;
	for(i=0;i<14;i++)				 	//显示主界面温度字样
	{
		LCD_Locatexy(17,col);			//定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<6;j++)
		{
			LCD_WriteData(bmp_wd[m]);
			m++;
		}
		col++;
	}
	m=0;
	col=38;
	for(i=0;i<14;i++)				 	//显示主界面温度符号
	{
		LCD_Locatexy(25,col);			//定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_wdf[m]);
			m++;
		}
		col++;
	}
	m=0;							   //显示主界面光强字样
	col=55;
	for(i=0;i<14;i++)				 
	{
		LCD_Locatexy(17,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<6;j++)
		{
			LCD_WriteData(bmp_gq[m]);
			m++;
		}
		col++;
	}
	m=0;							   //显示主界面光强符号字样
	col=55;
	for(i=0;i<14;i++)				 
	{
		LCD_Locatexy(25,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<1;j++)
		{
			LCD_WriteData(bmp_gqf[m]);
			m++;
		}
		col++;
	}
    m=0;							   //显示主界面门灯字样
	col=80;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(3,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(bmp_md[m]);
			m++;
		}
		col++;
	}

	m=0;							   //显示主界面空调字样
	col=96;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(3,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(bmp_kt[m]);
			m++;
		}
		col++;
	}

	m=0;							   //显示主界面卧室灯字样
	col=80;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(16,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<10;j++)
		{
			LCD_WriteData(bmp_wsd[m]);
			m++;
		}
		col++;
	}
	

	m=0;							   //显示主界面热水器字样
	col=96;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(16,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<10;j++)
		{
			LCD_WriteData(bmp_rsq[m]);
			m++;
		}
		col++;
	}

	m=0;							   //显示主界面菜单设置字样
	col=119;
	for(i=0;i<24;i++)				 
	{
		LCD_Locatexy(3,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(bmp_cd[m]);
			m++;
		}
		col++;
	}

	m=0;							   //显示主界面电器设置字样
	col=119;
	for(i=0;i<24;i++)				 
	{
		LCD_Locatexy(17,col);		   //定位光标起点，row表示LCD屏上的横坐标，col表示LCD屏上的纵坐标
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(bmp_dq[m]);
			m++;
		}
		col++;
	}
	return 1;
 }
//========================================================================
// 函数: INT8U LCD_UpdateApplianceState(INT8U uiair_state,INT8U uiwaterh_state,INT8U uidoorl_state,INT8U uibedl_state)
// 描述: 更新下位机端电器状态信息
// 参数: uiair_state 空调状态信息 1或0；		  1为开，0为关
//		 uiwaterh_state 热水器状态信息 1或0
//		 uidoorl_state  门灯状态信息 1或0
//       uibedl_state	卧室灯状态信息 1或0
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
INT8U LCD_UpdateApplianceState (INT8U uidoorl_state,INT8U uibedl_state,INT8U uiair_state,INT8U uiwaterh_state)
{	
	if (uiair_state == 1)
	{
		LCD_Display16bmp(10,78,bmp_16y);//门灯状态开
	}
	if (uidoorl_state ==1)
	{
		LCD_Display16bmp(25,78,bmp_16y);//卧室灯状态开    
	}
	if (uiwaterh_state == 1 )
	{
		LCD_Display16bmp(10,93,bmp_16y);//空调状态开
	}
	if(uibedl_state == 1)
	{
		LCD_Display16bmp(25,93,bmp_16y);//热水器状态开
	}
	else
	{
	}
	return 1;
}
//========================================================================
// 函数: INT8U LCD_UpdateConnect(INT8U uiConnectdata)
// 描述: 显示远程已连接页面
// 参数: uiConnectdata 当前的PC端连接状态 1为连接 0为断开
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_UpdateConnect(INT8U uiConnectdata)
 {
 	INT8U m;
	INT8U i,j,col;
	m=0;
	col=0;
	if (uiConnectdata == 1 )		   //显示远程控制已连接
	{
		LCD_Display16bmp(0,0,bmp_9y);  //刷新状态图片	
		LCD_Display72bmp(2,0,bmp_yc);
	}
	else 
	{
	
	for(i=0;i<10;i++)				  //显示远程控制未连接
	{
		LCD_Locatexy(2,col);		  //定位光标起点
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<9;j++)
		{
			LCD_WriteData(bmp_ycw[m]);
			m++;
		}
		col++;
	}
	}
	return 	1;
 }	
//========================================================================
// 函数: INT8U LCD_UpdateTime(INT8U uihourfirst,INT8U uihoursecond,INT8U uiminutefirst,INT8U uiminutesecond)
// 描述: 更新主页面时间，日期
// 参数: uihourfirst 小时第一位
//       uihoursecond 小时第二位
//       uiminutefirst 分钟第一位
//		 uiminutesecond 分钟第二位	
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_UpdateTime(INT8U uihourfirst,INT8U uihoursecond,INT8U uiminutefirst,INT8U uiminutesecond)
 {
 	LCD_PutNumberOnMS(2,12,uihourfirst);
	LCD_PutNumberOnMS(4,12,uihoursecond);
	LCD_PutNumberOnMS(7,12,uiminutefirst);
	LCD_PutNumberOnMS(9,12,uiminutesecond);
	return 1;
 }
//========================================================================
// 函数: INT8U LCD_UpdateWeek(INT8U uiweek)
// 描述: 更新主页面星期几
// 参数: uiweek 星期几	
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_UpdateWeek(INT8U uiweek)
 {
 	LCD_PutWeek(7,41,uiweek);
	return 1;
 }
//===================================================================================================================================================================================================================================================
// 函数: INT8U LCD_UpdateDate(INT8U uiyearfirst,INT8U uiyearsecond,INT8U uiyearthird,INT8U uiyearforth,INT8U uimonthfirst,INT8U uimonthsecond,INT8U uidayfirst,INT8U uidaysecond)
// 描述: 更新主页面日期
// 参数: uinianfirst 年的第一位
//		 uiyearsecond 年的第二位
//		 uiyearthird  年的第三位
//		 uiyearforth 年的第四位
//		 uimonthfirst 月的第一位
//		 uimonthsecond 月的第二位
//		 uidayfirst 天的第一位
//		 uidaysecond 天的第二位
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//===================================================================================================================================================================================================================================================
 INT8U LCD_UpdateDate(INT8U uiyearfirst,INT8U uiyearsecond,INT8U uiyearthird,INT8U uiyearforth,INT8U uimonthfirst,INT8U uimonthsecond,INT8U uidayfirst,INT8U uidaysecond)
 {
 	LCD_PutNumberOnData(1,54,uiyearfirst);
	LCD_PutNumberOnData(2,54,uiyearsecond);
	LCD_PutNumberOnData(3,54,uiyearthird);
	LCD_PutNumberOnData(4,54,uiyearforth);
	LCD_PutNumberOnData(7,54,uimonthfirst);
	LCD_PutNumberOnData(8,54,uimonthsecond);
	LCD_PutNumberOnData(11,54,uidayfirst);
	LCD_PutNumberOnData(12,54,uidaysecond);
	return 1;
 }

//==========================================================================
// 函数: INT8U LCD_UpdateCircumstance(INT8U uitem,INT8U uihum)
// 描述: 更新主界面环境信息页面
// 参数: uitem   温度信息   uihum  环境信息  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//===========================================================================
INT8U LCD_UpdateCircumstance(INT8U uitemfirst,INT8U uitemsecond,INT8U uihumfirst,INT8U uihumsecond)
{
	LCD_PutNumberOnData(22,37,uitemfirst);
	LCD_PutNumberOnData(23,37,uitemsecond);
	LCD_PutNumberOnData(22,55,uihumfirst);
	LCD_PutNumberOnData(23,55,uihumsecond);
	return 1;
}
//===================================================================================================================================================================================================================================================
// 函数: INT8U LCD_UpdateClockSetDate(INT8U uicsyearfirst,INT8U uicsyearsecond,INT8U uicsyearthird,INT8U uicsyearforth,INT8U uicsmonthfirst,INT8U uicsmonthsecond,INT8U uicsdayfirst,INT8U uicsdaysecond)
// 描述: 更新时钟界面日期设置
// 参数: uinianfirst 年的第一位	 
//		 uicsyearsecond 年的第二位 	 
//		 uicsyearthird 年的第三位	 
//       uicsyearforth 年的第四位
//       uicsmonthfirst 月的第一位
//       uicsmonthsecond 月的第二位
//       uicsdayfirst    天的第一位
//		 uicsdayfirst    天的第二位
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//===================================================================================================================================================================================================================================================
 INT8U LCD_UpdateClockSetDate(INT8U uicsyearfirst,INT8U uicsyearsecond,INT8U uicsyearthird,INT8U uicsyearforth,INT8U uicsmonthfirst,INT8U uicsmonthsecond,INT8U uicsdayfirst,INT8U uicsdaysecond)
 {
 	LCD_PutNumberOnData(10,48,uicsyearfirst);
	LCD_PutNumberOnData(11,48,uicsyearsecond);
	LCD_PutNumberOnData(12,48,uicsyearthird);
	LCD_PutNumberOnData(13,48,uicsyearforth);
	LCD_PutNumberOnData(16,48,uicsmonthfirst);
	LCD_PutNumberOnData(17,48,uicsmonthsecond);
	LCD_PutNumberOnData(20,48,uicsdayfirst);
	LCD_PutNumberOnData(21,48,uicsdaysecond);
	return 1;
}
//========================================================================
// 函数: INT8U  LCD_UpdateClockSetTime(INT8U uicshourfirst,INT8U uicshoursecond,INT8U uicsminutefirst,INT8U uicsminutesecond)
// 描述: 更新时钟设置时间
// 参数: uicshourfirst 小时第一位
//       uicshoursecond 小时第二位
//       uicsminutefirst 分钟第一位
//		 uicsminutesecond 分钟第二位	
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_UpdateClockSetTime(INT8U uicshourfirst,INT8U uicshoursecond,INT8U uicsminutefirst,INT8U uicsminutesecond)
 {
 	LCD_PutNumberOnData(10,65,uicshourfirst);
	LCD_PutNumberOnData(11,65,uicshoursecond);
	LCD_PutNumberOnData(14,65,uicsminutefirst);
	LCD_PutNumberOnData(15,65,uicsminutesecond);
	return 1;
 }
//==========================================================================
// 函数: INT8U LCD_UpdateTemSetTem(INT8U uitemsetfirst,INT8U uitemsetsecond)
// 描述: 更新空调和热水器信息页面温度设定
// 参数: uitemsetfirst_air  温度设置第一位   uitemsetsecond_air  温度设置第二位 
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//===========================================================================
INT8U LCD_UpdateTemSetTem(INT8U uitemsetfirst,INT8U uitemsetsecond)
{
	LCD_PutNumberOnData(14,52,uitemsetfirst_air);
	LCD_PutNumberOnData(15,52,uitemsetsecond_air);
	return 1;
}

//==========================================================================
// 函数: INT8U LCD_UpdateTimingSet(INT8U uitshourfirst,INT8U uitshoursecond,INT8U uitsminutefirst,INT8U uitsminutesecond,INT8U uitimingsetswitch)
// 描述: 更新电器信息页面定时时间
// 参数: uitshourfirst   定时时间小时第一位   uitshoursecond  定时时间小时第二位  uitsminutefirst 定时分钟第一位  uitsminutesecond 定时分钟第二位  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//===========================================================================
INT8U LCD_UpdateTimingSet(INT8U uitshourfirst,INT8U uitshoursecond,INT8U uitsminutefirst,INT8U uitsminutesecond,INT8U uitimingsetswitch)
{
	LCD_PutNumberOnData(10,84,uitshourfirst);
	LCD_PutNumberOnData(11,84,uitshoursecond);
	LCD_PutNumberOnData(14,84,uitsminutefirst);
	LCD_PutNumberOnData(15,84,uitsminutesecond);
	if ( uitimingsetswitch ==1 )
	{
		LCD_Display16bmp(19,84,bmp_dqk);
	}
	else 
	{
		LCD_Display16bmp(19,84,bmp_dqg);
	}
	return 1;
}
//========================================================================
// 函数: INT8U LCD_DisplayMenuSet()
// 描述: 显示菜单设置页面
// 参数: 无  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayMenuSet()
 {
 	LCD_Display80bmp(11,29,bmp_m1);
	LCD_Display80bmp(11,45,bmp_m2);
	LCD_Display80bmp(11,61,bmp_m3);
	LCD_Display80bmp(11,77,bmp_m4);
	LCD_Display32bmp(4,120,bmp_qd);
	LCD_Display32bmp(22,120,bmp_fhjk);
	return 	1;
 }

//========================================================================
// 函数: INT8U LCD_DisplayModeSelect()
// 描述: 显示模式选择页面
// 参数: 无  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayModeSelect()
 {
 	LCD_Display80bmp(11,29,bmp_ms1);
	LCD_Display80bmp(11,45,bmp_ms2);
	LCD_Display80bmp(11,61,bmp_ms3);
	LCD_Display80bmp(11,77,bmp_ms4);
	LCD_Display32bmp(4,120,bmp_qd);
	LCD_Display32bmp(22,120,bmp_fhjk);
	return 	1;
 }
//========================================================================
// 函数: INT8U LCD_DisplayTimeSet()
// 描述: 显示时钟设置页面
// 参数: 无  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayTimeSet()
 {
 	LCD_Display48bmp(5,48,bmp_shrq); 		 //显示日期：日期：日期：
	LCD_Display16bmp(14,48,bmp_dqn); 		 //显示年
	LCD_Display16bmp(18,48,bmp_dqy);		 //显示月
	LCD_Display16bmp(22,48,bmp_dqr);		 //显示日
	LCD_Display48bmp(5,65,bmp_shsj);		 //显示时间;时间;时间;
	LCD_Display16bmp(12,65,bmp_dqs);		 //显示时
	LCD_Display16bmp(16,65,bmp_dqf);		 //显示分
	LCD_Display32bmp(4,120,bmp_qd);
	LCD_Display32bmp(22,120,bmp_fhjk);
	return 	1;
 }
//========================================================================
// 函数: INT8U LCD_DisplayApplianceSet()
// 描述: 显示电器设置页面  即为显示选择哪个电器的页面
// 参数: 无  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayApplianceSet()
 {
 	LCD_Display48bmp(11,29,bmp_as1);
	LCD_Display64bmp(11,45,bmp_as2);
	LCD_Display48bmp(11,61,bmp_as3);
	LCD_Display64bmp(11,77,bmp_as4);
	LCD_Display32bmp(4,120,bmp_qd);
	LCD_Display32bmp(22,120,bmp_fhjk);
	return 	1;
 }
//========================================================================
// 函数: INT8U LCD_DisplayDoorl(INT8U uidoorl_state_display)
// 描述: 显示门灯页面
// 参数: uidoorl_state_disaplay    表示门灯电器当前的状态
//       不能直接读取系统状态表 进入电器显示界面后会把电器当前状态赋给这个变量  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayDoorl(INT8U uidoorl_state_display)
 {
 	LCD_Display32bmp(9,20,bmp_dqmd);
	LCD_Display80bmp(9,36,bmp_dqdqzt);
	if (uidoorl_state_display == 1)
	{
		LCD_Display16bmp(18,36,bmp_dqk);		
	}
	else 
	{
		LCD_Display16bmp(18,36,bmp_dqg);		
	}
//	LCD_Display48bmp(7,52,bmp_mdgq);
//	LCD_Display80bmp(7,68,bmp_mddssz);
	LCD_Display80bmp(9,68,bmp_dqdssj);
	LCD_Display16bmp(12,84,bmp_dqs);		 //显示时
	LCD_Display16bmp(16,84,bmp_dqf);		 //显示分
	LCD_Display32bmp(4,115,bmp_qd);
	LCD_Display32bmp(22,115,bmp_fhjk);
	return 	1;
 }
//========================================================================
// 函数: INT8U LCD_DisplayBedl(INT8U uibedl_state_display)
// 描述: 显示卧室灯页面
// 参数: uibedl_state_display 卧室灯电器当前的状态  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayBedl(INT8U uibedl_state_display)
 {
 	LCD_Display48bmp(9,20,bmp_dqwsd);
	LCD_Display80bmp(9,36,bmp_dqdqzt);
	if (uibedl_state_display == 1)
	{
		LCD_Display16bmp(18,36,bmp_dqk);		
	}
	else 
	{
		LCD_Display16bmp(18,36,bmp_dqg);		
	}
//	LCD_Display48bmp(7,52,bmp_mdgq);
//	LCD_Display80bmp(7,68,bmp_mddssz);
	LCD_Display80bmp(9,68,bmp_dqdssj);
	LCD_Display16bmp(12,84,bmp_dqs);		 //显示时
	LCD_Display16bmp(16,84,bmp_dqf);		 //显示分
	LCD_Display32bmp(4,115,bmp_qd);
	LCD_Display32bmp(22,115,bmp_fhjk);
	return 	1;
 }
//========================================================================
// 函数: INT8U LCD_DisplayAir_condition(INT8U uiair_state_display)
// 描述: 显示空调页面
// 参数: uiair_state_display 空调当前状态 
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayAir_condition(INT8U uiair_state_display)
 {
 	
	LCD_Display32bmp(9,20,bmp_dqkt);
	LCD_Display80bmp(9,36,bmp_dqdqzt);
	if (uiair_state_display == 1)
	{
		LCD_Display16bmp(18,36,bmp_dqk);		
	}
	else 
	{
		LCD_Display16bmp(18,36,bmp_dqg);		
	}
	LCD_Display48bmp(9,52,bmp_dqwd);
	LCD_Display16bmp(16,52,bmp_dqwdfh);			 //显示温度符号
//	LCD_Display80bmp(7,68,bmp_mddssz);
	LCD_Display80bmp(9,68,bmp_dqdssj);
	LCD_Display16bmp(12,84,bmp_dqs);		 //显示时
	LCD_Display16bmp(16,84,bmp_dqf);		 //显示分
	LCD_Display32bmp(4,125,bmp_qd);
	LCD_Display32bmp(22,125,bmp_fhjk);
	return 	1;
 }
//========================================================================
// 函数: INT8U LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
// 描述: 显示热水器页面
// 参数: uiwaterh_state_display 热水器当前状态 
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U  LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
 {
// 	INT8U i,j,m,col;
//	m=0;
//	col=52;
	LCD_Display48bmp(9,20,bmp_dqrsq);
	LCD_Display80bmp(9,36,bmp_dqdqzt);
	if (uiwaterh_state_display == 1)					  //判断当前热水器状态为开
	{
		LCD_Display16bmp(18,36,bmp_dqk);		  //显示当前状态开
	}
	else 
	{
		LCD_Display16bmp(18,36,bmp_dqg);		
	}
	LCD_Display48bmp(9,52,bmp_dqwd);			//显示温度字样
	
	LCD_Display16bmp(16,52,bmp_dqwdfh);			//显示温度符号
	//	LCD_Display80bmp(7,68,bmp_mddssz);	  //已注释的定时设置开关
	LCD_Display80bmp(9,68,bmp_dqdssj);
	LCD_Display16bmp(12,84,bmp_dqs);		 //显示时
	LCD_Display16bmp(16,84,bmp_dqf);		 //显示分
	LCD_Display32bmp(4,115,bmp_qd);
	LCD_Display32bmp(22,115,bmp_fhjk);
	return 	1;
 }
//========================================================================
// 函数: INT8U LCD_DisplayPowerOffSelect()
// 描述: 显示关机选择页面
// 参数: 无  
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayPowerOffSelect()
 {
 	LCD_Display48bmp(11,34,bmp_p1);
	LCD_Display48bmp(11,50,bmp_p2);
	LCD_Display48bmp(11,66,bmp_p3);
	LCD_Display32bmp(4,120,bmp_qd);
	LCD_Display32bmp(22,120,bmp_fhjk);
	return 	1;
 }
////==================================================================================
//// 函数: INT8U LCD_SelectMenuItem(INT8U menupagenumber,INT8U itemnumber)
//// 描述: 显示当前的菜单项
//// 参数: menunumber 菜单编号 itemnumber 菜单项编号  
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////=====================================================================================
//INT8U LCD_SelectMenuItem(INT8U uimenupagenumber,INT8U uiitemnumber)
//{
//	switch(uimenupagenumber)
//	{
//	 	case 1:	  //菜单设置页面
//			if (uiitemnumber == 0)
//				{
//					LCD_Display80bmpf(11,29,bmp_m1);	 //菜单设置页面菜单项一取反
////					LCD_Display80bmp(11,45,bmp_m2);
////					LCD_Display80bmp(11,61,bmp_m3);
////					LCD_Display80bmp(11,77,bmp_m4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk); 	 //取反后使其恢复
//				}
//			if (uiitemnumber == 1)
//				{
//					LCD_Display80bmp(11,29,bmp_m1);
//					LCD_Display80bmpf(11,45,bmp_m2);
////					LCD_Display80bmp(11,61,bmp_m3);
////					LCD_Display80bmp(11,77,bmp_m4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 2)
//				{
//					
////					LCD_Display80bmp(11,29,bmp_m1);
//					LCD_Display80bmp(11,45,bmp_m2);
//					LCD_Display80bmpf(11,61,bmp_m3);
////					LCD_Display80bmp(11,77,bmp_m4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 3)
//				{
//					
////					LCD_Display80bmp(11,29,bmp_m1);
////					LCD_Display80bmp(11,45,bmp_m2);
//					LCD_Display80bmp(11,61,bmp_m3);
//					LCD_Display80bmpf(11,77,bmp_m4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 4)
//				{
//					
////					LCD_Display80bmp(11,29,bmp_m1);
////					LCD_Display80bmp(11,45,bmp_m2);
////					LCD_Display80bmp(11,61,bmp_m3);
//					LCD_Display80bmp(11,77,bmp_m4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmpf(22,120,bmp_fhjk);	
//				}
//			break;
//		case 2:			/////模式选择页面
//			if (uiitemnumber == 0)
//				{
//					LCD_Display80bmpf(11,29,bmp_ms1);		  //工作模式
////					LCD_Display80bmp(11,45,bmp_ms2);
////					LCD_Display80bmp(11,61,bmp_ms3);
////					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 1)							  //回家模式
//				{
//					LCD_Display80bmp(11,29,bmp_ms1);
//					LCD_Display80bmpf(11,45,bmp_ms2);
////					LCD_Display80bmp(11,61,bmp_ms3);
////					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 2)							 //防盗模式
//				{
////					LCD_Display80bmp(11,29,bmp_ms1);
//					LCD_Display80bmp(11,45,bmp_ms2);
//					LCD_Display80bmpf(11,61,bmp_ms3);
////					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 3)							 //外出模式
//				{
////					LCD_Display80bmp(11,29,bmp_ms1);
////					LCD_Display80bmp(11,45,bmp_ms2);
//					LCD_Display80bmp(11,61,bmp_ms3);
//					LCD_Display80bmpf(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 4)							 //返回按钮
//				{
////					LCD_Display80bmp(11,29,bmp_ms1);
////					LCD_Display80bmp(11,45,bmp_ms2);
////					LCD_Display80bmp(11,61,bmp_ms3);
//					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmpf(22,120,bmp_fhjk);	
//				}
//			break;
//		case 5:				 //时钟设置界面
//			if (uiitemnumber == 0)								///选定时钟设置界面年
//				{
////					LCD_PutBlockOnScreen(10,48);
////					delay_ms(1000);
////					LCD_PutNumberOnData(10,48,uicsyearfirst);
//					LCD_Display40bmp(22,120,bmp_fhjk);    		///恢复返回按钮
//					LCD_PutNumberOnDataf(10,48,uicsyearfirst);	//选定年的第一位
//					LCD_PutNumberOnDataf(11,48,uicsyearsecond);	//选定年的第二位
//					LCD_PutNumberOnDataf(12,48,uicsyearthird);	//选定年的第三位
//					LCD_PutNumberOnDataf(13,48,uicsyearforth);	//选定年的第四位			 	
//				}
//			if (uiitemnumber == 1)							   /////选定时钟设置界面月
//				{
////					LCD_PutBlockOnScreen(11,48);
////					delay_ms(1000);
////					LCD_PutNumberOnData(1,48,uicsyearfirst);
//					LCD_PutNumberOnData(10,48,uicsyearfirst);	//恢复年的第一位
//					LCD_PutNumberOnData(11,48,uicsyearsecond);	//恢复年的第二位
//					LCD_PutNumberOnData(12,48,uicsyearthird);	//恢复年的第三位
//					LCD_PutNumberOnData(13,48,uicsyearforth);	//恢复年的第四位
//					LCD_PutNumberOnDataf(16,48,uicsmonthfirst);	//选定月的第一位
//					LCD_PutNumberOnDataf(17,48,uicsmonthsecond); //选定月的第二位			 	
//				}
//			if (uiitemnumber ==2)	   ///日/////////
//				{
//				 	LCD_PutNumberOnDataf(16,48,uicsmonthfirst);	//恢复月的第一位
//					LCD_PutNumberOnDataf(17,48,uicsmonthsecond); //恢复月的第二位
//					LCD_PutNumberOnDataf(20,48,uicsdayfirst);	 //选定天的第一位
//					LCD_PutNumberOnDataf(21,48,uicsdaysecond);	 //选定天的第二位
//				}
//			if (uiitemnumber ==3)	 /////时/////////
//				{
//				 	LCD_PutNumberOnData(20,48,uicsdayfirst);	 //恢复天的第一位
//					LCD_PutNumberOnData(21,48,uicsdaysecond);	 //恢复天的第二位
//					LCD_PutNumberOnDataf(10,65,uicshourfirst);	 //选定小时的第一位
//					LCD_PutNumberOnDataf(11,65,uicshoursecond);	 //选定小时的第二位
//				}
//			if (uiitemnumber ==4)  /////////分/////////////
//				{
//				 	LCD_PutNumberOnData(10,65,uicshourfirst);	 //恢复小时的第一位
//					LCD_PutNumberOnData(11,65,uicshoursecond);	 //恢复小时的第二位
//					LCD_PutNumberOnDataf(14,65,uicsminutefirst);  //选定分钟的第一位
//					LCD_PutNumberOnDataf(15,65,uicsminutesecond); //选定分钟的第二位
//				}
//			if (uiitemnumber ==5)  ///////返回按钮//////////
//				{
//					LCD_PutNumberOnDataf(14,65,uicsminutefirst);  //恢复分钟的第一位
//					LCD_PutNumberOnDataf(15,65,uicsminutesecond); //恢复分钟的第二位
//					LCD_Display40bmpf(22,120,bmp_fhjk);			  //选定返回按钮
//				}	
//	 		break;
//		case 3:		   ///电器设置页面
//			if (uiitemnumber == 0)						  //门灯项
//			{
//					LCD_Display48bmpf(11,29,bmp_as1);
////					LCD_Display64bmp(11,45,bmp_as2);
////					LCD_Display48bmp(11,61,bmp_as3);
////					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 1)						  //卧室灯项
//			{				 
//					LCD_Display48bmp(11,29,bmp_as1);
//					LCD_Display64bmpf(11,45,bmp_as2);
////					LCD_Display48bmp(11,61,bmp_as3);
////					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 2)						  //空调项
//			{
////					LCD_Display48bmp(11,29,bmp_as1);
//					LCD_Display64bmp(11,45,bmp_as2);
//					LCD_Display48bmpf(11,61,bmp_as3);
////					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 3)						  //热水器项
//			{
////					LCD_Display48bmp(11,29,bmp_as1);
////					LCD_Display64bmp(11,45,bmp_as2);
//					LCD_Display48bmp(11,61,bmp_as3);
//					LCD_Display64bmpf(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 4)						  //返回项
//			{
////					LCD_Display48bmp(11,29,bmp_as1);
////					LCD_Display64bmp(11,45,bmp_as2);
////					LCD_Display48bmp(11,61,bmp_as3);
//					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmpf(22,120,bmp_fhjk);	
//			}
//			break;
//		case 4:			//关机选择页面
//			if (uiitemnumber == 0)						//关机选项
//				{
//					LCD_Display48bmpf(11,34,bmp_p1);
////					LCD_Display48bmp(11,50,bmp_p2);
////					LCD_Display48bmp(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 1)					   //重启选项
//				{
//					LCD_Display48bmp(11,34,bmp_p1);
//					LCD_Display48bmpf(11,50,bmp_p2);
////					LCD_Display48bmp(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//
//			if (uiitemnumber == 2)					   //待机选项
//				{
////					LCD_Display48bmp(11,34,bmp_p1);
//					LCD_Display48bmp(11,50,bmp_p2);
//					LCD_Display48bmpf(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 3)					   //返回选项
//				{
////					LCD_Display48bmp(11,34,bmp_p1);
////					LCD_Display48bmp(11,50,bmp_p2);
//					LCD_Display48bmp(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmpf(22,120,bmp_fhjk);	
//				}
//	   	break;
//		case 6:	 //门灯页面菜单
//			if (uiitemnumber == 0)	//门灯开关
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);///恢复返回按钮
//					if (uidoorl_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1 )	//门灯页面定时小时位
//				{
//					if (uidoorl_state_display ==0)
//						{
//							LCD_Display16bmp(18,36,bmp_dqg);	////使开关正常
//						}
//					else
//						{
//							LCD_Display16bmp(18,36,bmp_dqk);
//						}
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 2 )	//门灯页面定时分钟位
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 3 )	//门灯页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,uitsminutefirst);
//					LCD_PutNumberOnData(15,84,uitsminutesecond);
//					if ( uitimingsetswitch ==1 )				 //选定定时开关
//					{
//						LCD_Display16bmpf(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmpf(19,84,bmp_dqg);
//					}
//				}
//			
//			if (uiitemnumber == 4)
//				{
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmp(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmp(19,84,bmp_dqg);
//					}
//					LCD_Display40bmpf(22,120,bmp_fhjk);///选定返回按钮
//				}
//		break;
//		case 7:	   ///////卧室灯界面/////////////////////
//			if (uiitemnumber == 0)	//卧室灯开关
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);   ///恢复返回按钮
//					if (uibedl_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1 )	//卧室灯页面定时小时位
//				{
//					if (uibedl_state_display ==0)
//						{
//							LCD_Display16bmp(18,36,bmp_dqg);	 //使开关正常
//						}
//					else
//						{
//							LCD_Display16bmp(18,36,bmp_dqk);
//						}
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 2 )	//卧室灯页面定时分钟位
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 3 )	//卧室灯页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,uitsminutefirst);
//					LCD_PutNumberOnData(15,84,uitsminutesecond);
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmpf(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmpf(19,84,bmp_dqg);
//					}
//				}
//			
//			if (uiitemnumber == 4)
//				{
//					if ( uitimingsetswitch ==1 )         //恢复定时时间开关
//					{
//						LCD_Display16bmp(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmp(19,84,bmp_dqg);
//					}
//					LCD_Display40bmpf(22,120,bmp_fhjk);///选定返回按钮
//				}
//		break;
//	    case 8:	   ////空调界面//////////////
//			if (uiitemnumber == 0)	//空调开关
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);///恢复返回按钮
//					if (uiair_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1)	//空调温度
//				{
//					if (uiair_state_display ==0)
//						{
//							LCD_Display16bmp(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmp(18,36,bmp_dqk);
//						}                        ////////////恢复开关状态的///////////////
//					LCD_PutNumberOnDataf(14,52,uitemsetfirst_wat);
//					LCD_PutNumberOnDataf(15,52,uitemsetsecond_wat);
//				}
//			if (uiitemnumber == 2 )	//空调页面定时小时位
//				{
//					LCD_PutNumberOnData(14,52,uitemsetfirst_wat);
//					LCD_PutNumberOnData(15,52,uitemsetsecond_wat);////////使温度恢复
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 3 )	//空调页面定时位
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 4 )	//空调灯页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,uitsminutefirst);
//					LCD_PutNumberOnData(15,84,uitsminutesecond);
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmpf(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmpf(19,84,bmp_dqg);
//					}
//				}
//			
//			if (uiitemnumber == 5)	//////////返回按钮/////////
//				{
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmp(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmp(19,84,bmp_dqg);
//					}
//					LCD_Display40bmpf(22,120,bmp_fhjk);///选定返回按钮
//				}
//		break;
//		case 9:
//			if (uiitemnumber == 0)	//热水器开关
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);///恢复返回按钮
//					if (uiwaterh_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1)	//热水器温度
//				{
//					if (uiwaterh_state_display ==0)
//						{
//							LCD_Display16bmp(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmp(18,36,bmp_dqk);
//						}
//					LCD_PutNumberOnDataf(14,52,uitemsetfirst_wat);
//					LCD_PutNumberOnDataf(15,52,uitemsetsecond_wat);
//				}
//			if (uiitemnumber == 2 )	//热水器页面定时小时位
//				{
//					LCD_PutNumberOnData(14,52,uitemsetfirst_wat);
//					LCD_PutNumberOnData(15,52,uitemsetsecond_wat);////////使温度恢复
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 3 )	//热水器页面定时分钟位
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 4 )	//热水器页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,uitsminutefirst);
//					LCD_PutNumberOnData(15,84,uitsminutesecond);
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmpf(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmpf(19,84,bmp_dqg);
//					}
//				}
//			
//			if (uiitemnumber == 5)	//////////返回按钮/////////
//				{
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmp(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmp(19,84,bmp_dqg);
//					}
//					LCD_Display40bmpf(22,120,bmp_fhjk);///选定返回按钮
//				}
//		break;
//		default:
//		break;
//	}	
//}
////========================================================================
//// 函数: INT8U LCD_DisplayError(INT8U errortype)
//// 描述: 显示错误页面
//// 参数: errortype 错误的类型
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
//INT8U LCD_DisplayError(INT8U errortype)
//{
//	switch (errortype)
//	{
//		case 1:
//
//			break;
//		case 2:
//			
//			break;
//		case 3:
//
//			break;
//		case 4:
//			
//			break;
//		default:
//			break;
//	}
//}
//========================================================================
// 函数: INT8U LCD_DisplayWarning(INT8U uiwarningtype)
// 描述: 显示警告页面
// 参数: warningtype 警告的类型
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayWarning(INT8U uiwarningtype)
 {
 	INT8U m;
	INT8U i,j,col;
	switch (uiwarningtype)
	{
	case 1:		 //煤气泄漏警告
		m=0;								 //清屏
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//定位清屏起始位置
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(0x00);	//写入清屏数组
				m++;
			}
			col++;
		}

		m=0;								 //显示警告图片
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//定位图片显示起始位置
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(bmp_jg[m]);	//写入警告图片数组
				m++;
			}
			col++;
		}

		m=0;								//显示煤气泄漏警告文字
		col=84;
		for(i=0;i<21;i++)				  
		{
			LCD_Locatexy(10,col);		    //定位文字显示起始位置	
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<11;j++)
			{
				LCD_WriteData(bmp_mq[m]);	 //写入煤气泄漏文字数组
				m++;
			}
			col++;
		}
		m=0;								//显示返回主界面按钮
		col=120;
		for(i=0;i<24;i++)				  
		{
			LCD_Locatexy(20,col);		    //定位返回按钮起始位置
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<6;j++)
			{
				LCD_WriteData(bmp_jgfh[m]);	 //写入返回按钮数组
				m++;
			}
			col++;
		}
		break;
	case 2:	 //小偷进入警告
		m=0;								 //清屏
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//定位清屏起始位置
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(0x00);	//写入清屏数组
				m++;
			}
			col++;
		}

		m=0;								 //显示警告图片
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//定位图片显示起始位置
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(bmp_jg[m]);	  //写入图片数组
				m++;
			}
			col++;
		}
		m=0;								//显示煤气泄漏警告文字
		col=84;
		for(i=0;i<21;i++)				  
		{
			LCD_Locatexy(10,col);		   //定位文字显示起始位置
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<11;j++)
			{
				LCD_WriteData(bmp_xt[m]);	 //写入文字数组
				m++;
			}
			col++;
		}
		m=0;								//显示返回主界面按钮
		col=120;
		for(i=0;i<24;i++)				  
		{
			LCD_Locatexy(20,col);		   //定位返回按钮起始位置
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<6;j++)
			{
				LCD_WriteData(bmp_jgfh[m]);	 //写入按钮数组
				m++;
			}
			col++;
		}
		break;
	default:
		break;
	}
	return 	1;
 }

