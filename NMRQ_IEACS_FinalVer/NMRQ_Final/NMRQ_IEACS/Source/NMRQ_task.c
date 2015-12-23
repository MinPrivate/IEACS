/******************************************************************************
*						�ļ�����	NMRQ_task.c	
*                       �ļ�������	���ļ�ΪTASKģ�����ݳ�ʼ���������߼���������ϵͳ���ܵı�д  
*                       ���ߣ�		����
*						����ʱ�䣺 	2013-8-1
******************************************************************************/

#include "..\Include\config.h"
#include "..\Include\NMRQ_task_glb.h"
#include "..\Include\NMRQ_task.h"




/*һЩ��Ҫʹ�õ����ⲿ����������*/
extern INT8U HI_Control(INT8U info_Type,INT8U ctrl_Obj,INT8U content);
extern INT8U HI_SwapTempAndLight(void);
extern void HI_PageSwitch(INT8U PageID,INT8U focus);
extern void HI_ErrorDisplay(INT8U errorType);
extern BOOLEAN HI_IfKeyClicked(void);
extern INT8U HI_GetKeyValue_whichKey(void);
extern BOOLEAN HI_GetKeyValue_LongOrShort(void);
extern INT8U COM_RecvDataDown(void);
extern void COM_SendDataDown(INT8U const *str);
extern void COM_InitDown(void);
extern void COM_SendByteDown(INT8U data);
extern INT8U HI_Control(INT8U info_Type,INT8U ctrl_Obj,INT8U content);
extern void InitialiseUART0(INT32U bps);


extern INT8U LCD_DisplayMainScreen(void);
extern INT8U LCD_UpdateConnect(INT8U uiConnectdata);
extern INT8U LCD_UpdateTime(INT8U uihourfirst,INT8U uihoursecond,INT8U uiminutefirst,INT8U uiminutesecond);
extern INT8U LCD_UpdateWeek(INT8U uiweek);
extern INT8U LCD_UpdateDate(INT8U uiyearfirst,INT8U uiyearsecond,INT8U uiyearthird,INT8U uiyearforth,INT8U uimonthfirst,INT8U uimonthsecond,INT8U uidayfirst,INT8U uidaysecond);
extern INT8U LCD_UpdateCircumstance(INT8U uitemfirst,INT8U uitemsecond,INT8U uihumfirst,INT8U uihumsecond);
extern INT8U LCD_DisplayMenuSet(void);
extern INT8U LCD_UpdateApplianceState (INT8U uidoorl_state,INT8U uibedl_state,INT8U uiair_state,INT8U uiwaterh_state);
extern INT8U LCD_SelectMenuSetItem(INT8U uimenupagenumber,INT8U uiitemnumber);
extern INT8U LCD_DisplayModeSelect(void);

/*�����ջ����*/
OS_STK        TASK_KeyDecStk[TASK_STK_SIZE];
OS_STK        TASK_PcDecStk[TASK_STK_SIZE];
OS_STK        TASK_EventHdlStk[TASK_STK_SIZE];
OS_STK        TASK_PCParseStk[TASK_STK_SIZE];									


/******************************************************************************
*						����������	TASK_Start	
*                       ����˵����  1��  pdata		//�������		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鿪������
*									��IEACSϵͳ���г�ʼ��
*									����ʱ�ӽ����жϲ���������
******************************************************************************/
void  TASK_Start(void *pdata)
{
	pdata = pdata;

	TASK_Init();
	T0TCR = 1;	/*����ʱ�ӽ����ж�*/

	TASK_DisplayMain ();                           	
	OSTaskCreate(TASK_KeyDec, (void *)0, &TASK_KeyDecStk[TASK_STK_SIZE - 1], TASK_PRIO_KEYDEC);
    OSTaskCreate(TASK_PcDec, (void *)0, &TASK_PcDecStk[TASK_STK_SIZE - 1], TASK_PRIO_PCDEC);
    OSTaskCreate(TASK_PC_Parse, (void *)0, &TASK_PCParseStk[TASK_STK_SIZE - 1], TASK_PRIO_PC_PARSE);
	//OSTaskCreate(TASK_Timing, (void *)0, &TASK_TimingStk[TASK_STK_SIZE - 1], TASK_PRIO_TIMING);
                        
    for (;;)																	
    {
		/*	ϵͳ���Ĳ���	*/
//		if(LCDCurrentPage == LCD_PAGE_MAIN)
//		{
//		 	//TASK_DisplayMain ();
//			LCD_UpdateTime(TASK_GetRTCTimeHour()/10,TASK_GetRTCTimeHour()%10,
//							TASK_GetRTCTimeMin()/10,TASK_GetRTCTimeMin()%10);
//			LCD_UpdateWeek(TASK_GetRTCTimeWeek());
//			LCD_UpdateDate(TASK_GetRTCTimeYear()/1000,
//							((TASK_GetRTCTimeYear())/100)%10,
//							((TASK_GetRTCTimeYear())/10)%10,
//							(TASK_GetRTCTimeYear())%10,
//							(TASK_GetRTCTimeMonth())/10,
//							(TASK_GetRTCTimeMonth())%10,
//							(TASK_GetRTCTimeDay())/10,
//							(TASK_GetRTCTimeDay())%10);
//		}
		//COM_SendData Down("StartTask starts to run\n");
        //OSTimeDlyHMSM(0,0,0,2);
		OSTimeDly(5);	
    }
}


/******************************************************************************
*						����������	TASK_KeyDec	
*                       ����˵����  1��  pdata		//�������		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鰴��������񣬼����̰�����Ϣ��
*									����⵽���̰�����Ϣ����TASK_Parse����
*									���Ѱ�����Ϣ���ݸ�TASK_Parse������Ϣ������
******************************************************************************/
void  TASK_KeyDec(void *pdata)
{
	INT8U	uiTimeNoKey = 0;			/*	��¼��15sû�а�������ʱ��λOSPowerSave	*/
	INT8U uiIsKeyDown;
	INT8U uiTempKeyType;
	INT8U uiTempKeyValue;	

	pdata = pdata;
	
	//T0TCR = 1;	/*����ʱ�ӽ����ж�*/
     //TASK_Init();  
	 BeepCount(1);                       	
	                      
    for (;;)																	
    {	/*	�ж��Ƿ��а�������	*/
		uiIsKeyDown = HI_IfKeyClicked();

		if(uiIsKeyDown != KEY_UNCLICKED)  					/*	��⵽�а�������	*/
		{													/*	�õ���ֵ����������	*/
		  	 uiTempKeyType = HI_GetKeyValue_LongOrShort();
		  	 uiTempKeyValue = HI_GetKeyValue_whichKey();
		   	
		   	BeepCount(1);
			TASK_KeyParse(uiTempKeyType,uiTempKeyValue);

															

		   
		   uiTimeNoKey = 0;									/*	�а�������uiTimeNoKey����	*/
		   
		}

		if(uiTimeNoKey >= OS_ENTER_POWERSAVING)
		{
			 OSPowerSave = TRUE;
		}


		uiTimeNoKey += 2;
        //OSTimeDlyHMSM(0,0,0,2);
		OSTimeDly(20);	
    }
}


/******************************************************************************
*						����������	TASK_PcDec	
*                       ����˵����  1��  pdata		//�������		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鴮�ڼ������
*									���PC��ͨ����������λ�����ݵ���Ϣ��
*									����⵽��PC��ͨ����������λ�����ݵ���Ϣ
*									����TASK_Parse���񲢰���Ϣ���ݸ�TASK_Parse
*									������Ϣ������
******************************************************************************/
void  TASK_PcDec(void *pdata)
{
	
	int i;
	pdata = pdata; 		                              //��ֹ���뾯��

	InitialiseUART0(9600);	                          //��ʼ������ 

    for (;;)																	
    {
		OS_ENTER_CRITICAL();						  //���ж�
		//COM_SendDataDown("d000000000000"); 
		if((U0LSR & 0x01)==0x01)
		{
			for(i=0;i<=13;)
			{
										  //����������ִ��
				PCBuffer[i]=U0RBR;
				i++;
					//DelayNS(10);
			}
			//for(i=0;i<13;i++) COM_SendByteDown(PCBuffer[i]);

			OSTaskResume(TASK_PRIO_PC_PARSE);
		}
		
		OS_EXIT_CRITICAL();							  //���ж�

		OSTimeDly(20);	
    }
}


/******************************************************************************
*						����������	TASK_KeyParse	
*                       ����˵����  1��  pdata		//�������		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ����Ϣ��������
*									����TASK_KeyDec��TASK_PcDec��⵽����Ϣ��
*									ͨ����Ϣ������õ���Ϣ������Ĳ�����
*									����TASK_EventHdl������в�������
******************************************************************************/
void  TASK_KeyParse(INT8U uiTempKeyType,INT8U uiTempKeyValue)
{
	INT8U uiTempOpeState; 									/*	��¼����ִ�����	*/
	INT8U uiTempIns[14];
	INT8U i;
//	pdata = pdata;
	                            	
	/*	����������ɣ����OSIsKeyDown��Ϣ	*/
	if(LCDCurrentPage == LCD_PAGE_MAIN) 	
	{	/*	��ǰ����Ϊ������	*/
	 	if(uiTempKeyType == KEY_LONGCLICKED)			
		{	/*	��ǰ��������Ϊ����	*/
		 	switch(uiTempKeyValue)
			{
				case KEY_SWI2:				/*	����KEY_SWI2�Ĳ��� ģ��AD	*/
								HI_SwapTempAndLight();
								/*	ˢ�¿���״̬	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[0].uiOSStateContent) COM_SendDataDown("d100000000000");
								else COM_SendDataDown("d000000000000");
								if(OSStateInfo[2].uiOSStateContent) COM_SendDataDown("h100000000000");
								else COM_SendDataDown("h000000000000");
								/*	ˢ���¶ȹ�ǿ״̬	*/
								LCD_UpdateCircumstance(OSStateInfo[7].uiOSStateContent/10,OSStateInfo[7].uiOSStateContent%10,
														OSStateInfo[8].uiOSStateContent/10,OSStateInfo[8].uiOSStateContent%10);
								uiTempIns[0]='p';
								uiTempIns[1]=TASK_CharToNum(OSStateInfo[7].uiOSStateContent/10);
								uiTempIns[2]=TASK_CharToNum(OSStateInfo[7].uiOSStateContent%10);
								for(i=3;i<13;i++) uiTempIns[i]='0';
								uiTempIns[13]='\0';
								COM_SendDataDown(uiTempIns);
								uiTempIns[0]='q';
								uiTempIns[1]=TASK_CharToNum(OSStateInfo[8].uiOSStateContent/10);
								uiTempIns[2]=TASK_CharToNum(OSStateInfo[8].uiOSStateContent%10);
								for(i=3;i<13;i++) uiTempIns[i]='0';
								uiTempIns[13]='\0';
								COM_SendDataDown(uiTempIns);
								break;
				case KEY_SWI1:				/*	����KEY_SWI3�Ĳ��� ��������ѡ�����	*/
								LCDCurrentPage = LCD_PAGE_SELECT_SETING;
								LCDCurrentFocus = 0;
								/*	LCD��ʾˢ��	*/
								TASK_DisplaySelectSet ();
								LCD_SelectMenuSetItem(LCDCurrentPage,LCDCurrentFocus);
								break;
				case KEY_SWI3:				/*	����KEY_SWI4�Ĳ��� ģ��С͵�ж�	*/
								COM_SendDataDown("r000000000000");
								HI_Control(OS_STATE_INFO_TYPE_INT,OS_STATE_CTRL_OBJ_THIEF,1);
								
								//LCD��ʾˢ��/////////////////////////////////////////////////////////////////////
								break;
				case KEY_SWI4:				/*	����KEY_SWI4�Ĳ��� ģ��ú���ж�	*/
								COM_SendDataDown("s000000000000");
								HI_Control(OS_STATE_INFO_TYPE_INT,OS_STATE_CTRL_OBJ_GASLEAK,1);
								/*	LCD��ʾˢ��	*/
								
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								
								break;
				default:		break;
			}
		}
		if(uiTempKeyType == KEY_SHORTCLICKED)			
		{	/*	��ǰ��������Ϊ�̰�	*/
		 	switch(uiTempKeyValue)
			{
			 	case KEY_SWI1:			/*	�̰�KEY_SWI1�Ĳ��� ���ŵƽ��п��ز���	*/
								/*	�ŵƵĿ��ز���	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_DOOR_LIGHT,!(OSStateInfo[0].uiOSStateContent));
								/*	��������ɹ� LCD��ʾˢ��
									PC��ʾˢ�£�������ӣ�	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[0].uiOSStateContent) COM_SendDataDown("d100000000000");
								else COM_SendDataDown("d000000000000");
								break;
				case KEY_SWI2:			/*	�̰�KEY_SWI2�Ĳ��� �����ҵƽ��п��ز���	*/
								/*	���ҵƵĿ��ز���	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,!(OSStateInfo[1].uiOSStateContent));
								/*	��������ɹ�LCD��ʾˢ��
									PC��ʾˢ�£�������ӣ�	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[1].uiOSStateContent) COM_SendDataDown("f100000000000");
								else COM_SendDataDown("f000000000000");
								break;
				case KEY_SWI3:			/*	�̰�KEY_SWI3�Ĳ��� �Կյ����п��ز���	*/
								/*	�յ��Ŀ��ز���	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_AIRCONDITION,!(OSStateInfo[2].uiOSStateContent));
								/*	��������ɹ�LCD��ʾˢ��
									PC��ʾˢ�£�������ӣ�	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[2].uiOSStateContent) COM_SendDataDown("h100000000000");
								else COM_SendDataDown("h000000000000");
								break;
				case KEY_SWI4:			/*	�̰�KEY_SWI4�Ĳ��� ����ˮ�����п��ز���	*/
								/*	��ˮ���Ŀ��ز���	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_CALORIFIER,!(OSStateInfo[3].uiOSStateContent));
								/*	��������ɹ�LCD��ʾˢ��
									PC��ʾˢ�£�������ӣ�	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[3].uiOSStateContent) COM_SendDataDown("k100000000000");
								else COM_SendDataDown("k000000000000");
								break;
				default:		break;
			}
		}
	}
	else if(LCDCurrentPage == LCD_PAGE_SELECT_SETING)
	{	/*	��ǰLCD����Ϊ��������	*/
		if(uiTempKeyType == KEY_SHORTCLICKED)			
				{	/*	��ǰ��������Ϊ�̰�	*/
					switch(uiTempKeyValue)
					{
					 	case KEY_SWI2:	/*	�̰�KEY_SWI2�Ĳ��� ȷ�ϲ��� ���н����л�	*/
										if(LCDCurrentFocus < 5)
										{/*	������һ������	*/
											switch(LCDCurrentFocus)
											{
												case 0:
														LCDCurrentPage = LCD_PAGE_SELECT_MODEL;
												        LCDCurrentFocus = 0;
														LCD_DisplayModeSelect();
														break;
												case 1:
														LCDCurrentPage = LCD_PAGE_SETING_TIME;
												        LCDCurrentFocus = 0;

//														LCDSetTime->uiTimeYear	 = TASK_GetRTCTimeYear();
//														LCDSetTime->uiTimeMonth	 = TASK_GetRTCTimeMonth();
//														LCDSetTime->uiTimeDay	 = TASK_GetRTCTimeDay();
//		
//														LCDSetTime->uiTimeHour 	 = TASK_GetRTCTimeHour();
//														LCDSetTime->uiTimeMinute = TASK_GetRTCTimeMin();
														//LCDSetTime->uiTimeSecond = TASK_GetRTCTimeSec();
														break;
												case 2:
														LCDCurrentPage = LCD_PAGE_SELECT_ELEC;
												        LCDCurrentFocus = 0;
														break;
												case 3:
														LCDCurrentPage = LCD_PAGE_SELECT_SYS;
												        LCDCurrentFocus = 0;
														break;
												case 4:
														LCDCurrentPage = LCD_PAGE_MAIN;
												        LCDCurrentFocus = 0;
														/*	����������	*/
														TASK_DisplayMain ();
														TASK_DisplayMain ();
														break;
												default:break;
											}
										}									
										break;
						case KEY_SWI4:	/*	�̰�KEY_SWI4�Ĳ��� �����л�������	*/
										LCDCurrentFocus = (LCDCurrentFocus + 1) % 5;
										/*	����ˢ�»��л�	ҳ�治�л��������л�	*/
										LCD_SelectMenuSetItem(LCDCurrentPage,LCDCurrentFocus);
										break;
						//case KEY_SWI1:	/*	�̰�KEY_SWI1�Ĳ��� �� 1 ����	*/
						//				break;
						//case KEY_SWI3:	/*	�̰�KEY_SWI3�Ĳ��� �� 1 ����	*/
						//				break;
						default:		break;
					}
				}
	}
//	else if(LCDCurrentPage == LCD_PAGE_SELECT_MODEL)
//	{	/*	��ǰLCD����Ϊ��������	*/
//		if(uiTempKeyType == KEY_SHORTCLICKED)			
//				{	/*	��ǰ��������Ϊ�̰�	*/
//					switch(uiTempKeyValue)
//					{
//					 	case KEY_SWI2:	/*	�̰�KEY_SWI2�Ĳ��� ȷ�ϲ��� ���н����л�	*/
//										if(LCDCurrentFocus < 5)
//										{/*	������һ������	*/
//											switch(LCDCurrentFocus)
//											{
//												case 0:
//														break;
//												case 1:
//														break;
//												case 2:
//														break;
//												case 3:
//														break;
//												case 4:
//														LCDCurrentPage = LCD_PAGE_SELECT_SETING;
//												        LCDCurrentFocus = 0;
//														/*	����������	*/
//														LCD_DisplayMenuSet ();
//														break;
//												default:break;
//											}
//										}									
//										break;
//						case KEY_SWI4:	/*	�̰�KEY_SWI4�Ĳ��� �����л�������	*/
//										LCDCurrentFocus = (LCDCurrentFocus + 1) % 5;
//										/*	����ˢ�»��л�	ҳ�治�л��������л�	*/
//										LCD_SelectMedelSelectItem(LCDCurrentPage,LCDCurrentFocus);
//										break;
//						//case KEY_SWI1:	/*	�̰�KEY_SWI1�Ĳ��� �� 1 ����	*/
//						//				break;
//						//case KEY_SWI3:	/*	�̰�KEY_SWI3�Ĳ��� �� 1 ����	*/
//						//				break;
//						default:		break;
//					}
//				}
//	}
	else{;}  	

}



/******************************************************************************
*						����������	TASK_Timing	
*                       ����˵����  1��  pdata		//�������		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鶨ʱ������������
*									����ϵͳ�е�����ʱ����������ʱ����ʱ��ʱ��
*									����TASK_EventHdl���������Ӧ�Ķ�ʱ������
******************************************************************************/
//void  TASK_Timing(void *pdata)
//{
//	INT8U 	uiTempCount;						/*	��ʱ���������±�	*/
//	INT8U	uiTempTimingSW;						/*	��Ӧ�Ķ�ʱ���ز���	*/
//
//	INT8U 	uiTempOpeState;
//												/*	��¼����ִ�����	*/
//	pdata = pdata;
//	                            		                        
//    for (;;)																	
//    {
//		while (0 == (ILR & 0x01));				/* �ȴ�RTC�����ж�	*/
//		ILR = 0x01;								/* ����жϱ�־	*/
//		
//		/*	������ʱ���������ж�ʱ���񵽾�����Ӧ�Ĳ���	*/
//		for(uiTempCount = 0; uiTempCount < TIMING_TBL_SIZE; uiTempCount++)
//		{
//		 	if(TASK_GetRTCTimeHour() == TimingTbl[uiTempCount].uiTimeHour	&&
//				TASK_GetRTCTimeMin() == TimingTbl[uiTempCount].uiTimeMinute	)
//				{
//				 	/*	��⵽�˶�ʱʱ���뵱ǰʱ���Ǻϣ���ն�ʱ���������Ӧ�Ŀ��ز���	*/
//					TimingTbl[uiTempCount].uiTimeHour 	= 0;
//					TimingTbl[uiTempCount].uiTimeMinute = 0;
//					/*	�õ���ǰ��ʱ�����Ƕ�ʱ�����Ƕ�ʱ��	*/
//					uiTempTimingSW = TimingSW[uiTempCount];
//
//					/*	��ʱ�������	*/
//					switch(uiTempCount)
//					{	/*	�ŵƶ�ʱ����	*/
//						case 0:
//								//�ŵƵĿ��ز���/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_DOOR_LIGHT,uiTempTimingSW);
//								//��������ɹ� LCD��ʾˢ��/////////////////////////////////////////////////////////////////////
//								//PC��ʾˢ�£�������ӣ�/////////////////////////////////////////////////////////////////////
//								
//								break;
//						/*	���ҵƶ�ʱ����	*/
//						case 1:
//								//���ҵƵĿ��ز���/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,uiTempTimingSW);
//								//��������ɹ�LCD��ʾˢ��/////////////////////////////////////////////////////////////////////
//								//PC��ʾˢ�£�������ӣ�/////////////////////////////////////////////////////////////////////
//
//								break;
//						/*	�յ���ʱ����	*/
//						case 2:
//								//�յ��Ŀ��ز���/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_AIRCONDITION,uiTempTimingSW);
//								//��������ɹ�LCD��ʾˢ��/////////////////////////////////////////////////////////////////////
//								//PC��ʾˢ�£�������ӣ�/////////////////////////////////////////////////////////////////////
//
//								break;
//						/*	��ˮ����ʱ����	*/
//						case 3:
//								//��ˮ���Ŀ��ز���/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_CALORIFIER,uiTempTimingSW);
//								//��������ɹ�LCD��ʾˢ��/////////////////////////////////////////////////////////////////////
//								//PC��ʾˢ�£�������ӣ�/////////////////////////////////////////////////////////////////////
//
//								break;
//						default:break;
//					}
//				}
//		}
//		
//        //OSTimeDlyHMSM(0,0,0,2);
//		OSTimeDly(2);	
//    }
//}





/******************************************************************************
*						����������	TASK_PC_Parse	
*                       ����˵����  1��  pdata		//�������		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鴮��ͨ�Ų�����������
*									�����ڷ��͹�������Ϣ��������Ϣ
*									���ò�ͬ��ģ��ӿڽ����¼�����
******************************************************************************/
void  TASK_PC_Parse(void *pdata)
{
	pdata = pdata;
	InitialiseUART0(9600);	
	for(;;)
	{
		OS_ENTER_CRITICAL();
		//COM_SendDataDown("PC_Parse starts to run\n");
		switch(PCBuffer[0])
		{
			case 'a':               //�������󣬷���һ��b000000000000��ʾ���ӳɹ�
				//COM_SendDataDown("I've received a link request\n");
				COM_SendDataDown("b000000000000");
				PCConnectState=TRUE;
				if(LCDCurrentPage==LCD_PAGE_MAIN)
				{
					TASK_DisplayMain();
				}
				break;	
			case 'c':               //״̬����
				//COM_SendDataDown("I've received a state request\n");
				//��״̬���͸���λ��
				TASK_SendStatTbl();
				//����ʱ���͸���λ��
				TASK_SendTimingTbl();
				
				break;    			 
			case 'd':				//�ŵƿ��أ�������ַ�Ϊ0�أ�1��
				if(PCBuffer[1]=='0') 
				{
					//COM_SendDataDown("Turn off the door light\n");
					//����HIģ����ŵ�
					HI_Control(OS_STATE_CTRL_OBJ_DOOR_LIGHT,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_OFF);

				}
				else if(PCBuffer[1]=='1') 
				{
					//COM_SendDataDown("Turn on the door light\n");
					//����HIģ�鿪�ŵ�
					HI_Control(OS_STATE_CTRL_OBJ_DOOR_LIGHT,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_ON);
				}
				LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);					
				break;	 
			case 'e':				//�ŵƶ�ʱ
				//COM_SendDataDown("Turn off the door light at:\n");
				//����ʱ������ӵ���ʱ�����
				TimingTbl[0].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[0].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[0]					= TASK_CharToNum(PCBuffer[5]);
				break;	
			case 'f':				//���ҵƿ���
				if(PCBuffer[1]=='0') 
				{
					//COM_SendDataDown("Turn off the room light\n");
					//����HIģ������ҵ�
					HI_Control(OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_OFF);

				}
				else if(PCBuffer[1]=='1') 
				{
					//COM_SendDataDown("Turn on the room light\n");
					//����HIģ�鿪���ҵ�
					HI_Control(OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_ON);
				}
					LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);

				break;    
			case 'g':								//���ҵƶ�ʱ   �������ֽ�����
				/*����ʱ������ӵ���ʱ�����*/
				TimingTbl[1].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[1].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[1]					= TASK_CharToNum(PCBuffer[5]);
				break;	 
			case 'h':								//�յ�����	   ����һ�ֽ�����
				if(PCBuffer[1]=='0')       //�ز���
				{
					//COM_SendDataDown("Turn off the Air Conditioner\n");
					//����HIģ��ؿյ�
					HI_Control(OS_STATE_CTRL_OBJ_AIRCONDITION,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_OFF);
				}
				else if(PCBuffer[1]=='1') 	 //������
				{
					//COM_SendDataDown("Turn on the Air Conditioner\n");
					//����HIģ�鿪�յ�
					HI_Control(OS_STATE_CTRL_OBJ_AIRCONDITION,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_ON);
				}
					LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);
				break;	
			case 'i':				//�յ��¶�	   �������ֽ�����
				HI_Control(OS_STATE_CTRL_OBJ_AIRCONDITION,
							OS_STATE_INFO_TYPE_TEMP ,
							TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]));
				break;	   
			case 'j':				//�յ���ʱ	   �������ֽ�����
				TimingTbl[2].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[2].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[2]					= TASK_CharToNum(PCBuffer[5]);
				break;	
			case 'k':				//��ˮ������   ����һ�ֽ�����
				if(PCBuffer[1]=='0')       //�ز���
				{
					//COM_SendDataDown("Turn off the Calorifier\n");
					//����HIģ�����ˮ��
					HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_OFF);
				}
				else if(PCBuffer[1]=='1') 	 //������
				{
					//COM_SendDataDown("Turn on the Calorifier\n");
					//����HIģ�鿪��ˮ��
					HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_ON);
				}
					LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);
				break;	
			case 'l':				//��ˮ���¶�   �������ֽ�����
				//����HIģ�����ÿյ��¶�
				HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
							OS_STATE_INFO_TYPE_TEMP ,
							TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]));
				break;	
			case 'm':				//��ˮ����ʱ   �������ֽ�����
				//�����յ��Ķ�ʱ����д�붨ʱ�����
				TimingTbl[3].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[3].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[3]					= TASK_CharToNum(PCBuffer[5]);
				break;
			case 'n':				//ϵͳ����ģʽ ����һ�ֽ�����
				//����HIģ��ı�ϵͳģʽ
				HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
							OS_STATE_INFO_TYPE_TEMP ,
							TASK_CharToNum(PCBuffer[1]));
				
				break;
			case 'o':			    //ϵͳʱ��	   ����ʮ���ֽ����� ��λ����������
				//��λ��������λ��������ʱ����е���
				/* �� */
				YEAR 	= (INT16U)(TASK_CharToNum(PCBuffer[1])*1000+
									TASK_CharToNum(PCBuffer[2])*100+
									TASK_CharToNum(PCBuffer[3])*10+
									TASK_CharToNum(PCBuffer[4]));
				/* �� */
				MONTH	= (INT8U)(TASK_CharToNum(PCBuffer[5])*10+
									TASK_CharToNum(PCBuffer[6]));
				/* �� */
				DOM		= (INT8U)(TASK_CharToNum(PCBuffer[7])*10+
									TASK_CharToNum(PCBuffer[8]));
				/* ʱ */
				HOUR	= (INT8U)(TASK_CharToNum(PCBuffer[9])*10+
									TASK_CharToNum(PCBuffer[10]));
				/* �� */
				MIN		= (INT8U)(TASK_CharToNum(PCBuffer[11])*10+
									TASK_CharToNum(PCBuffer[12]));

				if(LCDCurrentPage==LCD_PAGE_MAIN)
				{
					TASK_DisplayMain();
				}
				break;
			default: break;
		}
		PCBuffer[0]			= 0x00;	
		PCBuffer[1]			= 0x00;
		PCBuffer[2]			= 0x00;
		PCBuffer[3]			= 0x00;
		PCBuffer[4]			= 0x00;
		PCBuffer[5]			= 0x00;
		PCBuffer[6]			= 0x00;
		PCBuffer[7]			= 0x00;	
		PCBuffer[8]			= 0x00;
		PCBuffer[9]			= 0x00;
		PCBuffer[10]		= 0x00;	
		PCBuffer[11]		= 0x00;
		PCBuffer[12]		= 0x00;
		//PCBuffer[13]		= 0x00;
		OSTaskSuspend(TASK_PRIO_PC_PARSE);
		OS_EXIT_CRITICAL();
		OSTimeDly(2);
	}	
}

/******************************************************************************
*						����������	TASK_Init	
*                       ����˵����  ��		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ���ʼ��������
*									��ʼ��ϵͳȫ�ֱ�����
******************************************************************************/
void  TASK_Init(void)
{
/*	��ʼ��ʱ�رշ�����	*/
	PINSEL0=0x00000000;              			/* ����IO�ڹ���ģʽ	  */
   	PINSEL1=0x00000000;
   	IODIR |=BEEP;
   	IOCLR|=BEEP;                   			  	/*�رշ�����	*/

/*	��ʼ��ʵʱʱ��	*/
	TASK_RTCInit ();

/*	��ʼ��ϵͳ״̬��	*/
	TASK_OSStateInfoInit();

/*	��ʼ����ʱ�����	*/
	TASK_TimingTblInit();
/*	��ʼ��LCD������	*/
	//TASK_LcdPageTreeInit();

/*	������ȫ�ֱ�����ʼ��	*/
	LCDCurrentPage  = LCD_PAGE_MAIN;				/*	��ǰLCDҳ��ΪLCDҳ����ͷ���� ��ҳ��	*/
	LCDCurrentFocus = 0;						/*	LCD��ǰ����ĵ�ǰ����	*/

	PCConnectState  = 0;						/*	PC��ǰ����״̬	*/
	//OSCurrentTime.uiTimeYear	= 2013;			/*	ϵͳʱ��	*/
	//OSCurrentTime.uiTimeMonth	= 1;			/*	ϵͳʱ��	*/
	//OSCurrentTime.uiTimeDay		= 1;			/*	ϵͳʱ��	*/
	//OSCurrentTime.uiTimeHour	= 1;			/*	ϵͳʱ��	*/
	//OSCurrentTime.uiTimeMinute	= 1;			/*	ϵͳʱ��	*/
	//OSCurrentTime.uiTimeSecond	= 1;			/*	ϵͳʱ��	*/

//	OSIsKeyDown		  	= KEY_UNCLICKED;		/*	ϵͳ��ʼʱδ�а�������	*/
//	OSCurrentKeyInfo	= (struct key_info_t*)malloc(sizeof(struct key_info_t));			/*	��¼��ǰ��⵽�İ�����Ϣ	*/
	OSCurrentPcInfo		= (struct os_state_info_t*)malloc(sizeof(struct os_state_info_t));	/*	��¼��ǰ��⵽��PC����Ϣ	*/

//	OSOneMin			= 0;						/*	��¼1s	*/

	OSPowerSave			= FALSE;					/*	��¼ϵͳ�Ƿ����ʡ��ģʽ	*/

/*  PCBuffer��ʼ��  */
    PCBuffer[0]			= 0x00;	
	PCBuffer[1]			= 0x00;
	PCBuffer[2]			= 0x00;
	PCBuffer[3]			= 0x00;
	PCBuffer[4]			= 0x00;
	PCBuffer[5]			= 0x00;
	PCBuffer[6]			= 0x00;
	PCBuffer[7]			= 0x00;	
	PCBuffer[8]			= 0x00;
	PCBuffer[9]			= 0x00;
	PCBuffer[10]		= 0x00;	
	PCBuffer[11]		= 0x00;
	PCBuffer[12]		= 0x00;
	//PCBuffer[13]		= 0x00;
}


/******************************************************************************
*						����������	TASK_OSStateInfoInit	
*                       ����˵����  ��		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ��ϵͳ״̬���ʼ��������
*									
******************************************************************************/
void TASK_OSStateInfoInit (void)
{
	/*	ϵͳ״̬������ϵͳ״̬��Ϣ	*/
	OSStateInfo[0].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_DOOR_LIGHT;			/*	�ŵ�	*/
	OSStateInfo[0].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	����	*/
	OSStateInfo[0].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	��	*/

	OSStateInfo[1].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_BEDROOM_LIGHT;		/*	���ҵ�	*/
	OSStateInfo[1].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	����	*/
	OSStateInfo[1].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	��	*/

	OSStateInfo[2].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AIRCONDITION;		/*	�յ�	*/
	OSStateInfo[2].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	����	*/
	OSStateInfo[2].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	��	*/

	OSStateInfo[3].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_CALORIFIER;			/*	��ˮ��	*/
	OSStateInfo[3].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	����	*/
	OSStateInfo[3].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	��	*/

	OSStateInfo[4].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AIRCONDITION;		/*	�յ�	*/
	OSStateInfo[4].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_TEMP;  			/*	�¶�	*/
	OSStateInfo[4].uiOSStateContent 	= 26;									/*	��ʼ��Ϊ0	*/

	OSStateInfo[5].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_CALORIFIER;			/*	��ˮ��	*/
	OSStateInfo[5].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_TEMP;  			/*	�¶�	*/
	OSStateInfo[5].uiOSStateContent 	= 50;									/*	��ʼ��Ϊ0	*/

	OSStateInfo[6].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_SYS;				/*	ϵͳ	*/
	OSStateInfo[6].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_MODEL;  			/*	ģʽ	*/
	OSStateInfo[6].uiOSStateContent 	= OS_MODEL_STATE_COMMON;				/*	��ͨģʽ	*/

	OSStateInfo[7].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AD;					/*	AD	*/
	OSStateInfo[7].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SENTEMP;  			/*	����	*/
	OSStateInfo[7].uiOSStateContent 	= 30;									/*	��ʼ��Ϊ0	*/

	OSStateInfo[8].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AD;					/*	AD	*/
	OSStateInfo[8].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SENLIGHT;  		/*	�й�	*/
	OSStateInfo[8].uiOSStateContent 	= 45;									/*	��ʼ��Ϊ0	*/
}

/******************************************************************************
*						����������	TASK_TimingTblInit	
*                       ����˵����  ��		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鶨ʱ������ʼ��������
*									
******************************************************************************/
void TASK_TimingTblInit (void)
{
	INT8U 	uiTempCount;						/*	��ʱ���������±�	*/
	
	/*	��ʱ������У������±�Ϊ 0 ��ʾ��ʱ����Ϊ	�ŵ�
					  �����±�Ϊ 1 ��ʾ��ʱ����Ϊ	���ҵ�
					  �����±�Ϊ 2 ��ʾ��ʱ����Ϊ	�յ�
					  �����±�Ϊ 3 ��ʾ��ʱ����Ϊ	��ˮ��	*/
	for(uiTempCount = 0; uiTempCount < TIMING_TBL_SIZE; uiTempCount++)
	{
		TimingTbl[uiTempCount].uiTimeYear		= OSCurrentTime.uiTimeYear;			
		TimingTbl[uiTempCount].uiTimeMonth		= OSCurrentTime.uiTimeMonth;		
		TimingTbl[uiTempCount].uiTimeDay		= OSCurrentTime.uiTimeDay;		
		TimingTbl[uiTempCount].uiTimeHour		= 0;			
		TimingTbl[uiTempCount].uiTimeMinute		= 0;		
		TimingTbl[uiTempCount].uiTimeSecond		= 0;		
		TimingSW[uiTempCount]					= OS_ELEC_SWITCH_STATE_OFF;	  /*��ʼ��Ϊ��	*/

	}
}


/******************************************************************************
*						����������	TASK_DisplayMain	
*                       ����˵����  ��		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鶨ʱ������ʼ��������
*									
******************************************************************************/
void TASK_DisplayMain (void)
{
	LCD_DisplayMainScreen();
	LCD_UpdateConnect(PCConnectState);
	LCD_UpdateTime(TASK_GetRTCTimeHour()/10,TASK_GetRTCTimeHour()%10,
					TASK_GetRTCTimeMin()/10,TASK_GetRTCTimeMin()%10);
	LCD_UpdateWeek(TASK_GetRTCTimeWeek());
	LCD_UpdateDate(TASK_GetRTCTimeYear()/1000,
					((TASK_GetRTCTimeYear())/100)%10,
					((TASK_GetRTCTimeYear())/10)%10,
					(TASK_GetRTCTimeYear())%10,
					(TASK_GetRTCTimeMonth())/10,
					(TASK_GetRTCTimeMonth())%10,
					(TASK_GetRTCTimeDay())/10,
					(TASK_GetRTCTimeDay())%10);
	//LCD_UpdateDate(4,0,5,3,1,2,0,9);
	LCD_UpdateCircumstance(OSStateInfo[7].uiOSStateContent/10,OSStateInfo[7].uiOSStateContent%10,
							OSStateInfo[8].uiOSStateContent/10,OSStateInfo[8].uiOSStateContent%10);
	LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);
}

/******************************************************************************
*						����������	TASK_DisplaySelectSet	
*                       ����˵����  ��		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ�鶨ʱ������ʼ��������
*									
******************************************************************************/
void TASK_DisplaySelectSet (void)
{
	LCD_DisplayMenuSet();
}

/******************************************************************************
*						����������	TASK_LcdPageTreeInit	
*                       ����˵����  ��		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ��LCD��������ʼ��������
*									
******************************************************************************/
//void TASK_LcdPageTreeInit(void)
//{
///*	����LCD�ŵ�����ҳ��	*/
//	LCD_PAGE		*LCDPageSetingDoorLight;			/*	ָ��LCD�ŵ����ý����ָ��	*/
///*	����LCD���ҵ�����ҳ��	*/
//	LCD_PAGE		*LCDPageSetingBedroomLight;			/*	ָ��LCD���ҵ����ý����ָ��	*/
///*	����LCD�յ�����ҳ��	*/
//	LCD_PAGE		*LCDPageSetingAircondition;			/*	ָ��LCD�յ����ý����ָ��	*/
///*	����LCD��ˮ������ҳ��	*/
//	LCD_PAGE		*LCDPageSetingCalorifier;			/*	ָ��LCD��ˮ�����ý����ָ��	*/
///*	����LCD�ҵ�ѡ��ҳ��	*/
//	LCD_PAGE		*LCDPageSelectElec;				/*	ָ��LCD�ҵ�ѡ������ָ��	*/
///*	����LCDģʽѡ��ҳ��	*/
//	LCD_PAGE		*LCDPageSelectModel;				/*	ָ��LCDģʽѡ������ָ��	*/
///*	����LCDϵͳ���ػ�ѡ��ҳ��	*/
//	LCD_PAGE		*LCDPageSelectSys;				/*	ָ��LCDϵͳ���ػ�ѡ������ָ��	*/
///*	����LCDʱ������ҳ��	*/
//	LCD_PAGE		*LCDPageSetingTime;				/*	ָ��LCDʱ�����ý����ָ��	*/
///*	����LCD����ѡ��ҳ��	*/
//	LCD_PAGE		*LCDPageSelectSeting;				/*	ָ��LCD����ѡ������ָ��	*/
///*	����LCD������	*/
//	LCD_PAGE		*LCDPageMain;				/*	ָ��LCD�������ָ��	*/
//
///********************************���Ĳ�***************************************************/
///*	����LCD�ŵ�����ҳ��	*/
//	//LCD_PAGE		*LCDPageSetingDoorLight;			/*	ָ��LCD�ŵ����ý����ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSetingDoorLight  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingDoorLight->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSetingDoorLight->uiLcdPageID	= LCD_PAGE_SETING_DOOR_LIGHT;
//	LCDPageSetingDoorLight->uiSubPageNum	= 4;
//	LCDPageSetingDoorLight->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingDoorLight->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
///*	����LCD���ҵ�����ҳ��	*/
//	//LCD_PAGE		*LCDPageSetingBedroomLight;			/*	ָ��LCD���ҵ����ý����ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSetingBedroomLight  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingBedroomLight->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSetingBedroomLight->uiLcdPageID	= LCD_PAGE_SETING_BEDROOM_LIGHT;
//	LCDPageSetingBedroomLight->uiSubPageNum	= 4;
//	LCDPageSetingBedroomLight->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingBedroomLight->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
///*	����LCD�յ�����ҳ��	*/
//	//LCD_PAGE		*LCDPageSetingAircondition;			/*	ָ��LCD�յ����ý����ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSetingAircondition  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingAircondition->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSetingAircondition->uiLcdPageID	= LCD_PAGE_SETING_AIRCONDITION;
//	LCDPageSetingAircondition->uiSubPageNum	= 5;
//	LCDPageSetingAircondition->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingAircondition->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingAircondition->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
///*	����LCD��ˮ������ҳ��	*/
//	//LCD_PAGE		*LCDPageSetingCalorifier;			/*	ָ��LCD��ˮ�����ý����ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSetingCalorifier  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingCalorifier->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSetingCalorifier->uiLcdPageID	= LCD_PAGE_SETING_CALORIFIER;
//	LCDPageSetingCalorifier->uiSubPageNum	= 5;
//	LCDPageSetingCalorifier->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingCalorifier->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
///**********************������********************************************************/
//
///*	����LCD�ҵ�ѡ��ҳ��	*/
//	//LCD_PAGE		*LCDPageSelectElec;				/*	ָ��LCD�ҵ�ѡ������ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSelectElec  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSelectElec->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectElec->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectElec->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectElec->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectElec->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectElec->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectElec->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSelectElec->uiLcdPageID	= LCD_PAGE_SELECT_ELEC;
//	LCDPageSelectElec->uiSubPageNum	= 4;
//	LCDPageSelectElec->lcdPageNextPage[0]  = LCDPageSetingDoorLight; 		/*	ָ��Ϊ�ŵ����ý���	*/
//	LCDPageSelectElec->lcdPageNextPage[1]  = LCDPageSetingBedroomLight; 	/*	ָ��Ϊ���ҵ����ý���	*/
//	LCDPageSelectElec->lcdPageNextPage[2]  = LCDPageSetingAircondition; 	/*	ָ��Ϊ�յ����ý���	*/
//	LCDPageSelectElec->lcdPageNextPage[3]  = LCDPageSetingCalorifier; 		/*	ָ��Ϊ��ˮ�����ý���	*/
//	LCDPageSelectElec->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectElec->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectElec->lcdPagePrePage  	 = (struct lcd_page_t*)0; 			/*	ָ��Ϊ��	*/
//
//	LCDPageSetingDoorLight->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	ָ��Ϊ�ҵ�ѡ�����	*/
//	LCDPageSetingBedroomLight->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	ָ��Ϊ�ҵ�ѡ�����	*/
//	LCDPageSetingAircondition->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	ָ��Ϊ�ҵ�ѡ�����	*/
//	LCDPageSetingCalorifier->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	ָ��Ϊ�ҵ�ѡ�����	*/
//
//
///*	����LCDģʽѡ��ҳ��	*/
//	//LCD_PAGE		*LCDPageSelectModel;				/*	ָ��LCDģʽѡ������ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSelectModel  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSelectModel->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectModel->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectModel->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectModel->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectModel->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectModel->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectModel->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSelectModel->uiLcdPageID	= LCD_PAGE_SELECT_MODEL;
//	LCDPageSelectModel->uiSubPageNum	= 4;
//	LCDPageSelectModel->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectModel->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectModel->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectModel->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectModel->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectModel->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectModel->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
///*	����LCDϵͳ���ػ�ѡ��ҳ��	*/
//	//LCD_PAGE		*LCDPageSelectSys;				/*	ָ��LCDϵͳ���ػ�ѡ������ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSelectSys  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSelectSys->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSys->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSys->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSys->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSys->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSys->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSys->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSelectSys->uiLcdPageID	= LCD_PAGE_SELECT_SYS;
//	LCDPageSelectSys->uiSubPageNum	= 3;
//	LCDPageSelectSys->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSys->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSys->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSys->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSys->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSys->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSys->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
///*	����LCDʱ������ҳ��	*/
//	//LCD_PAGE		*LCDPageSetingTime;				/*	ָ��LCDʱ�����ý����ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSetingTime  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSetingTime->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingTime->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingTime->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingTime->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingTime->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingTime->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSetingTime->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSetingTime->uiLcdPageID	= LCD_PAGE_SETING_TIME;
//	LCDPageSetingTime->uiSubPageNum	= 5;
//	LCDPageSetingTime->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingTime->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingTime->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingTime->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingTime->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingTime->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSetingTime->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
///************************�ڶ���*************************************************************/
///*	����LCD����ѡ��ҳ��	*/
//	//LCD_PAGE		*LCDPageSelectSeting;				/*	ָ��LCD����ѡ������ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageSelectSeting  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageSelectSeting->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSeting->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSeting->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSeting->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSeting->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSeting->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageSelectSeting->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageSelectSeting->uiLcdPageID	= LCD_PAGE_SELECT_SETING;
//	LCDPageSelectSeting->uiSubPageNum	= 4;
//	LCDPageSelectSeting->lcdPageNextPage[0]  = LCDPageSelectModel; 		/*	ָ��Ϊģʽѡ�����	*/
//	LCDPageSelectSeting->lcdPageNextPage[1]  = LCDPageSetingTime; 		/*	ָ��Ϊʱ�����ý���	*/
//	LCDPageSelectSeting->lcdPageNextPage[2]  = LCDPageSelectElec; 		/*	ָ��Ϊ����ѡ�����	*/
//	LCDPageSelectSeting->lcdPageNextPage[3]  = LCDPageSelectSys; 		/*	ָ��Ϊϵͳ���ػ�ѡ�����	*/
//	LCDPageSelectSeting->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSeting->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageSelectSeting->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
//	LCDPageSelectModel->lcdPagePrePage  	 = LCDPageSelectSeting; 		/*	ָ��ΪLCD����ѡ��ҳ��	*/; 		/*	ָ��Ϊģʽѡ�����	*/
//	LCDPageSetingTime->lcdPagePrePage  	   	 = LCDPageSelectSeting; 		/*	ָ��ΪLCD����ѡ��ҳ��	*/;
//	LCDPageSelectElec->lcdPagePrePage  	 	 = LCDPageSelectSeting; 		/*	ָ��ΪLCD����ѡ��ҳ��	*/;
//	LCDPageSelectSys->lcdPagePrePage  	 	 = LCDPageSelectSeting; 		/*	ָ��ΪLCD����ѡ��ҳ��	*/;
//
///************************��һ��*************************************************************/
///*	����LCD������	*/
//	//LCD_PAGE		*LCDPageMain;				/*	ָ��LCD�������ָ��	*/
//	/*	����ռ�	*/
//   	LCDPageMain  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��ǰ�����ָ��	*/
//	LCDPageMain->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageMain->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageMain->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageMain->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageMain->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageMain->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	ָ��LCD��һ�������ָ��	*/
//	LCDPageMain->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	ָ��LCD��һ�������ָ��	*/
//	/*	����ֵ	*/
//	LCDPageMain->uiLcdPageID	= LCD_PAGE_MAIN;
//	LCDPageMain->uiSubPageNum	= 2;
//	LCDPageMain->lcdPageNextPage[0]  = LCDPageSelectSeting; 		/*	ָ��ΪLCD����ѡ��ҳ��	*/
//	LCDPageMain->lcdPageNextPage[1]  = LCDPageSelectElec; 			/*	ָ��Ϊ�ҵ�ѡ�����	*/
//	LCDPageMain->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageMain->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageMain->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageMain->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//	LCDPageMain->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	ָ��Ϊ��	*/
//
//	LCDPageSelectSeting->lcdPagePrePage  	 = LCDPageMain; 		/*	ָ��Ϊ������	*/
//	//LCDPageSelectElec->lcdPagePrePage  	 = LCDPageMain; 		/*	ָ��Ϊ������	*/
//
///*	LCD��������ͷָ��ָ�������������	*/
//   LCDPageTree = LCDPageMain;
//
//}

/******************************************************************************
*						����������	TASK_RTCInit	
*                       ����˵����  ��		
*											
*						�������ͣ�	void 	
*						����˵����	TASKģ��ʱ�ӳ�ʼ��������
*									
******************************************************************************/
void TASK_RTCInit (void)
{
	PREINT = Fpclk / 32768 - 1;					// ���û�׼ʱ�ӷ�Ƶ��
	PREFRAC = Fpclk - (Fpclk / 32768) * 32768;
	
	CCR   = 0x00;								// ��ֹʱ�������
	
	YEAR  = 2013;
	MONTH = 8;
	DOM   = 9;
	DOW   = 5;
	HOUR  = 8;
	MIN   = 30;
	SEC   = 50;
	
	CIIR = 0x01;								// ������ֵ����������1���ж�
	CCR  = 0x01;								// ����RTC
}

/******************************************************************************
*						����������	TASK_GetRTCTimeYear	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT16U ������ 	
*						����˵����	TASKģ���ȡʵʱʱ��	��
*									
******************************************************************************/
INT16U TASK_GetRTCTimeYear (void)
{
	INT32U uiDatas;
	INT32U uiBak;
												 	// ��ȡ������ʱ�ӼĴ���
	uiDatas = CTIME1;
	
	
	
	uiBak = (uiDatas >> 16) & 0xfff;				// ��ȡ��

	return (INT16U)uiBak;
    	
}

/******************************************************************************
*						����������	TASK_GetRTCTimeMonth	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT8U ������ 	
*						����˵����	TASKģ���ȡʵʱʱ��	��
*									
******************************************************************************/
INT8U TASK_GetRTCTimeMonth (void)
{
	INT32U uiDatas;
	INT32U uiBak;
													// ��ȡ������ʱ�ӼĴ���
	uiDatas = CTIME1;
	    	
	uiBak = (uiDatas >> 8) & 0x0f;					// ��ȡ��

	return (INT8U)uiBak;
    
}

/******************************************************************************
*						����������	TASK_GetRTCTimeDay	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT8U ������ 	
*						����˵����	TASKģ���ȡʵʱʱ��	��
*									
******************************************************************************/
INT8U TASK_GetRTCTimeDay (void)
{
	INT32U uiDatas;
	INT32U uiBak;
														// ��ȡ������ʱ�ӼĴ���
	uiDatas = CTIME1;
	    
	uiBak = uiDatas & 0x1f;							// ��ȡ��

	return (INT8U)uiBak;    
}


/******************************************************************************
*						����������	TASK_GetRTCTimeWeek	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT8U �������� 	
*						����˵����	TASKģ���ȡʵʱʱ��	����
*									
******************************************************************************/
INT8U TASK_GetRTCTimeWeek (void)
{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// ��ȡ������ʱ�ӼĴ���
	    
	uiBak = (uiTimes >> 24) & 0x07;					// ��ȡ����
	
	return (INT8U)uiBak;	
}

/******************************************************************************
*						����������	TASK_GetRTCTimeHour	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT8U ����Сʱ 	
*						����˵����	TASKģ���ȡʵʱʱ��	ʱ
*									
******************************************************************************/
INT8U TASK_GetRTCTimeHour (void)
{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// ��ȡ������ʱ�ӼĴ���
		
	uiBak = (uiTimes >> 16) & 0x1f;					// ��ȡСʱ
    
	return (INT8U)uiBak;
}

/******************************************************************************
*						����������	TASK_GetRTCTimeMin	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT8U ���ط��� 	
*						����˵����	TASKģ���ȡʵʱʱ��	��
*									
******************************************************************************/
INT8U TASK_GetRTCTimeMin (void)
{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// ��ȡ������ʱ�ӼĴ���
	    
	uiBak = (uiTimes >> 8) & 0x3f;					// ��ȡ����
    
	return (INT8U)uiBak;
}

/******************************************************************************
*						����������	TASK_GetRTCTimeSec	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT8U ������ 	
*						����˵����	TASKģ���ȡʵʱʱ��	��
*									
******************************************************************************/
INT8U TASK_GetRTCTimeSec (void)

{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// ��ȡ������ʱ�ӼĴ���
	    
	uiBak = uiTimes & 0x3f;							// ��ȡ����

	return (INT8U)uiBak;
}


/******************************************************************************
*						����������	INT8U TASK_CharToNum(INT8U c)	
*                       ����˵����  ��		
*											
*						�������ͣ�	INT8U ������ 	
*						����˵����	TASKģ���ȡʵʱʱ��	��
*									
******************************************************************************/
INT8U TASK_CharToNum(INT8U c)
{
	INT8U temp;
	switch(c)
	{
		case '0':temp = 0;break;
		case '1':temp = 1;break;
		case '2':temp = 2;break;
		case '3':temp = 3;break;
		case '4':temp = 4;break;
		case '5':temp = 5;break;
		case '6':temp = 6;break;
		case '7':temp = 7;break;
		case '8':temp = 8;break;
		case '9':temp = 9;break;
		case 0:temp = '0';break;
		case 1:temp = '1';break;
		case 2:temp = '2';break;
		case 3:temp = '3';break;
		case 4:temp = '4';break;
		case 5:temp = '5';break;
		case 6:temp = '6';break;
		case 7:temp = '7';break;
		case 8:temp = '8';break;
		case 9:temp = '9';break;
		default :temp = c;break;
	}
	return temp;
}

/******************************************************************************
*						����������	void TASK_SendStatTbl(void)	
*                       ����˵����  ��		
*											
*						�������ͣ�	�� 	
*						����˵����	����״̬��Ϣ������ݸ���λ��
*									
******************************************************************************/
void TASK_SendStatTbl(void)
{
	INT8U cInstruction[9][14];    //���淭�����ݽ��������
	INT8U  i;					  //ѭ����������
	
	//�ŵƿ���
	cInstruction[0][0]='d';	  
	if(OSStateInfo[0].uiOSStateContent)	cInstruction[0][1]='1';
	else cInstruction[0][1]='0';
	for(i=2;i<13;i++) cInstruction[0][i]='0'; 
	//���ҵƿ���
	cInstruction[1][0]='f';
	if(OSStateInfo[1].uiOSStateContent)	cInstruction[1][1]='1';
	else cInstruction[1][1]='0';
	for(i=2;i<13;i++) cInstruction[1][i]='0'; 
	//�յ�����
	cInstruction[2][0]='h';
	if(OSStateInfo[2].uiOSStateContent)	cInstruction[2][1]='1';
	else cInstruction[2][1]='0';
	for(i=2;i<13;i++) cInstruction[2][i]='0'; 
	//��ˮ������
	cInstruction[3][0]='k';
	if(OSStateInfo[3].uiOSStateContent)	cInstruction[3][1]='1';
	else cInstruction[3][1]='0';
	for(i=2;i<13;i++) cInstruction[3][i]='0'; 
	//�յ��¶�
	cInstruction[4][0]='i';
	cInstruction[4][1]=TASK_CharToNum(OSStateInfo[4].uiOSStateContent/10);
	cInstruction[4][2]=TASK_CharToNum(OSStateInfo[4].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[4][i]='0';
	//��ˮ���¶�
	cInstruction[5][0]='l';
	cInstruction[5][1]=TASK_CharToNum(OSStateInfo[5].uiOSStateContent/10);
	cInstruction[5][2]=TASK_CharToNum(OSStateInfo[5].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[5][i]='0';
	//ϵͳģʽ
	cInstruction[6][0]='n';
	cInstruction[6][1] = TASK_CharToNum(OSStateInfo[6].uiOSStateContent);
	for(i=2;i<13;i++) cInstruction[6][i]='0';		
	//��ǿ
	cInstruction[7][0]='p';
	cInstruction[7][1]=TASK_CharToNum(OSStateInfo[7].uiOSStateContent/10);
	cInstruction[7][2]=TASK_CharToNum(OSStateInfo[7].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[7][i]='0';
	//����
	cInstruction[8][0]='q';
	cInstruction[8][1]=TASK_CharToNum(OSStateInfo[8].uiOSStateContent/10);
	cInstruction[8][2]=TASK_CharToNum(OSStateInfo[8].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[8][i]='0';
	for(i=0;i<9;i++) cInstruction[i][13]='\0';
	//��������
	for(i=0;i<9;i++)
	{	
		COM_SendDataDown(cInstruction[i]);
		DelayNS(15);


	}

}

/******************************************************************************
*						����������	void TASK_SendTimingTbl(void)	
*                       ����˵����  ��		
*											
*						�������ͣ�	�� 	
*						����˵����	���Ͷ�ʱ���������ݸ���λ��
*									
******************************************************************************/
void TASK_SendTimingTbl(void)
{
	INT8U i,j;
	INT8U cInstruction[4][14];
	INT8U cFstChar[4]={'e','g','j','m'};
	
	for(i=0;i<4;i++)
	{
		cInstruction[i][0]=cFstChar[i];
		cInstruction[i][1]=TASK_CharToNum(TimingTbl[i].uiTimeHour/10);
		cInstruction[i][2]=TASK_CharToNum(TimingTbl[i].uiTimeHour%10);
		cInstruction[i][3]=TASK_CharToNum(TimingTbl[i].uiTimeMinute/10);
		cInstruction[i][4]=TASK_CharToNum(TimingTbl[i].uiTimeMinute%10);
		cInstruction[i][5]=TASK_CharToNum(TimingSW[i]);
		//ʹ��
		for(j=6;j<13;j++) cInstruction[i][j] = '0';
		cInstruction[i][13]='\0';
			
	}
	COM_SendDataDown(cInstruction[0]);
	COM_SendDataDown(cInstruction[1]);
	COM_SendDataDown(cInstruction[2]);
	COM_SendDataDown(cInstruction[3]);
		
}

/*****************************************************************************
*����: DelayNS()
*����: �����ʱ
*****************************************************************************/

void  DelayNS(INT32U nDly)
{  
    INT32U nLoop;

    for(; nDly>0; nDly--) 
        for(nLoop=0; nLoop<50000; nLoop++);
}

/****************************************************************************
* �������ƣ�BeepCount()
* ��    �ܣ���������ָ����������
****************************************************************************/

void BeepCount(INT8U count)
{
 	for(;count>0;count--)
    {
    	IOSET|=BEEP;                   		      //�������� 
		DelayNS(10);
       	IOCLR|=BEEP;                   			  //�رշ�����
		DelayNS(10);
    }
}

/******************************************************************************
*                            End Of File
******************************************************************************/
