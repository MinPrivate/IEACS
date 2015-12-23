/******************************************************************************************
*         文件名：NMRQ_eac.h
*         描述：NMRQ_eac.c的头文件
*         存储一些宏定义和类型定义
*         作者：杨林龙
*         创建日期：2013-7-25
*         修改日期1:2013-7-26 修改内容:修改了部分宏定义
*         修改日期2:2013-7-29 修改内容：删除了感温感光的错误类型宏定义      
**********************************************************************************************/


#include "..\Include\NMRQ_config.h"

extern	LCD_PAGE		*LCDCurrentPage;				/*	指向LCD当前界面的指针	*/
extern	INT8U	   		 LCDCurrentFocus;				/*	LCD当前界面的当前焦点	*/
extern	INT8U			 PCConnectState;				/*	PC当前连接状态	*/
extern	TIME		  	 OSCurrentTime;					/*	系统时间	*/

extern	KEY_INFO	 	 *OSCurrentKeyInfo;				/*	记录当前检测到的按键信息	*/
extern	OS_STATE_INFO	 *OSCurrentPcInfo;				/*	记录当前检测到的PC端信息	*/

/********************************************
*	数组名：OSStateInfo
*	功能说明：系统状态表，保存系统状态信息
*	使用说明：数组大小需要根据系统实际需要设定，系统状态表内容需要设定
********************************************/

extern	OS_STATE_INFO	OSStateInfo[OS_STATE_INFO_SIZE];


/********************************************
*	数组名：TimingTbl
*	功能说明：保存系统电器定时时间
*			  与TimingSW联合构成系统定时任务表
*	使用说明：
********************************************/

extern	TIME	TimingTbl[4];

/********************************************
*	数组名：TimingSW
*	功能说明：保存系统电器定时开关信息
*			  与TimingTbl联合构成系统定时任务表
*	使用说明：
********************************************/

extern	INT8U	TimingSW[4];



//当前AD转换器处于感温还是感温状态
#define EAC_AD_STATE_TEMP		   0     //感温状态
#define EAC_AD_STATE_LIGHT			1	 //感光状态	

//EAC模块函数声明
INT8U EAC_OpenDoorLight(void);
INT8U EAC_CloseDoorLight(void);
INT8U EAC_OpenAirCondition(void);
INT8U EAC_CloseAirCondition(void);
INT8U EAC_SetAirCond_Temp(INT8U aTemp);
INT8U EAC_OpenWaterheater(void);
INT8U EAC_CloseWaterheater(void);
INT8U EAC_SetWaterheater_Temp(INT8U wTemp);
void EAC_DelayNS(INT16U nDly);
void EAC_Bell(INT16U count);
void EAC_Beep(INT16U count);
void EAC_GetTemperatureInfo(void);
void EAC_GetLightInfo(void);
INT8U EAC_SwapTempAndLight(void);
INT8U EAC_ThiefFound(void);
INT8U EAC_GasLeak(void);
INT8U EAC_GetFeedbackMsg(INT8U EAC_functionNumber);
INT8U EAC_GetFeedbackMsg2(INT8U EAC_functionNumber,INT8U EAC_temperature);
INT8U EAC_SendFeedbackMsg(INT8U EAC_functionNumber);
INT8U EAC_SendFeedbackMsg2(INT8U EAC_functionNumber,INT8U EAC_temperature );


/***********************************************************************************
 *
 *								END OF FILE
 *
 *************************************************************************************/


