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
// ����: void LCD_Init(void)
// ����: LCD��ʼ������
// ����: ��
// ����: ��
// �汾:
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
	LCD_WriteData(0x0c);  //p1  Ĭ��00
	//display off
	LCD_WriteCommand(0x58);
	LCD_WriteData(0x06);
	//display on 
	LCD_WriteCommand(0x59);
}
//========================================================================
// ����: void LCD_Clear(void)
// ����: LCD��������
// ����: ��
// ����: ��
// �汾:
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
	LCD_WriteData(0x0c);  //p1  Ĭ��00
	//display off
	LCD_WriteCommand(0x58);
	LCD_WriteData(0x06);
	//display on 
	LCD_WriteCommand(0x59);
}


//========================================================================
// ����: void LCD_Locatexy(INT8U x,INT8U y)
// ����: ��λһ����,��LCD�����еĵ�ת��Ϊ�Դ��еĶ�Ӧ��ֵ
// ����: x X ������ y Y ������  
// ����: ��
// �汾:
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
// ����: void LCD_CheckBusy(void)
// ����: ���LCDæ����
// ����: ��
// ����: ��
// �汾:
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
// ����: void LCD_WriteCommand(INT8U cmd)
// ����: ��LCD�Ĵ�����д��ֵ
// ����: cmd д��Ĵ�����ֵ
// ����: ��
// �汾:
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
// ����: void LCD_WriteData(INT8U data)
// ����: ��LCD������RAM��д��һ���Լ�������
// ����: date д��RAM��ֵ
// ����: ��
// �汾:
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
// ����: INT8U  LCD_ReadData(void)
// ����: ��LCD��ʾ�洢��RAM�ж���ֵ
// ����: ��
// ����: ret  ����ʾ�洢��RAM�ж�����һ���ֽڵ�����
// �汾:
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
// ����: void LCD_SetCursor(INT8U  x,INT8U  y)
// ����: ���ù��ĵ�ַ
// ����: x ���ָ���8λ  y ���ָ���8λ
// ����: ��
// �汾:
//========================================================================
void LCD_SetCursor(INT8U  x,INT8U  y)
{
	LCD_WriteCommand(0x46);
	LCD_WriteData(x);
	LCD_WriteData(y);
}

//========================================================================
// ����: void LCD_WriteDot(INT8U dot_x,INT8U dot_y)
// ����: ��LCD ����ʵ����ϵ�ϵ�X��Y ����
// ����: x X ������
// 		 y Y ������
// ����: ��
// �汾:
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
// ����: void LCD_Displaybmp (INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��240X160ͼƬ
// ����: *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display72bmp (INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��72X16ͼƬ
// ����: *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display64bmp (INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��64X16ͼƬ
// ����: *putbmp ͼƬ�����ַָ�� uirow  ������  uicol ������
// ����: ��
// �汾:
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
// ����: void LCD_Display64bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��64X16ͼƬȡ��
// ����: uirow  ������  uicol ������
//		 *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display80bmp (INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��80X16ͼƬ
// ����: *putbmp ͼƬ�����ַָ�� uirow  ������  uicol ������
// ����: ��
// �汾:
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
// ����: void LCD_Display80bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��80X16ͼƬ��ȡ��ͼƬ
// ����: *putbmp ͼƬ�����ַָ�� uirow  ������  uicol ������
// ����: ��
// �汾:
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
// ����: void LCD_Display48bmp (INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��48X16ͼƬ
// ����: *putbmp ͼƬ�����ַָ�� uirow  ������  uicol ������
// ����: ��
// �汾:
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
// ����: void LCD_Display48bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��48X16ͼƬ��ȡ��ͼƬ
// ����: *putbmp ͼƬ�����ַָ�� uirow  ������  uicol ������
// ����: ��
// �汾:
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
// ����: void LCD_Display32bmp (INT8U row,INT8U col,const INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��32X16ͼƬ
// ����: *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display32bmpf (INT8U row,INT8U col,const INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��32X16ͼƬ��ȡ��
// ����: *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display16bmp (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��40X21ͼƬ	   ר��������ʾ���ؼӿ�ť
// ����: uirow  ͼƬ��ʼ��ַ������
//		 uicol  ͼƬ��ʼ��ַ������
//		 *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display16bmpf (INT8U uirow,INT8U uicol,const INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��40X21ͼƬ��ȡ��	ר��������ʾ���ؼӿ�ť
// ����: uirow  ͼƬ��ʼ��ַ������
//		 uicol  ͼƬ��ʼ��ַ������
//		 *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display16bmp (INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��16X16ͼƬ
// ����: *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_Display16bmpf (INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��16X16ͼƬȡ��
// ����: *putbmp ͼƬ�����ַָ��
// ����: ��
// �汾:
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
// ����: void LCD_PutHZ(INT8U col,INT8U row,INT8U HZcode)
// ����: �Ժ�����Ϊcol,������Ϊrow�ĵ�Ϊ�����ʾһ������ ���ִ�СΪ22X22
// ����: col X ������ row Y ������  HZcode �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
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
// ����: void LCD_PutSHZ(INT8U col,INT8U row,INT8U Hzcode)
// ����: �Ժ�����Ϊcol,������Ϊrow�ĵ�Ϊ�����ʾһ������ ���ִ�СΪ14X12
// ����: col X ������ row Y ������  HZcode �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
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
// ����: void LCD_PutNumberOnMS(INT8U uicol,INT8U uirow,INT8U NumberOnMS)
// ����: ����������ʾʱ������һ������
// ����: col X ������ row Y ������   NumberOnMS �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
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
// ����: void LCD_PutWeek(INT8U col,INT8U row,INT8U uiweek)
// ����: ����������ʾ���ڿ����һ����������
// ����: col X ������ row Y ������  uiweek �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
//========================================================================
void LCD_PutWeek(INT8U uicol,INT8U uirow,const INT8U uiweek)
{
	INT8U i,j;
	INT32U  x;
	x = 0x18*uiweek;				 //�����week����������ʼλ��
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //��λ��ʼ��ַ
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
// ����: void LCD_PutNumberOnData(INT8U uicol,INT8U uirow,INT8U uinumberondata)
// ����: ��һ��8X16������
// ����: uicol X ������ uirow Y ������   uinumberondata �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
//========================================================================
void LCD_PutNumberOnData(INT8U uicol,INT8U uirow,const INT8U uinumberondata)
{
	INT8U i,j;
	INT32U  x;
	x = 0x0c*uinumberondata;				 //�����uinumberondata����������ʼλ��
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //��λ��ʼ��ַ
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
// ����: void LCD_PutNumberOnDataf(INT8U uicol,INT8U uirow,INT8U uinumberondata)
// ����: ��һ��8X16�����ֵ�ȡ��
// ����: uicol X ������ uirow Y ������   uinumberondata �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
//========================================================================
void LCD_PutNumberOnDataf(INT8U uicol,INT8U uirow,const INT8U uinumberondata)
{
	INT8U i,j;
	INT32U  x;
	x = 0x0c*uinumberondata;				 //�����uinumberondata����������ʼλ��
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //��λ��ʼ��ַ
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
//// ����: void LCD_PutBlkOnScreen(INT8U uicol,INT8U uirow)
//// ����: ��һ��8X16�ĺڿ�
//// ����: uicol X ������ uirow Y ������   
//// ����: ��
//// �汾:
////========================================================================
//void LCD_PutBlockOnScreen(INT8U uicol,INT8U uirow)
//{
//	INT8U i,j;
//	INT32U  x;
//	x=0;				 //�����uinumberondata����������ʼλ��
//	for(i=0;i<16;i++)
//	{
//		LCD_Locatexy(uicol,uirow);   //��λ��ʼ��ַ
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
// ����: INT16U LCD_PowerOn()
// ����: ������ʾ����
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
INT8U LCD_PowerOn()
{
	LCD_PutHZ(3,48,0); //��ʾ��
	LCD_PutHZ(6,48,1); //��ʾ��
	LCD_PutHZ(9,48,2); //��ʾ��
	LCD_PutHZ(12,48,3);//��ʾ��
	LCD_PutHZ(15,48,4);//��ʾ��
	LCD_PutHZ(18,48,5);//��ʾ��
	LCD_PutHZ(21,48,6);//��ʾϵ
	LCD_PutHZ(24,48,7);//��ʾͳ
	LCD_PutHZ(9,71,8); //��ʾ��
	LCD_PutHZ(12,71,9);//��ʾӭ
	LCD_PutHZ(15,71,10);//��ʾ��
	LCD_PutHZ(18,71,15);//��ʾ��
	return 1;
}
//========================================================================
// ����: INT8U LCD_PowerOff()
// ����: ��ʾ�ػ�ҳ��
// ����: ��
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
INT8U LCD_PowerOff()
{
	LCD_PutHZ(3,48,0); //��ʾ��
	LCD_PutHZ(6,48,1); //��ʾ��
	LCD_PutHZ(9,48,2);//��ʾ��
	LCD_PutHZ(12,48,3);//��ʾ��
	LCD_PutHZ(15,48,4);//��ʾ��
	LCD_PutHZ(18,48,5);//��ʾ��
	LCD_PutHZ(21,48,6);//��ʾϵ
	LCD_PutHZ(24,48,7);//��ʾͳ
	LCD_PutHZ(3,71,8); //��ʾ��
	LCD_PutHZ(6,71,9); //��ʾӭ
	LCD_PutHZ(9,71,10);//��ʾ��
	LCD_PutHZ(12,71,11);//��ʾ��
	LCD_PutHZ(15,71,12);//��ʾ��
	LCD_PutHZ(18,71,13);//��ʾʹ
	LCD_PutHZ(21,71,14);//��ʾ��
	LCD_PutHZ(24,71,15);//��ʾ��
	return 1;	
}
//========================================================================
// ����: INT8U LCD_DispalyMainScreen()
// ����: ��ʾ��λ����������
// ����: ��
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_DispalyMainScreen()
 {
 	INT8U m;
	INT8U i,j,col;
	////////////////��ȱ��ʾʱ����صĺ���//////////////////
	m=0;
	col=12;
	for(i=0;i<26;i++)				  //  ��ʾ�ֺŷֺŷֺŷֺŷֺŷֺŷֺŷֺŷֺŷֺŷֺŷֺ�
	{
		LCD_Locatexy(6,col);		  //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
	for(i=0;i<12;i++)				  //��ʾ������������������������������������������������
	{
		LCD_Locatexy(4,col);		  //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
	for(i=0;i<12;i++)				  //��ʾ������������
	{
		LCD_Locatexy(5,col);		  //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
	for(i=0;i<12;i++)				  //��ʾ������������������
	{
		LCD_Locatexy(9,col);		  //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
	for(i=0;i<12;i++)				  //��ʾ����������������������
	{
		LCD_Locatexy(13,col);		  //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
	for(i=0;i<19;i++)				  //��ʾ���������ܼҵ����ϵͳ
	{
		LCD_Locatexy(13,col);		  //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
	for(i=0;i<14;i++)				 	//��ʾ�������¶�����
	{
		LCD_Locatexy(17,col);			//��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
	for(i=0;i<14;i++)				 	//��ʾ�������¶ȷ���
	{
		LCD_Locatexy(25,col);			//��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_wdf[m]);
			m++;
		}
		col++;
	}
	m=0;							   //��ʾ�������ǿ����
	col=55;
	for(i=0;i<14;i++)				 
	{
		LCD_Locatexy(17,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<6;j++)
		{
			LCD_WriteData(bmp_gq[m]);
			m++;
		}
		col++;
	}
	m=0;							   //��ʾ�������ǿ��������
	col=55;
	for(i=0;i<14;i++)				 
	{
		LCD_Locatexy(25,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<1;j++)
		{
			LCD_WriteData(bmp_gqf[m]);
			m++;
		}
		col++;
	}
    m=0;							   //��ʾ�������ŵ�����
	col=80;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(3,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(bmp_md[m]);
			m++;
		}
		col++;
	}

	m=0;							   //��ʾ������յ�����
	col=96;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(3,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(bmp_kt[m]);
			m++;
		}
		col++;
	}

	m=0;							   //��ʾ���������ҵ�����
	col=80;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(16,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<10;j++)
		{
			LCD_WriteData(bmp_wsd[m]);
			m++;
		}
		col++;
	}
	

	m=0;							   //��ʾ��������ˮ������
	col=96;
	for(i=0;i<12;i++)				 
	{
		LCD_Locatexy(16,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<10;j++)
		{
			LCD_WriteData(bmp_rsq[m]);
			m++;
		}
		col++;
	}

	m=0;							   //��ʾ������˵���������
	col=119;
	for(i=0;i<24;i++)				 
	{
		LCD_Locatexy(3,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
		for(j=0;j<8;j++)
		{
			LCD_WriteData(bmp_cd[m]);
			m++;
		}
		col++;
	}

	m=0;							   //��ʾ�����������������
	col=119;
	for(i=0;i<24;i++)				 
	{
		LCD_Locatexy(17,col);		   //��λ�����㣬row��ʾLCD���ϵĺ����꣬col��ʾLCD���ϵ�������
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
// ����: INT8U LCD_UpdateApplianceState(INT8U uiair_state,INT8U uiwaterh_state,INT8U uidoorl_state,INT8U uibedl_state)
// ����: ������λ���˵���״̬��Ϣ
// ����: uiair_state �յ�״̬��Ϣ 1��0��		  1Ϊ����0Ϊ��
//		 uiwaterh_state ��ˮ��״̬��Ϣ 1��0
//		 uidoorl_state  �ŵ�״̬��Ϣ 1��0
//       uibedl_state	���ҵ�״̬��Ϣ 1��0
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
INT8U LCD_UpdateApplianceState (INT8U uidoorl_state,INT8U uibedl_state,INT8U uiair_state,INT8U uiwaterh_state)
{	
	if (uiair_state == 1)
	{
		LCD_Display16bmp(10,78,bmp_16y);//�ŵ�״̬��
	}
	if (uidoorl_state ==1)
	{
		LCD_Display16bmp(25,78,bmp_16y);//���ҵ�״̬��    
	}
	if (uiwaterh_state == 1 )
	{
		LCD_Display16bmp(10,93,bmp_16y);//�յ�״̬��
	}
	if(uibedl_state == 1)
	{
		LCD_Display16bmp(25,93,bmp_16y);//��ˮ��״̬��
	}
	else
	{
	}
	return 1;
}
//========================================================================
// ����: INT8U LCD_UpdateConnect(INT8U uiConnectdata)
// ����: ��ʾԶ��������ҳ��
// ����: uiConnectdata ��ǰ��PC������״̬ 1Ϊ���� 0Ϊ�Ͽ�
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_UpdateConnect(INT8U uiConnectdata)
 {
 	INT8U m;
	INT8U i,j,col;
	m=0;
	col=0;
	if (uiConnectdata == 1 )		   //��ʾԶ�̿���������
	{
		LCD_Display16bmp(0,0,bmp_9y);  //ˢ��״̬ͼƬ	
		LCD_Display72bmp(2,0,bmp_yc);
	}
	else 
	{
	
	for(i=0;i<10;i++)				  //��ʾԶ�̿���δ����
	{
		LCD_Locatexy(2,col);		  //��λ������
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
// ����: INT8U LCD_UpdateTime(INT8U uihourfirst,INT8U uihoursecond,INT8U uiminutefirst,INT8U uiminutesecond)
// ����: ������ҳ��ʱ�䣬����
// ����: uihourfirst Сʱ��һλ
//       uihoursecond Сʱ�ڶ�λ
//       uiminutefirst ���ӵ�һλ
//		 uiminutesecond ���ӵڶ�λ	
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_UpdateWeek(INT8U uiweek)
// ����: ������ҳ�����ڼ�
// ����: uiweek ���ڼ�	
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_UpdateWeek(INT8U uiweek)
 {
 	LCD_PutWeek(7,41,uiweek);
	return 1;
 }
//===================================================================================================================================================================================================================================================
// ����: INT8U LCD_UpdateDate(INT8U uiyearfirst,INT8U uiyearsecond,INT8U uiyearthird,INT8U uiyearforth,INT8U uimonthfirst,INT8U uimonthsecond,INT8U uidayfirst,INT8U uidaysecond)
// ����: ������ҳ������
// ����: uinianfirst ��ĵ�һλ
//		 uiyearsecond ��ĵڶ�λ
//		 uiyearthird  ��ĵ���λ
//		 uiyearforth ��ĵ���λ
//		 uimonthfirst �µĵ�һλ
//		 uimonthsecond �µĵڶ�λ
//		 uidayfirst ��ĵ�һλ
//		 uidaysecond ��ĵڶ�λ
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_UpdateCircumstance(INT8U uitem,INT8U uihum)
// ����: ���������滷����Ϣҳ��
// ����: uitem   �¶���Ϣ   uihum  ������Ϣ  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_UpdateClockSetDate(INT8U uicsyearfirst,INT8U uicsyearsecond,INT8U uicsyearthird,INT8U uicsyearforth,INT8U uicsmonthfirst,INT8U uicsmonthsecond,INT8U uicsdayfirst,INT8U uicsdaysecond)
// ����: ����ʱ�ӽ�����������
// ����: uinianfirst ��ĵ�һλ	 
//		 uicsyearsecond ��ĵڶ�λ 	 
//		 uicsyearthird ��ĵ���λ	 
//       uicsyearforth ��ĵ���λ
//       uicsmonthfirst �µĵ�һλ
//       uicsmonthsecond �µĵڶ�λ
//       uicsdayfirst    ��ĵ�һλ
//		 uicsdayfirst    ��ĵڶ�λ
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U  LCD_UpdateClockSetTime(INT8U uicshourfirst,INT8U uicshoursecond,INT8U uicsminutefirst,INT8U uicsminutesecond)
// ����: ����ʱ������ʱ��
// ����: uicshourfirst Сʱ��һλ
//       uicshoursecond Сʱ�ڶ�λ
//       uicsminutefirst ���ӵ�һλ
//		 uicsminutesecond ���ӵڶ�λ	
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_UpdateTemSetTem(INT8U uitemsetfirst,INT8U uitemsetsecond)
// ����: ���¿յ�����ˮ����Ϣҳ���¶��趨
// ����: uitemsetfirst_air  �¶����õ�һλ   uitemsetsecond_air  �¶����õڶ�λ 
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//===========================================================================
INT8U LCD_UpdateTemSetTem(INT8U uitemsetfirst,INT8U uitemsetsecond)
{
	LCD_PutNumberOnData(14,52,uitemsetfirst_air);
	LCD_PutNumberOnData(15,52,uitemsetsecond_air);
	return 1;
}

//==========================================================================
// ����: INT8U LCD_UpdateTimingSet(INT8U uitshourfirst,INT8U uitshoursecond,INT8U uitsminutefirst,INT8U uitsminutesecond,INT8U uitimingsetswitch)
// ����: ���µ�����Ϣҳ�涨ʱʱ��
// ����: uitshourfirst   ��ʱʱ��Сʱ��һλ   uitshoursecond  ��ʱʱ��Сʱ�ڶ�λ  uitsminutefirst ��ʱ���ӵ�һλ  uitsminutesecond ��ʱ���ӵڶ�λ  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_DisplayMenuSet()
// ����: ��ʾ�˵�����ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_DisplayModeSelect()
// ����: ��ʾģʽѡ��ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_DisplayTimeSet()
// ����: ��ʾʱ������ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_DisplayTimeSet()
 {
 	LCD_Display48bmp(5,48,bmp_shrq); 		 //��ʾ���ڣ����ڣ����ڣ�
	LCD_Display16bmp(14,48,bmp_dqn); 		 //��ʾ��
	LCD_Display16bmp(18,48,bmp_dqy);		 //��ʾ��
	LCD_Display16bmp(22,48,bmp_dqr);		 //��ʾ��
	LCD_Display48bmp(5,65,bmp_shsj);		 //��ʾʱ��;ʱ��;ʱ��;
	LCD_Display16bmp(12,65,bmp_dqs);		 //��ʾʱ
	LCD_Display16bmp(16,65,bmp_dqf);		 //��ʾ��
	LCD_Display32bmp(4,120,bmp_qd);
	LCD_Display32bmp(22,120,bmp_fhjk);
	return 	1;
 }
//========================================================================
// ����: INT8U LCD_DisplayApplianceSet()
// ����: ��ʾ��������ҳ��  ��Ϊ��ʾѡ���ĸ�������ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
// ����: INT8U LCD_DisplayDoorl(INT8U uidoorl_state_display)
// ����: ��ʾ�ŵ�ҳ��
// ����: uidoorl_state_disaplay    ��ʾ�ŵƵ�����ǰ��״̬
//       ����ֱ�Ӷ�ȡϵͳ״̬�� ���������ʾ������ѵ�����ǰ״̬�����������  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
	LCD_Display16bmp(12,84,bmp_dqs);		 //��ʾʱ
	LCD_Display16bmp(16,84,bmp_dqf);		 //��ʾ��
	LCD_Display32bmp(4,115,bmp_qd);
	LCD_Display32bmp(22,115,bmp_fhjk);
	return 	1;
 }
//========================================================================
// ����: INT8U LCD_DisplayBedl(INT8U uibedl_state_display)
// ����: ��ʾ���ҵ�ҳ��
// ����: uibedl_state_display ���ҵƵ�����ǰ��״̬  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
	LCD_Display16bmp(12,84,bmp_dqs);		 //��ʾʱ
	LCD_Display16bmp(16,84,bmp_dqf);		 //��ʾ��
	LCD_Display32bmp(4,115,bmp_qd);
	LCD_Display32bmp(22,115,bmp_fhjk);
	return 	1;
 }
//========================================================================
// ����: INT8U LCD_DisplayAir_condition(INT8U uiair_state_display)
// ����: ��ʾ�յ�ҳ��
// ����: uiair_state_display �յ���ǰ״̬ 
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
	LCD_Display16bmp(16,52,bmp_dqwdfh);			 //��ʾ�¶ȷ���
//	LCD_Display80bmp(7,68,bmp_mddssz);
	LCD_Display80bmp(9,68,bmp_dqdssj);
	LCD_Display16bmp(12,84,bmp_dqs);		 //��ʾʱ
	LCD_Display16bmp(16,84,bmp_dqf);		 //��ʾ��
	LCD_Display32bmp(4,125,bmp_qd);
	LCD_Display32bmp(22,125,bmp_fhjk);
	return 	1;
 }
//========================================================================
// ����: INT8U LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
// ����: ��ʾ��ˮ��ҳ��
// ����: uiwaterh_state_display ��ˮ����ǰ״̬ 
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U  LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
 {
// 	INT8U i,j,m,col;
//	m=0;
//	col=52;
	LCD_Display48bmp(9,20,bmp_dqrsq);
	LCD_Display80bmp(9,36,bmp_dqdqzt);
	if (uiwaterh_state_display == 1)					  //�жϵ�ǰ��ˮ��״̬Ϊ��
	{
		LCD_Display16bmp(18,36,bmp_dqk);		  //��ʾ��ǰ״̬��
	}
	else 
	{
		LCD_Display16bmp(18,36,bmp_dqg);		
	}
	LCD_Display48bmp(9,52,bmp_dqwd);			//��ʾ�¶�����
	
	LCD_Display16bmp(16,52,bmp_dqwdfh);			//��ʾ�¶ȷ���
	//	LCD_Display80bmp(7,68,bmp_mddssz);	  //��ע�͵Ķ�ʱ���ÿ���
	LCD_Display80bmp(9,68,bmp_dqdssj);
	LCD_Display16bmp(12,84,bmp_dqs);		 //��ʾʱ
	LCD_Display16bmp(16,84,bmp_dqf);		 //��ʾ��
	LCD_Display32bmp(4,115,bmp_qd);
	LCD_Display32bmp(22,115,bmp_fhjk);
	return 	1;
 }
//========================================================================
// ����: INT8U LCD_DisplayPowerOffSelect()
// ����: ��ʾ�ػ�ѡ��ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
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
//// ����: INT8U LCD_SelectMenuItem(INT8U menupagenumber,INT8U itemnumber)
//// ����: ��ʾ��ǰ�Ĳ˵���
//// ����: menunumber �˵���� itemnumber �˵�����  
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////=====================================================================================
//INT8U LCD_SelectMenuItem(INT8U uimenupagenumber,INT8U uiitemnumber)
//{
//	switch(uimenupagenumber)
//	{
//	 	case 1:	  //�˵�����ҳ��
//			if (uiitemnumber == 0)
//				{
//					LCD_Display80bmpf(11,29,bmp_m1);	 //�˵�����ҳ��˵���һȡ��
////					LCD_Display80bmp(11,45,bmp_m2);
////					LCD_Display80bmp(11,61,bmp_m3);
////					LCD_Display80bmp(11,77,bmp_m4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk); 	 //ȡ����ʹ��ָ�
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
//		case 2:			/////ģʽѡ��ҳ��
//			if (uiitemnumber == 0)
//				{
//					LCD_Display80bmpf(11,29,bmp_ms1);		  //����ģʽ
////					LCD_Display80bmp(11,45,bmp_ms2);
////					LCD_Display80bmp(11,61,bmp_ms3);
////					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 1)							  //�ؼ�ģʽ
//				{
//					LCD_Display80bmp(11,29,bmp_ms1);
//					LCD_Display80bmpf(11,45,bmp_ms2);
////					LCD_Display80bmp(11,61,bmp_ms3);
////					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 2)							 //����ģʽ
//				{
////					LCD_Display80bmp(11,29,bmp_ms1);
//					LCD_Display80bmp(11,45,bmp_ms2);
//					LCD_Display80bmpf(11,61,bmp_ms3);
////					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 3)							 //���ģʽ
//				{
////					LCD_Display80bmp(11,29,bmp_ms1);
////					LCD_Display80bmp(11,45,bmp_ms2);
//					LCD_Display80bmp(11,61,bmp_ms3);
//					LCD_Display80bmpf(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 4)							 //���ذ�ť
//				{
////					LCD_Display80bmp(11,29,bmp_ms1);
////					LCD_Display80bmp(11,45,bmp_ms2);
////					LCD_Display80bmp(11,61,bmp_ms3);
//					LCD_Display80bmp(11,77,bmp_ms4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmpf(22,120,bmp_fhjk);	
//				}
//			break;
//		case 5:				 //ʱ�����ý���
//			if (uiitemnumber == 0)								///ѡ��ʱ�����ý�����
//				{
////					LCD_PutBlockOnScreen(10,48);
////					delay_ms(1000);
////					LCD_PutNumberOnData(10,48,uicsyearfirst);
//					LCD_Display40bmp(22,120,bmp_fhjk);    		///�ָ����ذ�ť
//					LCD_PutNumberOnDataf(10,48,uicsyearfirst);	//ѡ����ĵ�һλ
//					LCD_PutNumberOnDataf(11,48,uicsyearsecond);	//ѡ����ĵڶ�λ
//					LCD_PutNumberOnDataf(12,48,uicsyearthird);	//ѡ����ĵ���λ
//					LCD_PutNumberOnDataf(13,48,uicsyearforth);	//ѡ����ĵ���λ			 	
//				}
//			if (uiitemnumber == 1)							   /////ѡ��ʱ�����ý�����
//				{
////					LCD_PutBlockOnScreen(11,48);
////					delay_ms(1000);
////					LCD_PutNumberOnData(1,48,uicsyearfirst);
//					LCD_PutNumberOnData(10,48,uicsyearfirst);	//�ָ���ĵ�һλ
//					LCD_PutNumberOnData(11,48,uicsyearsecond);	//�ָ���ĵڶ�λ
//					LCD_PutNumberOnData(12,48,uicsyearthird);	//�ָ���ĵ���λ
//					LCD_PutNumberOnData(13,48,uicsyearforth);	//�ָ���ĵ���λ
//					LCD_PutNumberOnDataf(16,48,uicsmonthfirst);	//ѡ���µĵ�һλ
//					LCD_PutNumberOnDataf(17,48,uicsmonthsecond); //ѡ���µĵڶ�λ			 	
//				}
//			if (uiitemnumber ==2)	   ///��/////////
//				{
//				 	LCD_PutNumberOnDataf(16,48,uicsmonthfirst);	//�ָ��µĵ�һλ
//					LCD_PutNumberOnDataf(17,48,uicsmonthsecond); //�ָ��µĵڶ�λ
//					LCD_PutNumberOnDataf(20,48,uicsdayfirst);	 //ѡ����ĵ�һλ
//					LCD_PutNumberOnDataf(21,48,uicsdaysecond);	 //ѡ����ĵڶ�λ
//				}
//			if (uiitemnumber ==3)	 /////ʱ/////////
//				{
//				 	LCD_PutNumberOnData(20,48,uicsdayfirst);	 //�ָ���ĵ�һλ
//					LCD_PutNumberOnData(21,48,uicsdaysecond);	 //�ָ���ĵڶ�λ
//					LCD_PutNumberOnDataf(10,65,uicshourfirst);	 //ѡ��Сʱ�ĵ�һλ
//					LCD_PutNumberOnDataf(11,65,uicshoursecond);	 //ѡ��Сʱ�ĵڶ�λ
//				}
//			if (uiitemnumber ==4)  /////////��/////////////
//				{
//				 	LCD_PutNumberOnData(10,65,uicshourfirst);	 //�ָ�Сʱ�ĵ�һλ
//					LCD_PutNumberOnData(11,65,uicshoursecond);	 //�ָ�Сʱ�ĵڶ�λ
//					LCD_PutNumberOnDataf(14,65,uicsminutefirst);  //ѡ�����ӵĵ�һλ
//					LCD_PutNumberOnDataf(15,65,uicsminutesecond); //ѡ�����ӵĵڶ�λ
//				}
//			if (uiitemnumber ==5)  ///////���ذ�ť//////////
//				{
//					LCD_PutNumberOnDataf(14,65,uicsminutefirst);  //�ָ����ӵĵ�һλ
//					LCD_PutNumberOnDataf(15,65,uicsminutesecond); //�ָ����ӵĵڶ�λ
//					LCD_Display40bmpf(22,120,bmp_fhjk);			  //ѡ�����ذ�ť
//				}	
//	 		break;
//		case 3:		   ///��������ҳ��
//			if (uiitemnumber == 0)						  //�ŵ���
//			{
//					LCD_Display48bmpf(11,29,bmp_as1);
////					LCD_Display64bmp(11,45,bmp_as2);
////					LCD_Display48bmp(11,61,bmp_as3);
////					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 1)						  //���ҵ���
//			{				 
//					LCD_Display48bmp(11,29,bmp_as1);
//					LCD_Display64bmpf(11,45,bmp_as2);
////					LCD_Display48bmp(11,61,bmp_as3);
////					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 2)						  //�յ���
//			{
////					LCD_Display48bmp(11,29,bmp_as1);
//					LCD_Display64bmp(11,45,bmp_as2);
//					LCD_Display48bmpf(11,61,bmp_as3);
////					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 3)						  //��ˮ����
//			{
////					LCD_Display48bmp(11,29,bmp_as1);
////					LCD_Display64bmp(11,45,bmp_as2);
//					LCD_Display48bmp(11,61,bmp_as3);
//					LCD_Display64bmpf(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//			}
//			if (uiitemnumber == 4)						  //������
//			{
////					LCD_Display48bmp(11,29,bmp_as1);
////					LCD_Display64bmp(11,45,bmp_as2);
////					LCD_Display48bmp(11,61,bmp_as3);
//					LCD_Display64bmp(11,77,bmp_as4);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmpf(22,120,bmp_fhjk);	
//			}
//			break;
//		case 4:			//�ػ�ѡ��ҳ��
//			if (uiitemnumber == 0)						//�ػ�ѡ��
//				{
//					LCD_Display48bmpf(11,34,bmp_p1);
////					LCD_Display48bmp(11,50,bmp_p2);
////					LCD_Display48bmp(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 1)					   //����ѡ��
//				{
//					LCD_Display48bmp(11,34,bmp_p1);
//					LCD_Display48bmpf(11,50,bmp_p2);
////					LCD_Display48bmp(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//
//			if (uiitemnumber == 2)					   //����ѡ��
//				{
////					LCD_Display48bmp(11,34,bmp_p1);
//					LCD_Display48bmp(11,50,bmp_p2);
//					LCD_Display48bmpf(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
////					LCD_Display40bmp(22,120,bmp_fhjk);	
//				}
//			if (uiitemnumber == 3)					   //����ѡ��
//				{
////					LCD_Display48bmp(11,34,bmp_p1);
////					LCD_Display48bmp(11,50,bmp_p2);
//					LCD_Display48bmp(11,66,bmp_p3);
////					LCD_Display32bmp(4,120,bmp_qd);
//					LCD_Display40bmpf(22,120,bmp_fhjk);	
//				}
//	   	break;
//		case 6:	 //�ŵ�ҳ��˵�
//			if (uiitemnumber == 0)	//�ŵƿ���
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);///�ָ����ذ�ť
//					if (uidoorl_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1 )	//�ŵ�ҳ�涨ʱСʱλ
//				{
//					if (uidoorl_state_display ==0)
//						{
//							LCD_Display16bmp(18,36,bmp_dqg);	////ʹ��������
//						}
//					else
//						{
//							LCD_Display16bmp(18,36,bmp_dqk);
//						}
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 2 )	//�ŵ�ҳ�涨ʱ����λ
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 3 )	//�ŵ�ҳ�涨ʱ�����λ
//				{
//					LCD_PutNumberOnData(14,84,uitsminutefirst);
//					LCD_PutNumberOnData(15,84,uitsminutesecond);
//					if ( uitimingsetswitch ==1 )				 //ѡ����ʱ����
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
//					LCD_Display40bmpf(22,120,bmp_fhjk);///ѡ�����ذ�ť
//				}
//		break;
//		case 7:	   ///////���ҵƽ���/////////////////////
//			if (uiitemnumber == 0)	//���ҵƿ���
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);   ///�ָ����ذ�ť
//					if (uibedl_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1 )	//���ҵ�ҳ�涨ʱСʱλ
//				{
//					if (uibedl_state_display ==0)
//						{
//							LCD_Display16bmp(18,36,bmp_dqg);	 //ʹ��������
//						}
//					else
//						{
//							LCD_Display16bmp(18,36,bmp_dqk);
//						}
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 2 )	//���ҵ�ҳ�涨ʱ����λ
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 3 )	//���ҵ�ҳ�涨ʱ�����λ
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
//					if ( uitimingsetswitch ==1 )         //�ָ���ʱʱ�俪��
//					{
//						LCD_Display16bmp(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmp(19,84,bmp_dqg);
//					}
//					LCD_Display40bmpf(22,120,bmp_fhjk);///ѡ�����ذ�ť
//				}
//		break;
//	    case 8:	   ////�յ�����//////////////
//			if (uiitemnumber == 0)	//�յ�����
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);///�ָ����ذ�ť
//					if (uiair_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1)	//�յ��¶�
//				{
//					if (uiair_state_display ==0)
//						{
//							LCD_Display16bmp(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmp(18,36,bmp_dqk);
//						}                        ////////////�ָ�����״̬��///////////////
//					LCD_PutNumberOnDataf(14,52,uitemsetfirst_wat);
//					LCD_PutNumberOnDataf(15,52,uitemsetsecond_wat);
//				}
//			if (uiitemnumber == 2 )	//�յ�ҳ�涨ʱСʱλ
//				{
//					LCD_PutNumberOnData(14,52,uitemsetfirst_wat);
//					LCD_PutNumberOnData(15,52,uitemsetsecond_wat);////////ʹ�¶Ȼָ�
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 3 )	//�յ�ҳ�涨ʱλ
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 4 )	//�յ���ҳ�涨ʱ�����λ
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
//			if (uiitemnumber == 5)	//////////���ذ�ť/////////
//				{
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmp(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmp(19,84,bmp_dqg);
//					}
//					LCD_Display40bmpf(22,120,bmp_fhjk);///ѡ�����ذ�ť
//				}
//		break;
//		case 9:
//			if (uiitemnumber == 0)	//��ˮ������
//			   {
//				   	LCD_Display40bmp(22,120,bmp_fhjk);///�ָ����ذ�ť
//					if (uiwaterh_state_display ==0)
//						{
//							LCD_Display16bmpf(18,36,bmp_dqg);
//						}
//					else
//						{
//							LCD_Display16bmpf(18,36,bmp_dqk);
//						}
//				}
//			if (uiitemnumber == 1)	//��ˮ���¶�
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
//			if (uiitemnumber == 2 )	//��ˮ��ҳ�涨ʱСʱλ
//				{
//					LCD_PutNumberOnData(14,52,uitemsetfirst_wat);
//					LCD_PutNumberOnData(15,52,uitemsetsecond_wat);////////ʹ�¶Ȼָ�
//					LCD_PutNumberOnDataf(10,84,uitshourfirst);
//					LCD_PutNumberOnDataf(11,84,uitshoursecond);	
//				}
//			if (uiitemnumber == 3 )	//��ˮ��ҳ�涨ʱ����λ
//				{
//					LCD_PutNumberOnData(10,84,uitshourfirst);
//					LCD_PutNumberOnData(11,84,uitshoursecond);
//					LCD_PutNumberOnDataf(14,84,uitsminutefirst);
//					LCD_PutNumberOnDataf(15,84,uitsminutesecond);
//				}
//			if (uiitemnumber == 4 )	//��ˮ��ҳ�涨ʱ�����λ
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
//			if (uiitemnumber == 5)	//////////���ذ�ť/////////
//				{
//					if ( uitimingsetswitch ==1 )
//					{
//						LCD_Display16bmp(19,84,bmp_dqk);
//					}
//					else 
//					{
//						LCD_Display16bmp(19,84,bmp_dqg);
//					}
//					LCD_Display40bmpf(22,120,bmp_fhjk);///ѡ�����ذ�ť
//				}
//		break;
//		default:
//		break;
//	}	
//}
////========================================================================
//// ����: INT8U LCD_DisplayError(INT8U errortype)
//// ����: ��ʾ����ҳ��
//// ����: errortype ���������
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
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
// ����: INT8U LCD_DisplayWarning(INT8U uiwarningtype)
// ����: ��ʾ����ҳ��
// ����: warningtype ���������
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_DisplayWarning(INT8U uiwarningtype)
 {
 	INT8U m;
	INT8U i,j,col;
	switch (uiwarningtype)
	{
	case 1:		 //ú��й©����
		m=0;								 //����
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//��λ������ʼλ��
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(0x00);	//д����������
				m++;
			}
			col++;
		}

		m=0;								 //��ʾ����ͼƬ
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//��λͼƬ��ʾ��ʼλ��
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(bmp_jg[m]);	//д�뾯��ͼƬ����
				m++;
			}
			col++;
		}

		m=0;								//��ʾú��й©��������
		col=84;
		for(i=0;i<21;i++)				  
		{
			LCD_Locatexy(10,col);		    //��λ������ʾ��ʼλ��	
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<11;j++)
			{
				LCD_WriteData(bmp_mq[m]);	 //д��ú��й©��������
				m++;
			}
			col++;
		}
		m=0;								//��ʾ���������水ť
		col=120;
		for(i=0;i<24;i++)				  
		{
			LCD_Locatexy(20,col);		    //��λ���ذ�ť��ʼλ��
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<6;j++)
			{
				LCD_WriteData(bmp_jgfh[m]);	 //д�뷵�ذ�ť����
				m++;
			}
			col++;
		}
		break;
	case 2:	 //С͵���뾯��
		m=0;								 //����
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//��λ������ʼλ��
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(0x00);	//д����������
				m++;
			}
			col++;
		}

		m=0;								 //��ʾ����ͼƬ
		col=20;
		for(i=0;i<60;i++)				  
		{
			LCD_Locatexy(11,col);			//��λͼƬ��ʾ��ʼλ��
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<9;j++)
			{
				LCD_WriteData(bmp_jg[m]);	  //д��ͼƬ����
				m++;
			}
			col++;
		}
		m=0;								//��ʾú��й©��������
		col=84;
		for(i=0;i<21;i++)				  
		{
			LCD_Locatexy(10,col);		   //��λ������ʾ��ʼλ��
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<11;j++)
			{
				LCD_WriteData(bmp_xt[m]);	 //д����������
				m++;
			}
			col++;
		}
		m=0;								//��ʾ���������水ť
		col=120;
		for(i=0;i<24;i++)				  
		{
			LCD_Locatexy(20,col);		   //��λ���ذ�ť��ʼλ��
		    LCD_WriteCommand(0x4c);
		    LCD_WriteCommand(0x42);
			for(j=0;j<6;j++)
			{
				LCD_WriteData(bmp_jgfh[m]);	 //д�밴ť����
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

