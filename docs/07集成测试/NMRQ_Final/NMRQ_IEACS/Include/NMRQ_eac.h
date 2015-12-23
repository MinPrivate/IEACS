/******************************************************************************************
*         �ļ�����NMRQ_eac.h
*         ������NMRQ_eac.c��ͷ�ļ�
*         �洢һЩ�궨������Ͷ���
*         ���ߣ�������
*         �������ڣ�2013-7-25
*         �޸�����1:2013-7-26 �޸�����:�޸��˲��ֺ궨��
*         �޸�����2:2013-7-29 �޸����ݣ�ɾ���˸��¸й�Ĵ������ͺ궨��      
**********************************************************************************************/


#include "..\Include\NMRQ_config.h"

extern	LCD_PAGE		*LCDCurrentPage;				/*	ָ��LCD��ǰ�����ָ��	*/
extern	INT8U	   		 LCDCurrentFocus;				/*	LCD��ǰ����ĵ�ǰ����	*/
extern	INT8U			 PCConnectState;				/*	PC��ǰ����״̬	*/
extern	TIME		  	 OSCurrentTime;					/*	ϵͳʱ��	*/

extern	KEY_INFO	 	 *OSCurrentKeyInfo;				/*	��¼��ǰ��⵽�İ�����Ϣ	*/
extern	OS_STATE_INFO	 *OSCurrentPcInfo;				/*	��¼��ǰ��⵽��PC����Ϣ	*/

/********************************************
*	��������OSStateInfo
*	����˵����ϵͳ״̬������ϵͳ״̬��Ϣ
*	ʹ��˵���������С��Ҫ����ϵͳʵ����Ҫ�趨��ϵͳ״̬��������Ҫ�趨
********************************************/

extern	OS_STATE_INFO	OSStateInfo[OS_STATE_INFO_SIZE];


/********************************************
*	��������TimingTbl
*	����˵��������ϵͳ������ʱʱ��
*			  ��TimingSW���Ϲ���ϵͳ��ʱ�����
*	ʹ��˵����
********************************************/

extern	TIME	TimingTbl[4];

/********************************************
*	��������TimingSW
*	����˵��������ϵͳ������ʱ������Ϣ
*			  ��TimingTbl���Ϲ���ϵͳ��ʱ�����
*	ʹ��˵����
********************************************/

extern	INT8U	TimingSW[4];



//��ǰADת�������ڸ��»��Ǹ���״̬
#define EAC_AD_STATE_TEMP		   0     //����״̬
#define EAC_AD_STATE_LIGHT			1	 //�й�״̬	

//EACģ�麯������
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


