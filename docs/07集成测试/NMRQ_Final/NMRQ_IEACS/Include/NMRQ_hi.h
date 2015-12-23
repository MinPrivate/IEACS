/*******************************************************************
*					  文件名：		NMRQ_hi.h
*					  文件说明 ：	声明HI模块的函数，
*                                	存放hi模块需要使用的信息等
*                     作者：		杨林龙 
*					  创建日期：	2013-8-1
********************************************************************/
//HI模块需要使用到的相关模块的头文件

#include "NMRQ_config.h"

//HI模块会调用的外部函数
extern BOOLEAN KEY_IfClicked(void);
extern INT8U KEY_SendKeyValue_whichKey(void);
extern BOOLEAN KEY_SendKeyValue_LongOrShort(void);

extern INT8U EAC_SendFeedbackMsg(INT8U EAC_functionNumber);
extern INT8U EAC_SendFeedbackMsg2(INT8U EAC_functionNumber,INT8U EAC_temperature );

//HI模块函数声明
INT8U HI_Control(INT8U info_Type,INT8U ctrl_Obj,INT8U content);
INT8U HI_SwapTempAndLight(void);

void HI_PageSwitch(INT8U PageID,INT8U focus);
void HI_ErrorDisplay(INT8U errorType);

BOOLEAN HI_IfKeyClicked(void);
INT8U HI_GetKeyValue_whichKey(void);
BOOLEAN HI_GetKeyValue_LongOrShort(void);


 /***********************************************************************************
 *
 *								END OF FILE
 *
 *************************************************************************************/
