/*************************************************************
*            					文件名：	NMRQ_key.h
*           					描述：		KEY.c 的头文件，存储KEY.c要用到的宏定义
*           					作者：		杨林龙
*           					创建日期：	2013-7-26
**************************************************************/

 #include "..\Include\NMRQ_config.h"

//KEY模块函数声明
void KEY_DelayNS(INT16U nDly);
void KEY_Beep(INT16U count);
BOOLEAN KEY_IfClicked(void);
INT8U KEY_SendKeyValue_whickKey(void);
BOOLEAN KEY_SendKeyValue_LongOrShort(void);

 /***********************************************************************************
 *
 *								END OF FILE
 *
 *************************************************************************************/

