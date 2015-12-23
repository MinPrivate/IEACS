/******************************************************************************
*						文件名：	NMRQ_lcd240160.c	
*                       文件描述：	本文件包括LCD模块驱动程序，内部函数以及接口函数，主要负责下位机端的显示  
*                       作者：		林鹏
*						创建时间： 	2013-8-1
******************************************************************************/


#include <lpc2103.h>
#include "..\Include\helper.h"
#include "..\Include\NMRQ_config.h"
#include "..\Include\NMRQ_lcd_zimo.h"

extern	TIME			*LCDSetTime;					/*	时间设置时使用的全局变量	*/
extern	INT8U			 LCDSetElecSW;					/*	电器设置时使用的电器开关变量	*/
extern	INT8U			 LCDSetElecTemp;				/*	电器设置时使用的电器温度变量	*/
extern	INT8U			 LCDSetElecTimingHour;			/*	电器设置时使用的电器定时变量	*/
extern	INT8U			 LCDSetElecTimingMin;			/*	电器设置时使用的电器定时变量	*/
extern	INT8U			 LCDSetElecTimingSW;			/*	电器设置时使用的电器定时变量	*/
extern	BOOLEAN			 LCDSetElecTimingEnable;		/*	电器设置时使用的电器定时变量	*/

void LCD_WriteCommand(INT8U cmd);
void LCD_WriteData(INT8U data);
void LCD_Init(void);
void LCD_Clear(void);
//void LCD_PutHZ(INT8U col,INT8U row,INT8U HZcode);
//void LCD_Locatexy(INT8U x,INT8U y);
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
	INT32U i;
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
	for(i = 32765;i>0;i--)
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
////==============================================================================
//// 函数: void LCD_PutHZ(INT8U uicol,INT8U uirow,INT8U uiHZcode)
//// 描述: 以横坐标为col,纵坐标为row的点为起点显示一个汉字 汉字大小为22X22
//// 参数: col X 轴坐标 row Y 轴坐标  HZcode 字符在字符库中的偏移量
//// 返回: 无
//// 版本:
////========================================================================
//void LCD_PutHZ(INT8U uicol,INT8U uirow,const INT8U uiHZcode)
//{
//	INT8U i,j;
//	INT32U  x;
//	x = 0x42*uiHZcode;
//	LCD_WriteCommand(0x4c);
//	for(i=0;i<22;i++)
//	{
//		LCD_Locatexy(uicol,uirow);
//		LCD_WriteCommand(0x42);
//		for(j=0;j<3;j++)
//		{
//			LCD_WriteData(bmp_HZTable[x]);
//			x++;
//		}
//		uirow++;
//	}
//}
//=====================================================================================================================================
// 函数: void LCD_Displaybmp (unsigned char uibmpx,unsignedchar uibmpy,unsigned char uirow,unsigned char uicol)
// 描述: 在LCD 的真实坐标系上清屏
// 参数:  uirow  横坐标  uicol 纵坐标 uibmpx 屏长  uibmpy 屏宽
// 返回: 无
// 版本:
//======================================================================================================================================
void LCD_Displayemptybmp (unsigned char uibmpx,unsigned char uibmpy,unsigned char uirow,unsigned char uicol)
{
	unsigned char k,yu;
	unsigned char i,j;
	unsigned short m=0;
	yu=(uibmpx)%8;
	k=(uibmpx)/8;
	if (yu==0)
	{
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k;j++)
			{
				LCD_WriteData(0x00);
				m++;
			}
			uicol++;
		 }
	}
	else
	{   
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k+1;j++)
			{
				LCD_WriteData(0x00);
				m++;
			}
			uicol++;
		 }
	}
}
//=====================================================================================================================================
// 函数: void LCD_Displaybmp (INT8U uibmpx,unsignedchar uibmpy,INT8U uirow,INT8U uicol,INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张图片
// 参数: *putbmp 图片数组地址指针 uirow  横坐标  uicol 纵坐标 uibmpx 图的长  uibmpy 图的宽
// 返回: 无
// 版本:
//======================================================================================================================================
void LCD_Displaybmp (INT8U uibmpx,INT8U uibmpy,INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m,k,yu;
	INT8U i,j;
	m=0;
	yu=(uibmpx)%8;
	k=(uibmpx)/8;
	if (yu==0)
	{
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k;j++)
			{
				LCD_WriteData(putbmp[m]);
				m++;
			}
			uicol++;
		 }
	}
	else
	{   
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k+1;j++)
			{
				LCD_WriteData(putbmp[m]);
				m++;
			}
			uicol++;
		 }
	}
}
//=====================================================================================================================================
// 函数: void LCD_Displaybmp (INT8U uibmpx,unsignedchar uibmpy,INT8U uirow,INT8U uicol,INT8U  *putbmp)
// 描述: 在LCD 的真实坐标系上绘制一张图片的取反
// 参数: *putbmp 图片数组地址指针 uirow  横坐标  uicol 纵坐标 uibmpx 图的长  uibmpy 图的宽
// 返回: 无
// 版本:
//======================================================================================================================================
void LCD_Displaybmpf (INT8U uibmpx,INT8U uibmpy,INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m,k,yu;
	INT8U i,j;
	m=0;
	yu=(uibmpx)%8;
	k=(uibmpx)/8;
	if (yu==0)
	{
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k;j++)
			{
				LCD_WriteData(~putbmp[m]);
				m++;
			}
			uicol++;
		 }
	}
	else
	{   
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k+1;j++)
			{
				LCD_WriteData(~putbmp[m]);
				m++;
			}
			uicol++;
		 }
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
////========================================================================
//// 函数: INT16U LCD_PowerOn()
//// 描述: 开机显示画面
//// 参数: 无  
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
//INT8U LCD_PowerOn()
//{
//	LCD_Clear();
//	LCD_PutHZ(3,48,0); //显示智
//	LCD_PutHZ(6,48,1); //显示能
//	LCD_PutHZ(9,48,2); //显示家
//	LCD_PutHZ(12,48,3);//显示电
//	LCD_PutHZ(15,48,4);//显示控
//	LCD_PutHZ(18,48,5);//显示制
//	LCD_PutHZ(21,48,6);//显示系
//	LCD_PutHZ(24,48,7);//显示统
//	LCD_PutHZ(9,71,8); //显示欢
//	LCD_PutHZ(12,71,9);//显示迎
//	LCD_PutHZ(15,71,10);//显示您
//	LCD_PutHZ(18,71,15);//显示！
//	return 1;
//}
////========================================================================
//// 函数: INT8U LCD_PowerOff()
//// 描述: 显示关机页面
//// 参数: 无
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
//INT8U LCD_PowerOff()
//{
//	LCD_Clear();
//	LCD_PutHZ(3,48,0); //显示智
//	LCD_PutHZ(6,48,1); //显示能
//	LCD_PutHZ(9,48,2); //显示家
//	LCD_PutHZ(12,48,3);//显示电
//	LCD_PutHZ(15,48,4);//显示控
//	LCD_PutHZ(18,48,5);//显示制
//	LCD_PutHZ(21,48,6);//显示系
//	LCD_PutHZ(24,48,7);//显示统
//	LCD_PutHZ(3,71,8); //显示欢
//	LCD_PutHZ(6,71,9); //显示迎
//	LCD_PutHZ(9,71,10);//显示您
//	LCD_PutHZ(12,71,11);//显示下
//	LCD_PutHZ(15,71,12);//显示次
//	LCD_PutHZ(18,71,13);//显示使
//	LCD_PutHZ(21,71,14);//显示用
//	LCD_PutHZ(24,71,15);//显示！
//	return 1;	
//}
//========================================================================
// 函数: INT8U LCD_DispalyMainScreen()
// 描述: 显示下位机端主界面
// 参数: 无
// 返回: success 函数执行成功
//		 fault   函数执行失败
// 版本:
//========================================================================
 INT8U LCD_DisplayMainScreen()
 {
    LCD_Clear();
	LCD_Displaybmp(8,26,6,12,bmp_zf);	    //主界面时间分号
	LCD_Displaybmp(24,12,4,41,bmp_xq);		//主界面星期
	LCD_Displaybmp(12,12,5,55,bmp_n);		//主界面年
	LCD_Displaybmp(12,12,9,55,bmp_y);		//主界面月
	LCD_Displaybmp(12,12,13,55,bmp_r);		//主界面日
    LCD_Displaybmp(128,19,13,16,bmp_znz);	//主界智能家电控制系统
	LCD_Displaybmp(42,14,17,38,bmp_wd);		//主界面温度
	LCD_Displaybmp(16,14,25,38,bmp_wdf);	//主界面温度符号
	LCD_Displaybmp(42,14,17,55,bmp_gq);		//主界面光强
	LCD_Displaybmp(7,14,25,55,bmp_gqf);		//主界面光强符号
	LCD_Displaybmp(60,12,3,80,bmp_md);		//主界面门灯状态
	LCD_Displaybmp(60,12,3,96,bmp_kt);		//主界面空调状态
	LCD_Displaybmp(78,12,16,80,bmp_wsd);	//主界面卧室灯状态
	LCD_Displaybmp(78,12,16,96,bmp_rsq);	//主界面热水器
	LCD_Displaybmp(64,24,3,119,bmp_cd);		//主界面菜单设置
	LCD_Displaybmp(64,24,17,119,bmp_dq);	//主界面电器设置
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
	if (uidoorl_state == OS_ELEC_SWITCH_STATE_ON)
	{
		LCD_Displayemptybmp(16,16,10,78);
		LCD_Displaybmp(16,16,10,78,bmp_16y);//门灯状态开
	}
	else
	{
		LCD_Displayemptybmp(16,16,10,78);
	}
	if (uibedl_state ==OS_ELEC_SWITCH_STATE_ON)
	{
		LCD_Displayemptybmp(16,16,25,78);
		LCD_Displaybmp(16,16,25,78,bmp_16y);//卧室灯状态开    
	}
	else
	{
	    LCD_Displayemptybmp(16,16,25,78);
	}
	if (uiair_state == OS_ELEC_SWITCH_STATE_ON )
	{
		LCD_Displayemptybmp(16,16,10,93);
		LCD_Displaybmp(16,16,10,93,bmp_16y);//空调状态开
	}
	else
	{
	    LCD_Displayemptybmp(16,16,10,93);
	}
	if(uiwaterh_state == OS_ELEC_SWITCH_STATE_ON)
	{
		LCD_Displayemptybmp(16,16,25,93);
		LCD_Displaybmp(16,16,25,93,bmp_16y);//热水器状态开
	}
	else
	{
		LCD_Displayemptybmp(16,16,25,93);
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
 	if (uiConnectdata == 1 )		   
	{
		LCD_Displayemptybmp(16,16,0,0);
		LCD_Displaybmp(16,16,0,0,bmp_9y);//刷新状态图片
		LCD_Displaybmp(68,10,2,0,bmp_ycl);//显示远程控制已连接
	}
	else 
	{
		LCD_Displaybmp(68,10,2,0,bmp_ycw); //显示未连接
	}
	return 	1;
 }	
//========================================================================
// 函数: INT8U LCD_UpdateTIME(INT8U uihourfirst,INT8U uihoursecond,INT8U uiminutefirst,INT8U uiminutesecond)
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
// 函数: INT8U LCD_Update(INT8U uiyearfirst,INT8U uiyearsecond,INT8U uiyearthird,INT8U uiyearforth,INT8U uimonthfirst,INT8U uimonthsecond,INT8U uidayfirst,INT8U uidaysecond)
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
// 函数: INT8U LCD_Update(INT8U uicsyearfirst,INT8U uicsyearsecond,INT8U uicsyearthird,INT8U uicsyearforth,INT8U uicsmonthfirst,INT8U uicsmonthsecond,INT8U uicsdayfirst,INT8U uicsdaysecond)
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
////==========================================================================
//// 函数: INT8U LCD_UpdateTemSetAir(INT8U uitemsetfirst_air,INT8U uitemsetsecond_air)
//// 描述: 更新空调信息页面温度设定
//// 参数: uitemsetfirst_air  温度设置第一位   uitemsetsecond_air  温度设置第二位 
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////===========================================================================
//INT8U LCD_UpdateTemSetTem(INT8U uitemsetfirst,INT8U uitemsetsecond)
//{
//	LCD_PutNumberOnData(14,52,uitemsetfirst);
//	LCD_PutNumberOnData(15,52,uitemsetsecond);
//	return 1;
//}
////==========================================================================
//// 函数: INT8U LCD_UpdateTimingSet(INT8U uitshourfirst,INT8U uitshoursecond,INT8U uitsminutefirst,INT8U uitsminutesecond,INT8U uitimingsetswitch)
//// 描述: 更新电器信息页面定时时间
//// 参数: uitshourfirst   定时时间小时第一位   uitshoursecond  定时时间小时第二位  uitsminutefirst 定时分钟第一位  uitsminutesecond 定时分钟第二位  
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////===========================================================================
//INT8U LCD_UpdateTimingSet(INT8U uitshourfirst,INT8U uitshoursecond,INT8U uitsminutefirst,INT8U uitsminutesecond,INT8U uitimingsetswitch)
//{
//	LCD_PutNumberOnData(10,84,uitshourfirst);
//	LCD_PutNumberOnData(11,84,uitshoursecond);
//	LCD_PutNumberOnData(14,84,uitsminutefirst);
//	LCD_PutNumberOnData(15,84,uitsminutesecond);
//	if ( uitimingsetswitch ==1 )
//	{
//		LCD_Displaybmp(16,16,19,84,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,19,84,bmp_dqg);
//	}
//	return 1;
//}
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
 	LCD_Clear();
	LCD_Displaybmp(16,16,11,29,bmp_x1);
	LCD_Displaybmp(32,16,13,29,bmp_moshi);
	LCD_Displaybmp(32,16,17,29,bmp_m1);		//显示模式选择

	LCD_Displaybmp(16,16,11,45,bmp_x2);
	LCD_Displaybmp(32,16,13,45,bmp_m2sz);
	LCD_Displaybmp(32,16,17,45,bmp_m3sz);  	//显示时钟设置

	LCD_Displaybmp(16,16,11,61,bmp_x3);
	LCD_Displaybmp(32,16,13,61,bmp_m3dq);
	LCD_Displaybmp(32,16,17,61,bmp_m3sz);  //显示电器设置

	LCD_Displaybmp(16,16,11,77,bmp_x4);
	LCD_Displaybmp(32,16,13,77,bmp_m4);
	LCD_Displaybmp(32,16,17,77,bmp_m1);	   	//显示关机选择

	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
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
 	LCD_Clear();
	LCD_Displaybmp(16,16,11,29,bmp_x1);
	LCD_Displaybmp(32,16,13,29,bmp_ms1);
	LCD_Displaybmp(32,16,17,29,bmp_moshi);	//显示工作模式
	
	LCD_Displaybmp(16,16,11,45,bmp_x2);
	LCD_Displaybmp(32,16,13,45,bmp_ms2);
	LCD_Displaybmp(32,16,17,45,bmp_moshi);	//显示回家模式

	LCD_Displaybmp(16,16,11,61,bmp_x3);
	LCD_Displaybmp(32,16,13,61,bmp_ms3);
	LCD_Displaybmp(32,16,17,61,bmp_moshi);	//显示防盗模式

	LCD_Displaybmp(16,16,11,77,bmp_x4);
	LCD_Displaybmp(32,16,13,77,bmp_ms4);
	LCD_Displaybmp(32,16,17,77,bmp_moshi);	//显示外出模式
	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
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
 	LCD_Clear();
	LCD_Displaybmp(32,16,5,48,bmp_szrq);		  //显示日期
 	LCD_Displaybmp(8,16,9,48,bmp_szfh);		  //显示：
	LCD_Displaybmp(16,16,14,48,bmp_dqn); 	//显示年
	LCD_Displaybmp(16,16,18,48,bmp_dqy);		 //显示月
	LCD_Displaybmp(16,16,22,48,bmp_dqr);		 //显示日
	LCD_Displaybmp(32,16,5,65,bmp_szsj);		 //显示时间
	LCD_Displaybmp(8,16,9,65,bmp_szfh);		  //显示：
	LCD_Displaybmp(16,16,12,65,bmp_dqs);		 //显示时
	LCD_Displaybmp(16,16,16,65,bmp_dqf);		 //显示分
	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
	return 	1;
 }
////========================================================================
//// 函数: INT8U LCD_DisplayApplianceSet()
//// 描述: 显示电器设置页面  即为显示选择哪个电器的页面
//// 参数: 无  
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
// INT8U LCD_DisplayApplianceSet()
// {
// 	LCD_Clear();
//	LCD_Displaybmp(16,16,11,29,bmp_x1);
//	LCD_Displaybmp(32,16,13,29,bmp_as1);
//
//	LCD_Displaybmp(16,16,11,45,bmp_x2);
//	LCD_Displaybmp(48,16,13,45,bmp_as2);
//
//	LCD_Displaybmp(16,16,11,61,bmp_x3);
//	LCD_Displaybmp(32,16,13,61,bmp_as3);
//
//	LCD_Displaybmp(16,16,11,77,bmp_x4);
//	LCD_Displaybmp(48,16,13,77,bmp_as4);
//
//	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// 函数: INT8U LCD_DisplayDoorl(INT8U uidoorl_state_display)
//// 描述: 显示门灯页面
//// 参数: uidoorl_state_disaplay    表示门灯电器当前的状态
////       不能直接读取系统状态表 进入电器显示界面后会把电器当前状态赋给这个变量  
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
// INT8U LCD_DisplayDoorl(INT8U uidoorl_state_display)
// {
// 	LCD_Clear();
// 	LCD_Displaybmp(32,16,9,20,bmp_as1);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uidoorl_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//显示定时
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //显示时间
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//显示：
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //显示分
//	LCD_Displaybmp(38,21,22,115,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// 函数: INT8U LCD_DisplayBedl(INT8U uibedl_state_display)
//// 描述: 显示卧室灯页面
//// 参数: uibedl_state_display 卧室灯电器当前的状态  
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
// INT8U LCD_DisplayBedl(INT8U uibedl_state_display)
// {
// 	LCD_Clear();
//	LCD_Displaybmp(48,16,9,20,bmp_as2);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uibedl_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//显示定时
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //显示时间
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//显示：
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //显示分
//	LCD_Displaybmp(38,21,22,115,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// 函数: INT8U LCD_DisplayAir_condition(INT8U uiair_state_display)
//// 描述: 显示空调页面
//// 参数: uiair_state_display 空调当前状态 
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
// INT8U LCD_DisplayAir_condition(INT8U uiair_state_display)
// {
// 	LCD_Clear();
//	LCD_Displaybmp(32,16,9,20,bmp_as3);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uiair_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,52,bmp_dqwd);	   //显示温度字样
//	LCD_Displaybmp(8,16,13,52,bmp_szfh);	   //显示：
//	LCD_Displaybmp(16,14,16,52,bmp_wdf);		//显示温度符号
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//显示定时
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //显示时间
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//显示：
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //显示分
//	LCD_Displaybmp(38,21,22,115,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// 函数: INT8U LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
//// 描述: 显示热水器页面
//// 参数: uiwaterh_state_display 热水器当前状态 
//// 返回: success 函数执行成功
////		 fault   函数执行失败
//// 版本:
////========================================================================
// INT8U  LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
// {
//	LCD_Clear();
//	LCD_Displaybmp(48,16,9,20,bmp_as4);//LCD_Display48bmp(9,20,bmp_dqrsq);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uiwaterh_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,52,bmp_dqwd);	   //显示温度字样
//	LCD_Displaybmp(8,16,13,52,bmp_szfh);	   //显示：
//	LCD_Displaybmp(16,14,16,52,bmp_wdf);		//显示温度符号
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//显示定时
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //显示时间
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//显示：
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //显示分
//	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
//	return 	1;
// }
//========================================================================
// 函数: INT8U LCD_DisplayPowerOffSelect()
// 描述: 显示关机选择页面
// 参数: 无  
// 返回: success 函数执行成功
//		 fault   函数执行失败
//========================================================================
 INT8U LCD_DisplayPowerOffSelect()
 {
 	LCD_Clear();
	LCD_Displaybmp(16,16,11,34,bmp_x1);
	LCD_Displaybmp(32,16,13,34,bmp_m4);	  //显示关机
	LCD_Displaybmp(16,16,11,50,bmp_x2);
	LCD_Displaybmp(32,16,13,50,bmp_p2);	  //显示重启
	LCD_Displaybmp(16,16,11,66,bmp_x3);
	LCD_Displaybmp(32,16,13,66,bmp_p3);	  //显示待机
	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
	return 	1;
 }
//==================================================================================
// 函数: INT8U LCD_SelectMenuSetItem(INT8U menupagenumber,INT8U itemnumber)
// 描述: 显示菜单设置当前的菜单项
// 参数: menunumber 菜单编号 itemnumber 菜单项编号  
// 返回: success 函数执行成功
//		 fault   函数执行失败
//=====================================================================================
INT8U LCD_SelectMenuSetItem(INT8U uimenupagenumber,INT8U uiitemnumber)
{
	switch(uimenupagenumber)
	{
	 	case 1:	  //菜单设置页面
			if (uiitemnumber == 0)
				{
					LCD_Displaybmp(38,21,22,120,bmp_fhjk); 	  //恢复返回按钮
					LCD_Displaybmpf(16,16,11,29,bmp_x1);	  
					LCD_Displaybmpf(32,16,13,29,bmp_moshi);
					LCD_Displaybmpf(32,16,17,29,bmp_m1);	 //显示模式选择
						 
				}
			if (uiitemnumber == 1)
				{
					LCD_Displaybmp(16,16,11,29,bmp_x1);		  //恢复模式选择
					LCD_Displaybmp(32,16,13,29,bmp_moshi);
					LCD_Displaybmp(32,16,17,29,bmp_m1);
					LCD_Displaybmpf(16,16,11,45,bmp_x2);
					LCD_Displaybmpf(32,16,13,45,bmp_m2sz);
					LCD_Displaybmpf(32,16,17,45,bmp_m3sz);	  //显示时钟设置
				}
			if (uiitemnumber == 2)
				{
					LCD_Displaybmp(16,16,11,45,bmp_x2);		 //恢复时钟设置
					LCD_Displaybmp(32,16,13,45,bmp_m2sz);
					LCD_Displaybmp(32,16,17,45,bmp_m3sz);
					LCD_Displaybmpf(16,16,11,61,bmp_x3);
					LCD_Displaybmpf(32,16,13,61,bmp_m3dq);
					LCD_Displaybmpf(32,16,17,61,bmp_m3sz);  //显示电器设置
				}
			if (uiitemnumber == 3)
				{
					LCD_Displaybmp(16,16,11,61,bmp_x3);
					LCD_Displaybmp(32,16,13,61,bmp_m3dq);
					LCD_Displaybmp(32,16,17,61,bmp_m3sz);  //恢复电器设置
					LCD_Displaybmpf(16,16,11,77,bmp_x4);
					LCD_Displaybmpf(32,16,13,77,bmp_m4);
					LCD_Displaybmpf(32,16,17,77,bmp_m1);	 //显示关机选择	
				}
			if (uiitemnumber == 4)
				{
					LCD_Displaybmp(16,16,11,77,bmp_x4);
					LCD_Displaybmp(32,16,13,77,bmp_m4);
					LCD_Displaybmp(32,16,17,77,bmp_m1);	     //恢复关机选择
					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //显示返回按钮
				}
			break;
		default:
			break;
	}
}
//==================================================================================
// 函数: INT8U LCD_SelectMedelSelectItem(INT8U menupagenumber,INT8U itemnumber)
// 描述: 显示模式选择当前的菜单项
// 参数: menunumber 菜单编号 itemnumber 菜单项编号  
// 返回: success 函数执行成功
//		 fault   函数执行失败
//=====================================================================================
//INT8U LCD_SelectMedelSelectItem(INT8U uimenupagenumber,INT8U uiitemnumber)
//{
//	switch(uimenupagenumber)
//	{
//	 	case 2:			/////模式选择页面
//			if (uiitemnumber == 0)
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //恢复返回按钮
//					LCD_Displaybmpf(16,16,11,29,bmp_x1);
//					LCD_Displaybmpf(32,16,13,29,bmp_ms1);
//					LCD_Displaybmpf(32,16,17,29,bmp_moshi);	//显示工作模式	
//				}
//			if (uiitemnumber == 1)							  //回家模式
//				{
//					LCD_Displaybmp(16,16,11,29,bmp_x1);
//					LCD_Displaybmp(32,16,13,29,bmp_ms1);
//					LCD_Displaybmp(32,16,17,29,bmp_moshi);	//恢复工作模式
//					LCD_Displaybmpf(16,16,11,45,bmp_x2);
//					LCD_Displaybmpf(32,16,13,45,bmp_ms2);
//					LCD_Displaybmpf(32,16,17,45,bmp_moshi);	//显示回家模式	
//				}
//			if (uiitemnumber == 2)							 //防盗模式
//				{
//					LCD_Displaybmp(16,16,11,45,bmp_x2);
//					LCD_Displaybmp(32,16,13,45,bmp_ms2);
//					LCD_Displaybmp(32,16,17,45,bmp_moshi);	//恢复回家模式
//					LCD_Displaybmpf(16,16,11,61,bmp_x3);
//					LCD_Displaybmpf(32,16,13,61,bmp_ms3);
//					LCD_Displaybmpf(32,16,17,61,bmp_moshi);	//显示防盗模式	
//				}
//			if (uiitemnumber == 3)							 //外出模式
//				{
//					LCD_Displaybmp(16,16,11,61,bmp_x3);
//					LCD_Displaybmp(32,16,13,61,bmp_ms3);
//					LCD_Displaybmp(32,16,17,61,bmp_moshi);	//恢复防盗模式
//					LCD_Displaybmpf(16,16,11,77,bmp_x4);
//					LCD_Displaybmpf(32,16,13,77,bmp_ms4);
//					LCD_Displaybmpf(32,16,17,77,bmp_moshi);	//显示外出模式	
//				}
//			if (uiitemnumber == 4)							 //返回按钮
//				{
//					LCD_Displaybmp(16,16,11,77,bmp_x4);
//					LCD_Displaybmp(32,16,13,77,bmp_ms4);
//					LCD_Displaybmp(32,16,17,77,bmp_moshi);	//恢复外出模式
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//显示返回按钮
//				}
//			break;
//		default:
//			break;
//	}
//}
////==================================================================================
//// 函数: INT8U LCD_SelectMenuItem(INT8U menupagenumber,INT8U itemnumber)
//// 描述: 显示当前的菜单项
//// 参数: menunumber 菜单编号 itemnumber 菜单项编号  
//// 返回: success 函数执行成功
////		 fault   函数执行失败
////=====================================================================================
//INT8U LCD_SelectMenuItem(INT8U uimenupagenumber,INT8U uiitemnumber)
//{
//	switch(uimenupagenumber)
//	{
//	 	case 1:	  //菜单设置页面
//			if (uiitemnumber == 0)
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk); 	  //恢复返回按钮
//					LCD_Displaybmpf(16,16,11,29,bmp_x1);	  
//					LCD_Displaybmpf(32,16,13,29,bmp_moshi);
//					LCD_Displaybmpf(32,16,17,29,bmp_m1);	 //显示模式选择
//						 
//				}
//			if (uiitemnumber == 1)
//				{
//					LCD_Displaybmp(16,16,11,29,bmp_x1);		  //恢复模式选择
//					LCD_Displaybmp(32,16,13,29,bmp_moshi);
//					LCD_Displaybmp(32,16,17,29,bmp_m1);
//					LCD_Displaybmpf(16,16,11,45,bmp_x2);
//					LCD_Displaybmpf(32,16,13,45,bmp_m2sz);
//					LCD_Displaybmpf(32,16,17,45,bmp_m3sz);	  //显示时钟设置
//				}
//			if (uiitemnumber == 2)
//				{
//					LCD_Displaybmp(16,16,11,45,bmp_x2);		 //恢复时钟设置
//					LCD_Displaybmp(32,16,13,45,bmp_m2sz);
//					LCD_Displaybmp(32,16,17,45,bmp_m3sz);
//					LCD_Displaybmpf(16,16,11,61,bmp_x3);
//					LCD_Displaybmpf(32,16,13,61,bmp_m3dq);
//					LCD_Displaybmpf(32,16,17,61,bmp_m3sz);  //显示电器设置
//				}
//			if (uiitemnumber == 3)
//				{
//					LCD_Displaybmp(16,16,11,61,bmp_x3);
//					LCD_Displaybmp(32,16,13,61,bmp_m3dq);
//					LCD_Displaybmp(32,16,17,61,bmp_m3sz);  //恢复电器设置
//					LCD_Displaybmpf(16,16,11,77,bmp_x4);
//					LCD_Displaybmpf(32,16,13,77,bmp_m4);
//					LCD_Displaybmpf(32,16,17,77,bmp_m1);	 //显示关机选择	
//				}
//			if (uiitemnumber == 4)
//				{
//					LCD_Displaybmp(16,16,11,77,bmp_x4);
//					LCD_Displaybmp(32,16,13,77,bmp_m4);
//					LCD_Displaybmp(32,16,17,77,bmp_m1);	     //恢复关机选择
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //显示返回按钮
//				}
//			break;
//		case 2:			/////模式选择页面
//			if (uiitemnumber == 0)
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //恢复返回按钮
//					LCD_Displaybmpf(16,16,11,29,bmp_x1);
//					LCD_Displaybmpf(32,16,13,29,bmp_ms1);
//					LCD_Displaybmpf(32,16,17,29,bmp_moshi);	//显示工作模式	
//				}
//			if (uiitemnumber == 1)							  //回家模式
//				{
//					LCD_Displaybmp(16,16,11,29,bmp_x1);
//					LCD_Displaybmp(32,16,13,29,bmp_ms1);
//					LCD_Displaybmp(32,16,17,29,bmp_moshi);	//恢复工作模式
//					LCD_Displaybmpf(16,16,11,45,bmp_x2);
//					LCD_Displaybmpf(32,16,13,45,bmp_ms2);
//					LCD_Displaybmpf(32,16,17,45,bmp_moshi);	//显示回家模式	
//				}
//			if (uiitemnumber == 2)							 //防盗模式
//				{
//					LCD_Displaybmp(16,16,11,45,bmp_x2);
//					LCD_Displaybmp(32,16,13,45,bmp_ms2);
//					LCD_Displaybmp(32,16,17,45,bmp_moshi);	//恢复回家模式
//					LCD_Displaybmpf(16,16,11,61,bmp_x3);
//					LCD_Displaybmpf(32,16,13,61,bmp_ms3);
//					LCD_Displaybmpf(32,16,17,61,bmp_moshi);	//显示防盗模式	
//				}
//			if (uiitemnumber == 3)							 //外出模式
//				{
//					LCD_Displaybmp(16,16,11,61,bmp_x3);
//					LCD_Displaybmp(32,16,13,61,bmp_ms3);
//					LCD_Displaybmp(32,16,17,61,bmp_moshi);	//恢复防盗模式
//					LCD_Displaybmpf(16,16,11,77,bmp_x4);
//					LCD_Displaybmpf(32,16,13,77,bmp_ms4);
//					LCD_Displaybmpf(32,16,17,77,bmp_moshi);	//显示外出模式	
//				}
//			if (uiitemnumber == 4)							 //返回按钮
//				{
//					LCD_Displaybmp(16,16,11,77,bmp_x4);
//					LCD_Displaybmp(32,16,13,77,bmp_ms4);
//					LCD_Displaybmp(32,16,17,77,bmp_moshi);	//恢复外出模式
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//显示返回按钮
//				}
//			break;
//		case 5:				 //时钟设置界面
//			if (uiitemnumber == 0)								///选定时钟设置界面年
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);    		///恢复返回按钮
//					LCD_PutNumberOnDataf(10,48,(LCDSetTime->uiTimeYear)/1000);	//选定年的第一位
//					LCD_PutNumberOnDataf(11,48,((LCDSetTime->uiTimeYear)%1000)/100);	//选定年的第二位
//					LCD_PutNumberOnDataf(12,48,((LCDSetTime->uiTimeYear)%100)/10);	//选定年的第三位
//					LCD_PutNumberOnDataf(13,48,(LCDSetTime->uiTimeYear)%10);	//选定年的第四位			 	
//				}
//			if (uiitemnumber == 1)							   /////选定时钟设置界面月
//				{
//					LCD_PutNumberOnData(10,48,(LCDSetTime->uiTimeYear)/1000);	//恢复年的第一位
//					LCD_PutNumberOnData(11,48,((LCDSetTime->uiTimeYear)%1000)/100);	//恢复年的第二位
//					LCD_PutNumberOnData(12,48,((LCDSetTime->uiTimeYear)%100)/10);	//恢复年的第三位
//					LCD_PutNumberOnData(13,48,(LCDSetTime->uiTimeYear)%10);	//恢复年的第四位
//					LCD_PutNumberOnDataf(16,48,(LCDSetTime->uiTimeMonth)/10);	//选定月的第一位
//					LCD_PutNumberOnDataf(17,48,(LCDSetTime->uiTimeMonth)%10); //选定月的第二位			 	
//				}
//			if (uiitemnumber ==2)	   ///日/////////
//				{
//				 	LCD_PutNumberOnData(16,48,(LCDSetTime->uiTimeMonth)/10);	//恢复月的第一位
//					LCD_PutNumberOnData(17,48,(LCDSetTime->uiTimeMonth)%10); //恢复月的第二位
//					LCD_PutNumberOnDataf(20,48,(LCDSetTime->uiTimeDay)/10);	 //选定天的第一位
//					LCD_PutNumberOnDataf(21,48,(LCDSetTime->uiTimeDay)%10);	 //选定天的第二位
//				}
//			if (uiitemnumber ==3)	 /////时/////////
//				{
//				 	LCD_PutNumberOnData(20,48,(LCDSetTime->uiTimeDay)/10);	 //恢复天的第一位
//					LCD_PutNumberOnData(21,48,(LCDSetTime->uiTimeDay)%10);	 //恢复天的第二位
//					LCD_PutNumberOnDataf(10,65,(LCDSetTime->uiTimeHour)/10);	 //选定小时的第一位
//					LCD_PutNumberOnDataf(11,65,(LCDSetTime->uiTimeHour)%10);	 //选定小时的第二位
//				}
//			if (uiitemnumber ==4)  /////////分/////////////
//				{
//				 	LCD_PutNumberOnData(10,65,(LCDSetTime->uiTimeHour)/10);	 //恢复小时的第一位
//					LCD_PutNumberOnData(11,65,(LCDSetTime->uiTimeHour)%10);	 //恢复小时的第二位
//					LCD_PutNumberOnDataf(14,65,(LCDSetTime->uiTimeMinute)/10);  //选定分钟的第一位
//					LCD_PutNumberOnDataf(15,65,(LCDSetTime->uiTimeMinute)%10); //选定分钟的第二位
//				}
//			if (uiitemnumber ==5)  ///////返回按钮//////////
//				{
//					LCD_PutNumberOnData(14,65,(LCDSetTime->uiTimeMinute)/10);  //恢复分钟的第一位
//					LCD_PutNumberOnData(15,65,(LCDSetTime->uiTimeMinute)%10); //恢复分钟的第二位
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);			  //选定返回按钮
//				}	
//	 		break;
//		case 3:		   ///电器设置页面
//			if (uiitemnumber == 0)						  
//			{
//						LCD_Displaybmp(38,21,22,120,bmp_fhjk);//恢复返回按钮
//						LCD_Displaybmpf(16,16,11,29,bmp_x1);
//						LCD_Displaybmpf(32,16,13,29,bmp_as1);  //显示门灯项
//			}
//			if (uiitemnumber == 1)						  
//			{				 
//						LCD_Displaybmp(16,16,11,29,bmp_x1);
//						LCD_Displaybmp(32,16,13,29,bmp_as1);  //恢复门灯项
//						LCD_Displaybmpf(16,16,11,45,bmp_x2);
//						LCD_Displaybmpf(48,16,13,45,bmp_as2);   //选定卧室灯		
//			}
//			if (uiitemnumber == 2)						  
//			{
//						LCD_Displaybmp(16,16,11,45,bmp_x2);
//						LCD_Displaybmp(48,16,13,45,bmp_as2);   //恢复卧室灯
//						LCD_Displaybmpf(16,16,11,61,bmp_x3);
//						LCD_Displaybmpf(32,16,13,61,bmp_as3);   //选定空调项	
//			}
//			if (uiitemnumber == 3)						  
//			{
//						LCD_Displaybmp(16,16,11,61,bmp_x3);
//						LCD_Displaybmp(32,16,13,61,bmp_as3);   //恢复空调项
//						LCD_Displaybmpf(16,16,11,77,bmp_x4);
//						LCD_Displaybmpf(48,16,13,77,bmp_as4);	//选定热水器项
//			}
//			if (uiitemnumber == 4)						  
//			{
//						LCD_Displaybmp(16,16,11,77,bmp_x4);
//						LCD_Displaybmp(48,16,13,77,bmp_as4);	//恢复热水器项
//						LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//选定返回项
//			}
//			break;
//		case 4:			//关机选择页面
//			if (uiitemnumber == 0)						
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);//恢复返回按钮
//					LCD_Displaybmpf(16,16,11,34,bmp_x1);
//					LCD_Displaybmpf(32,16,13,34,bmp_m4);	  //显示关机	
//				}
//			if (uiitemnumber == 1)					   
//				{
//					LCD_Displaybmp(16,16,11,34,bmp_x1);
//					LCD_Displaybmp(32,16,13,34,bmp_m4);	  //恢复关机
//					LCD_Displaybmpf(16,16,11,50,bmp_x2);
//					LCD_Displaybmpf(32,16,13,50,bmp_p2);	//显示重启	
//				}
//			if (uiitemnumber == 2)					   
//				{
//					LCD_Displaybmp(16,16,11,50,bmp_x2);
//					LCD_Displaybmp(32,16,13,50,bmp_p2);	//恢复重启
//					LCD_Displaybmpf(16,16,11,66,bmp_x3);
//					LCD_Displaybmpf(32,16,13,66,bmp_p3);	  //显示待机	
//				}
//			if (uiitemnumber == 3)					   
//				{
//					LCD_Displaybmp(16,16,11,66,bmp_x3);
//					LCD_Displaybmp(32,16,13,66,bmp_p3);	  //恢复待机
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	  //显示返回选项
//				}
//	   	break;
//		case 6:	 //门灯页面菜单
//			if (uiitemnumber == 0)	//门灯开关
//			   {
//				   	LCD_Displaybmpf(38,21,22,120,bmp_fhjk);//恢复返回按钮
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1 )	//门灯页面定时小时位
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);	////使开关正常
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 2 )	//门灯页面定时分钟位
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 3 )	//门灯页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )				 //选定定时开关
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//				}
//			
//			if (uiitemnumber == 4)
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )			   //恢复定时开关
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);///选定返回按钮
//				}
//		break;
//		case 7:	   ///////卧室灯界面/////////////////////
//			if (uiitemnumber == 0)	//卧室灯开关
//			   {
//				   	LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //恢复返回按钮
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1 )	//卧室灯页面定时小时位
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 2 )	//卧室灯页面定时分钟位
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 3 )	//卧室灯页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//				}
//			if (uiitemnumber == 4)
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //返回按钮
//				}
//		break;
//	    case 8:	   ////空调界面//////////////
//			if (uiitemnumber == 0)	//空调开关
//			   {
//				   	LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //恢复返回按钮
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1)	//空调温度
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}                      
//					LCD_PutNumberOnDataf(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnDataf(15,52,LCDSetElecTemp%10);
//				}
//			if (uiitemnumber == 2 )	//空调页面定时小时位
//				{
//					LCD_PutNumberOnData(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnData(15,52,LCDSetElecTemp%10);
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 3 )	//空调页面定时位
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 4 )	//空调灯页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//				}
//			
//			if (uiitemnumber == 5)	//////////返回按钮/////////
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//						LCD_Displaybmpf(38,21,22,120,bmp_fhjk); ///选定返回按钮
//				}
//		break;
//		case 9:
//			if (uiitemnumber == 0)	//热水器开关
//			   {
//				   	LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //恢复返回按钮
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1)	//热水器温度
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//					LCD_PutNumberOnDataf(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnDataf(15,52,LCDSetElecTemp%10);
//				}
//			if (uiitemnumber == 2 )	//热水器页面定时小时位
//				{
//					LCD_PutNumberOnData(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnData(15,52,LCDSetElecTemp%10);////////使温度恢复
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 3 )	//热水器页面定时分钟位
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 4 )	//热水器页面定时开或关位
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqg);
//					}
//					else 
//						{
//						}
//				}
//			
//			if (uiitemnumber == 5)	//////////返回按钮/////////
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else 
//						{
//						}
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);///选定返回按钮
//				}
//		break;
//		default:
//		break;
//	}	
//}
////========================================================================
//// 函数: INT8U LCD_DisplayWarning(INT8U uiwarningtype)
//// 描述: 显示警告页面
//// 参数: uiwarningtype 警告的类型
//// 返回: success 函数执行成功
////========================================================================
// INT8U LCD_DisplayWarning(INT8U uiwarningtype)
// {
//	LCD_Clear();
//	switch (uiwarningtype)
//	{
//	case 1:		 //煤气泄漏警告
////		LCD_Displaybmp(72,60,11,20,bmp_jg);//显示警告图片
//	    LCD_Displaybmp(88,21,10,84,bmp_mq); 	//显示煤气泄漏警告文字
//		LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//显示返回主界面按钮
//		break;
//	case 2:	 //小偷进入警告
////		LCD_Displaybmp(68,60,11,20,bmp_jg);//显示警告图片
//		LCD_Displaybmp(88,21,10,84,bmp_xt);	//显示小偷进入
//		LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//显示返回主界面按钮
//		break;
//	default:
//		break;
//	}
//	return 	1;
//}
/******************************************************************************
*							
*                      END   FILE 
*                      
******************************************************************************/
