/**********************************************************************************************************
**							文件名：	NMRQ_task.h
**                          文件描述：  本文件为IEACS系统TASK模块相关文件
**                               		包含系统设计相关的全局变量定义
**                          作者：		程敏
**							创建时间： 	2013-8-2
**
********************************************************************************************************/



#include "..\Include\NMRQ_config.h"

/*
********************************************************************************************************
*                                         系统全局变量
*********************************************************************************************************
*/
//LCD_PAGE		*LCDPageTree;					/*	指向LCD界面树头部界面的指针	*/
INT8U			LCDCurrentPage;				/*	指向LCD当前界面的指针	*/
INT8U	   		 LCDCurrentFocus;				/*	LCD当前界面的当前焦点	*/
INT8U			 PCConnectState;				/*	PC当前连接状态	*/
TIME		  	 OSCurrentTime;					/*	系统时间	*/

//BOOLEAN			 OSIsKeyDown;					/*	记录系统中是否有按键按下	*/
//KEY_INFO	 	 *OSCurrentKeyInfo;				/*	记录当前检测到的按键信息	*/
OS_STATE_INFO	 *OSCurrentPcInfo;				/*	记录当前检测到的PC端信息	*/

//INT8U			 OSOneMin;						/*	记录1s	*/

BOOLEAN			 OSPowerSave;					/*	记录系统是否进入省电模式	*/

/*	以下7个全局变量 LCD进入设置页面时使用	*/
//TIME			*LCDSetTime;					/*	时间设置时使用的全局变量	*/
//
//INT8U			 LCDSetElecSW;					/*	电器设置时使用的电器开关变量	*/
//INT8U			 LCDSetElecTemp;				/*	电器设置时使用的电器温度变量	*/
//INT8U			 LCDSetElecTimingHour;			/*	电器设置时使用的电器定时变量	*/
//INT8U			 LCDSetElecTimingMin;			/*	电器设置时使用的电器定时变量	*/
//INT8U			 LCDSetElecTimingSW;			/*	电器设置时使用的电器定时变量	*/
//BOOLEAN			 LCDSetElecTimingEnable;		/*	电器设置时使用的电器定时变量	*/


/********************************************
*	数组名：OSStateInfo
*	功能说明：系统状态表，保存系统状态信息
*	使用说明：数组大小需要根据系统实际需要设定，系统状态表内容需要设定
********************************************/

OS_STATE_INFO	OSStateInfo[OS_STATE_INFO_SIZE];

/********************************************
*	数组名：TimingTbl
*	功能说明：保存系统电器定时时间
*			  与TimingSW联合构成系统定时任务表
*	使用说明：
********************************************/

TIME	TimingTbl[TIMING_TBL_SIZE];

/********************************************
*	数组名：TimingSW
*	功能说明：保存系统电器定时开关信息
*			  与TimingTbl联合构成系统定时任务表
*	使用说明：
********************************************/

INT8U	TimingSW[TIMING_TBL_SIZE];

/********************************************
*	数组名：PCBuffer
*	功能说明：保存上位机发送过来的指令信息，作
*			  为参数传给串口信息解析任务
*	使用说明：
********************************************/
INT8U   PCBuffer[13];
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
