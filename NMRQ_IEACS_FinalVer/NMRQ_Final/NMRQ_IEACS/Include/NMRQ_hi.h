/*******************************************************************
*					  �ļ�����		NMRQ_hi.h
*					  �ļ�˵�� ��	����HIģ��ĺ�����
*                                	���hiģ����Ҫʹ�õ���Ϣ��
*                     ���ߣ�		������ 
*					  �������ڣ�	2013-8-1
********************************************************************/
//HIģ����Ҫʹ�õ������ģ���ͷ�ļ�

#include "NMRQ_config.h"

//HIģ�����õ��ⲿ����
extern BOOLEAN KEY_IfClicked(void);
extern INT8U KEY_SendKeyValue_whichKey(void);
extern BOOLEAN KEY_SendKeyValue_LongOrShort(void);

extern INT8U EAC_SendFeedbackMsg(INT8U EAC_functionNumber);
extern INT8U EAC_SendFeedbackMsg2(INT8U EAC_functionNumber,INT8U EAC_temperature );

//HIģ�麯������
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
