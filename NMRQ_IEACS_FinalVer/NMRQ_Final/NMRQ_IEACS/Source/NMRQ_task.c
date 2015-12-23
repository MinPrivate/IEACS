/******************************************************************************
*						文件名：	NMRQ_task.c	
*                       文件描述：	本文件为TASK模块数据初始化、任务逻辑、及其他系统功能的编写  
*                       作者：		程敏
*						创建时间： 	2013-8-1
******************************************************************************/

#include "..\Include\config.h"
#include "..\Include\NMRQ_task_glb.h"
#include "..\Include\NMRQ_task.h"




/*一些需要使用到的外部函数的声明*/
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

/*任务堆栈声明*/
OS_STK        TASK_KeyDecStk[TASK_STK_SIZE];
OS_STK        TASK_PcDecStk[TASK_STK_SIZE];
OS_STK        TASK_EventHdlStk[TASK_STK_SIZE];
OS_STK        TASK_PCParseStk[TASK_STK_SIZE];									


/******************************************************************************
*						函数命名：	TASK_Start	
*                       参数说明：  1、  pdata		//任务参数		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块开启任务
*									对IEACS系统进行初始化
*									开启时钟节拍中断并建立任务
******************************************************************************/
void  TASK_Start(void *pdata)
{
	pdata = pdata;

	TASK_Init();
	T0TCR = 1;	/*开启时钟节拍中断*/

	TASK_DisplayMain ();                           	
	OSTaskCreate(TASK_KeyDec, (void *)0, &TASK_KeyDecStk[TASK_STK_SIZE - 1], TASK_PRIO_KEYDEC);
    OSTaskCreate(TASK_PcDec, (void *)0, &TASK_PcDecStk[TASK_STK_SIZE - 1], TASK_PRIO_PCDEC);
    OSTaskCreate(TASK_PC_Parse, (void *)0, &TASK_PCParseStk[TASK_STK_SIZE - 1], TASK_PRIO_PC_PARSE);
	//OSTaskCreate(TASK_Timing, (void *)0, &TASK_TimingStk[TASK_STK_SIZE - 1], TASK_PRIO_TIMING);
                        
    for (;;)																	
    {
		/*	系统级的操作	*/
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
*						函数命名：	TASK_KeyDec	
*                       参数说明：  1、  pdata		//任务参数		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块按键检测任务，检测键盘按键信息。
*									当检测到键盘按键信息后唤醒TASK_Parse任务
*									并把按键信息传递给TASK_Parse进行信息解析。
******************************************************************************/
void  TASK_KeyDec(void *pdata)
{
	INT8U	uiTimeNoKey = 0;			/*	记录到15s没有按键按下时置位OSPowerSave	*/
	INT8U uiIsKeyDown;
	INT8U uiTempKeyType;
	INT8U uiTempKeyValue;	

	pdata = pdata;
	
	//T0TCR = 1;	/*开启时钟节拍中断*/
     //TASK_Init();  
	 BeepCount(1);                       	
	                      
    for (;;)																	
    {	/*	判断是否有按键按下	*/
		uiIsKeyDown = HI_IfKeyClicked();

		if(uiIsKeyDown != KEY_UNCLICKED)  					/*	检测到有按键按下	*/
		{													/*	得到键值及按键类型	*/
		  	 uiTempKeyType = HI_GetKeyValue_LongOrShort();
		  	 uiTempKeyValue = HI_GetKeyValue_whichKey();
		   	
		   	BeepCount(1);
			TASK_KeyParse(uiTempKeyType,uiTempKeyValue);

															

		   
		   uiTimeNoKey = 0;									/*	有按键按下uiTimeNoKey清零	*/
		   
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
*						函数命名：	TASK_PcDec	
*                       参数说明：  1、  pdata		//任务参数		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块串口检测任务，
*									检测PC端通过串口向下位机传递的信息。
*									当检测到测PC端通过串口向下位机传递的信息
*									后唤醒TASK_Parse任务并把信息传递给TASK_Parse
*									进行信息解析。
******************************************************************************/
void  TASK_PcDec(void *pdata)
{
	
	int i;
	pdata = pdata; 		                              //防止编译警告

	InitialiseUART0(9600);	                          //初始化串口 

    for (;;)																	
    {
		OS_ENTER_CRITICAL();						  //关中断
		//COM_SendDataDown("d000000000000"); 
		if((U0LSR & 0x01)==0x01)
		{
			for(i=0;i<=13;)
			{
										  //若无数据则不执行
				PCBuffer[i]=U0RBR;
				i++;
					//DelayNS(10);
			}
			//for(i=0;i<13;i++) COM_SendByteDown(PCBuffer[i]);

			OSTaskResume(TASK_PRIO_PC_PARSE);
		}
		
		OS_EXIT_CRITICAL();							  //开中断

		OSTimeDly(20);	
    }
}


/******************************************************************************
*						函数命名：	TASK_KeyParse	
*                       参数说明：  1、  pdata		//任务参数		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块信息解析任务，
*									解析TASK_KeyDec与TASK_PcDec检测到的信息。
*									通过信息解析后得到信息所代表的操作，
*									唤醒TASK_EventHdl任务进行操作处理。
******************************************************************************/
void  TASK_KeyParse(INT8U uiTempKeyType,INT8U uiTempKeyValue)
{
	INT8U uiTempOpeState; 									/*	记录操作执行情况	*/
	INT8U uiTempIns[14];
	INT8U i;
//	pdata = pdata;
	                            	
	/*	按键操作完成，清空OSIsKeyDown信息	*/
	if(LCDCurrentPage == LCD_PAGE_MAIN) 	
	{	/*	当前界面为主界面	*/
	 	if(uiTempKeyType == KEY_LONGCLICKED)			
		{	/*	当前按键类型为长按	*/
		 	switch(uiTempKeyValue)
			{
				case KEY_SWI2:				/*	长按KEY_SWI2的操作 模拟AD	*/
								HI_SwapTempAndLight();
								/*	刷新开关状态	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[0].uiOSStateContent) COM_SendDataDown("d100000000000");
								else COM_SendDataDown("d000000000000");
								if(OSStateInfo[2].uiOSStateContent) COM_SendDataDown("h100000000000");
								else COM_SendDataDown("h000000000000");
								/*	刷新温度光强状态	*/
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
				case KEY_SWI1:				/*	长按KEY_SWI3的操作 进入设置选择界面	*/
								LCDCurrentPage = LCD_PAGE_SELECT_SETING;
								LCDCurrentFocus = 0;
								/*	LCD显示刷新	*/
								TASK_DisplaySelectSet ();
								LCD_SelectMenuSetItem(LCDCurrentPage,LCDCurrentFocus);
								break;
				case KEY_SWI3:				/*	长按KEY_SWI4的操作 模拟小偷中断	*/
								COM_SendDataDown("r000000000000");
								HI_Control(OS_STATE_INFO_TYPE_INT,OS_STATE_CTRL_OBJ_THIEF,1);
								
								//LCD显示刷新/////////////////////////////////////////////////////////////////////
								break;
				case KEY_SWI4:				/*	长按KEY_SWI4的操作 模拟煤气中断	*/
								COM_SendDataDown("s000000000000");
								HI_Control(OS_STATE_INFO_TYPE_INT,OS_STATE_CTRL_OBJ_GASLEAK,1);
								/*	LCD显示刷新	*/
								
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								
								break;
				default:		break;
			}
		}
		if(uiTempKeyType == KEY_SHORTCLICKED)			
		{	/*	当前按键类型为短按	*/
		 	switch(uiTempKeyValue)
			{
			 	case KEY_SWI1:			/*	短按KEY_SWI1的操作 对门灯进行开关操作	*/
								/*	门灯的开关操作	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_DOOR_LIGHT,!(OSStateInfo[0].uiOSStateContent));
								/*	如果操作成功 LCD显示刷新
									PC显示刷新（如果连接）	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[0].uiOSStateContent) COM_SendDataDown("d100000000000");
								else COM_SendDataDown("d000000000000");
								break;
				case KEY_SWI2:			/*	短按KEY_SWI2的操作 对卧室灯进行开关操作	*/
								/*	卧室灯的开关操作	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,!(OSStateInfo[1].uiOSStateContent));
								/*	如果操作成功LCD显示刷新
									PC显示刷新（如果连接）	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[1].uiOSStateContent) COM_SendDataDown("f100000000000");
								else COM_SendDataDown("f000000000000");
								break;
				case KEY_SWI3:			/*	短按KEY_SWI3的操作 对空调进行开关操作	*/
								/*	空调的开关操作	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_AIRCONDITION,!(OSStateInfo[2].uiOSStateContent));
								/*	如果操作成功LCD显示刷新
									PC显示刷新（如果连接）	*/
								LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
												OSStateInfo[1].uiOSStateContent,
												OSStateInfo[2].uiOSStateContent,
												OSStateInfo[3].uiOSStateContent);
								if(OSStateInfo[2].uiOSStateContent) COM_SendDataDown("h100000000000");
								else COM_SendDataDown("h000000000000");
								break;
				case KEY_SWI4:			/*	短按KEY_SWI4的操作 对热水器进行开关操作	*/
								/*	热水器的开关操作	*/
								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_CALORIFIER,!(OSStateInfo[3].uiOSStateContent));
								/*	如果操作成功LCD显示刷新
									PC显示刷新（如果连接）	*/
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
	{	/*	当前LCD界面为非主界面	*/
		if(uiTempKeyType == KEY_SHORTCLICKED)			
				{	/*	当前按键类型为短按	*/
					switch(uiTempKeyValue)
					{
					 	case KEY_SWI2:	/*	短按KEY_SWI2的操作 确认操作 进行界面切换	*/
										if(LCDCurrentFocus < 5)
										{/*	进入下一级界面	*/
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
														/*	返回主界面	*/
														TASK_DisplayMain ();
														TASK_DisplayMain ();
														break;
												default:break;
											}
										}									
										break;
						case KEY_SWI4:	/*	短按KEY_SWI4的操作 焦点切换级操作	*/
										LCDCurrentFocus = (LCDCurrentFocus + 1) % 5;
										/*	界面刷新或切换	页面不切换、焦点切换	*/
										LCD_SelectMenuSetItem(LCDCurrentPage,LCDCurrentFocus);
										break;
						//case KEY_SWI1:	/*	短按KEY_SWI1的操作 加 1 操作	*/
						//				break;
						//case KEY_SWI3:	/*	短按KEY_SWI3的操作 减 1 操作	*/
						//				break;
						default:		break;
					}
				}
	}
//	else if(LCDCurrentPage == LCD_PAGE_SELECT_MODEL)
//	{	/*	当前LCD界面为非主界面	*/
//		if(uiTempKeyType == KEY_SHORTCLICKED)			
//				{	/*	当前按键类型为短按	*/
//					switch(uiTempKeyValue)
//					{
//					 	case KEY_SWI2:	/*	短按KEY_SWI2的操作 确认操作 进行界面切换	*/
//										if(LCDCurrentFocus < 5)
//										{/*	进入下一级界面	*/
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
//														/*	返回主界面	*/
//														LCD_DisplayMenuSet ();
//														break;
//												default:break;
//											}
//										}									
//										break;
//						case KEY_SWI4:	/*	短按KEY_SWI4的操作 焦点切换级操作	*/
//										LCDCurrentFocus = (LCDCurrentFocus + 1) % 5;
//										/*	界面刷新或切换	页面不切换、焦点切换	*/
//										LCD_SelectMedelSelectItem(LCDCurrentPage,LCDCurrentFocus);
//										break;
//						//case KEY_SWI1:	/*	短按KEY_SWI1的操作 加 1 操作	*/
//						//				break;
//						//case KEY_SWI3:	/*	短按KEY_SWI3的操作 减 1 操作	*/
//						//				break;
//						default:		break;
//					}
//				}
//	}
	else{;}  	

}



/******************************************************************************
*						函数命名：	TASK_Timing	
*                       参数说明：  1、  pdata		//任务参数		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块定时操作处理任务，
*									处理系统中电器定时，当电器定时到达时间时，
*									唤醒TASK_EventHdl任务进行相应的定时操作。
******************************************************************************/
//void  TASK_Timing(void *pdata)
//{
//	INT8U 	uiTempCount;						/*	定时任务表遍历下标	*/
//	INT8U	uiTempTimingSW;						/*	对应的定时开关操作	*/
//
//	INT8U 	uiTempOpeState;
//												/*	记录操作执行情况	*/
//	pdata = pdata;
//	                            		                        
//    for (;;)																	
//    {
//		while (0 == (ILR & 0x01));				/* 等待RTC增量中断	*/
//		ILR = 0x01;								/* 清除中断标志	*/
//		
//		/*	遍历定时任务表，如果有定时任务到就做相应的操作	*/
//		for(uiTempCount = 0; uiTempCount < TIMING_TBL_SIZE; uiTempCount++)
//		{
//		 	if(TASK_GetRTCTimeHour() == TimingTbl[uiTempCount].uiTimeHour	&&
//				TASK_GetRTCTimeMin() == TimingTbl[uiTempCount].uiTimeMinute	)
//				{
//				 	/*	检测到了定时时间与当前时间吻合，清空定时任务表并作相应的开关操作	*/
//					TimingTbl[uiTempCount].uiTimeHour 	= 0;
//					TimingTbl[uiTempCount].uiTimeMinute = 0;
//					/*	得到当前定时任务是定时开还是定时关	*/
//					uiTempTimingSW = TimingSW[uiTempCount];
//
//					/*	定时任务操作	*/
//					switch(uiTempCount)
//					{	/*	门灯定时开关	*/
//						case 0:
//								//门灯的开关操作/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_DOOR_LIGHT,uiTempTimingSW);
//								//如果操作成功 LCD显示刷新/////////////////////////////////////////////////////////////////////
//								//PC显示刷新（如果连接）/////////////////////////////////////////////////////////////////////
//								
//								break;
//						/*	卧室灯定时开关	*/
//						case 1:
//								//卧室灯的开关操作/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,uiTempTimingSW);
//								//如果操作成功LCD显示刷新/////////////////////////////////////////////////////////////////////
//								//PC显示刷新（如果连接）/////////////////////////////////////////////////////////////////////
//
//								break;
//						/*	空调定时开关	*/
//						case 2:
//								//空调的开关操作/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_AIRCONDITION,uiTempTimingSW);
//								//如果操作成功LCD显示刷新/////////////////////////////////////////////////////////////////////
//								//PC显示刷新（如果连接）/////////////////////////////////////////////////////////////////////
//
//								break;
//						/*	热水器定时开关	*/
//						case 3:
//								//热水器的开关操作/////////////////////////////////////////////////////////////////////
//								uiTempOpeState = HI_Control(OS_STATE_INFO_TYPE_SWITCH,OS_STATE_CTRL_OBJ_CALORIFIER,uiTempTimingSW);
//								//如果操作成功LCD显示刷新/////////////////////////////////////////////////////////////////////
//								//PC显示刷新（如果连接）/////////////////////////////////////////////////////////////////////
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
*						函数命名：	TASK_PC_Parse	
*                       参数说明：  1、  pdata		//任务参数		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块串口通信操作解析任务，
*									处理串口发送过来的信息，根据信息
*									调用不同的模块接口进行事件处理
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
			case 'a':               //连接请求，返回一个b000000000000表示连接成功
				//COM_SendDataDown("I've received a link request\n");
				COM_SendDataDown("b000000000000");
				PCConnectState=TRUE;
				if(LCDCurrentPage==LCD_PAGE_MAIN)
				{
					TASK_DisplayMain();
				}
				break;	
			case 'c':               //状态请求
				//COM_SendDataDown("I've received a state request\n");
				//将状态表发送给上位机
				TASK_SendStatTbl();
				//将定时表发送给上位机
				TASK_SendTimingTbl();
				
				break;    			 
			case 'd':				//门灯开关，后面的字符为0关，1开
				if(PCBuffer[1]=='0') 
				{
					//COM_SendDataDown("Turn off the door light\n");
					//调用HI模块关门灯
					HI_Control(OS_STATE_CTRL_OBJ_DOOR_LIGHT,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_OFF);

				}
				else if(PCBuffer[1]=='1') 
				{
					//COM_SendDataDown("Turn on the door light\n");
					//调用HI模块开门灯
					HI_Control(OS_STATE_CTRL_OBJ_DOOR_LIGHT,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_ON);
				}
				LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);					
				break;	 
			case 'e':				//门灯定时
				//COM_SendDataDown("Turn off the door light at:\n");
				//将定时任务添加到定时任务表
				TimingTbl[0].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[0].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[0]					= TASK_CharToNum(PCBuffer[5]);
				break;	
			case 'f':				//卧室灯开关
				if(PCBuffer[1]=='0') 
				{
					//COM_SendDataDown("Turn off the room light\n");
					//调用HI模块关卧室灯
					HI_Control(OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_OFF);

				}
				else if(PCBuffer[1]=='1') 
				{
					//COM_SendDataDown("Turn on the room light\n");
					//调用HI模块开卧室灯
					HI_Control(OS_STATE_CTRL_OBJ_BEDROOM_LIGHT,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_ON);
				}
					LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);

				break;    
			case 'g':								//卧室灯定时   后续六字节数字
				/*将定时任务添加到定时任务表*/
				TimingTbl[1].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[1].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[1]					= TASK_CharToNum(PCBuffer[5]);
				break;	 
			case 'h':								//空调开关	   后续一字节数据
				if(PCBuffer[1]=='0')       //关操作
				{
					//COM_SendDataDown("Turn off the Air Conditioner\n");
					//调用HI模块关空调
					HI_Control(OS_STATE_CTRL_OBJ_AIRCONDITION,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_OFF);
				}
				else if(PCBuffer[1]=='1') 	 //开操作
				{
					//COM_SendDataDown("Turn on the Air Conditioner\n");
					//调用HI模块开空调
					HI_Control(OS_STATE_CTRL_OBJ_AIRCONDITION,
									OS_STATE_INFO_TYPE_SWITCH ,
									OS_ELEC_SWITCH_STATE_ON);
				}
					LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);
				break;	
			case 'i':				//空调温度	   后续两字节数据
				HI_Control(OS_STATE_CTRL_OBJ_AIRCONDITION,
							OS_STATE_INFO_TYPE_TEMP ,
							TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]));
				break;	   
			case 'j':				//空调定时	   后续六字节数据
				TimingTbl[2].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[2].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[2]					= TASK_CharToNum(PCBuffer[5]);
				break;	
			case 'k':				//热水器开关   后续一字节数据
				if(PCBuffer[1]=='0')       //关操作
				{
					//COM_SendDataDown("Turn off the Calorifier\n");
					//调用HI模块关热水器
					HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_OFF);
				}
				else if(PCBuffer[1]=='1') 	 //开操作
				{
					//COM_SendDataDown("Turn on the Calorifier\n");
					//调用HI模块开热水器
					HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
								OS_STATE_INFO_TYPE_SWITCH ,
								OS_ELEC_SWITCH_STATE_ON);
				}
					LCD_UpdateApplianceState(OSStateInfo[0].uiOSStateContent,
								OSStateInfo[1].uiOSStateContent,
								OSStateInfo[2].uiOSStateContent,
								OSStateInfo[3].uiOSStateContent);
				break;	
			case 'l':				//热水器温度   后续两字节数据
				//调用HI模块设置空调温度
				HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
							OS_STATE_INFO_TYPE_TEMP ,
							TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]));
				break;	
			case 'm':				//热水器定时   后续六字节数据
				//将接收到的定时任务写入定时任务表
				TimingTbl[3].uiTimeHour		= TASK_CharToNum(PCBuffer[1])*10+TASK_CharToNum(PCBuffer[2]);			
				TimingTbl[3].uiTimeMinute	= TASK_CharToNum(PCBuffer[3])*10+TASK_CharToNum(PCBuffer[4]);
				TimingSW[3]					= TASK_CharToNum(PCBuffer[5]);
				break;
			case 'n':				//系统工作模式 后续一字节数据
				//调用HI模块改变系统模式
				HI_Control(OS_STATE_CTRL_OBJ_CALORIFIER,
							OS_STATE_INFO_TYPE_TEMP ,
							TASK_CharToNum(PCBuffer[1]));
				
				break;
			case 'o':			    //系统时间	   后续十二字节数据 上位机单方向发送
				//下位机根据上位机传来的时间进行调整
				/* 年 */
				YEAR 	= (INT16U)(TASK_CharToNum(PCBuffer[1])*1000+
									TASK_CharToNum(PCBuffer[2])*100+
									TASK_CharToNum(PCBuffer[3])*10+
									TASK_CharToNum(PCBuffer[4]));
				/* 月 */
				MONTH	= (INT8U)(TASK_CharToNum(PCBuffer[5])*10+
									TASK_CharToNum(PCBuffer[6]));
				/* 日 */
				DOM		= (INT8U)(TASK_CharToNum(PCBuffer[7])*10+
									TASK_CharToNum(PCBuffer[8]));
				/* 时 */
				HOUR	= (INT8U)(TASK_CharToNum(PCBuffer[9])*10+
									TASK_CharToNum(PCBuffer[10]));
				/* 分 */
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
*						函数命名：	TASK_Init	
*                       参数说明：  无		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块初始化函数，
*									初始化系统全局变量。
******************************************************************************/
void  TASK_Init(void)
{
/*	初始化时关闭蜂鸣器	*/
	PINSEL0=0x00000000;              			/* 设置IO口工作模式	  */
   	PINSEL1=0x00000000;
   	IODIR |=BEEP;
   	IOCLR|=BEEP;                   			  	/*关闭蜂鸣器	*/

/*	初始化实时时钟	*/
	TASK_RTCInit ();

/*	初始化系统状态表	*/
	TASK_OSStateInfoInit();

/*	初始化定时任务表	*/
	TASK_TimingTblInit();
/*	初始化LCD界面树	*/
	//TASK_LcdPageTreeInit();

/*	以下是全局变量初始化	*/
	LCDCurrentPage  = LCD_PAGE_MAIN;				/*	当前LCD页面为LCD页面树头部即 主页面	*/
	LCDCurrentFocus = 0;						/*	LCD当前界面的当前焦点	*/

	PCConnectState  = 0;						/*	PC当前连接状态	*/
	//OSCurrentTime.uiTimeYear	= 2013;			/*	系统时间	*/
	//OSCurrentTime.uiTimeMonth	= 1;			/*	系统时间	*/
	//OSCurrentTime.uiTimeDay		= 1;			/*	系统时间	*/
	//OSCurrentTime.uiTimeHour	= 1;			/*	系统时间	*/
	//OSCurrentTime.uiTimeMinute	= 1;			/*	系统时间	*/
	//OSCurrentTime.uiTimeSecond	= 1;			/*	系统时间	*/

//	OSIsKeyDown		  	= KEY_UNCLICKED;		/*	系统初始时未有按键按下	*/
//	OSCurrentKeyInfo	= (struct key_info_t*)malloc(sizeof(struct key_info_t));			/*	记录当前检测到的按键信息	*/
	OSCurrentPcInfo		= (struct os_state_info_t*)malloc(sizeof(struct os_state_info_t));	/*	记录当前检测到的PC端信息	*/

//	OSOneMin			= 0;						/*	记录1s	*/

	OSPowerSave			= FALSE;					/*	记录系统是否进入省电模式	*/

/*  PCBuffer初始化  */
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
*						函数命名：	TASK_OSStateInfoInit	
*                       参数说明：  无		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块系统状态表初始化函数，
*									
******************************************************************************/
void TASK_OSStateInfoInit (void)
{
	/*	系统状态表，保存系统状态信息	*/
	OSStateInfo[0].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_DOOR_LIGHT;			/*	门灯	*/
	OSStateInfo[0].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	开关	*/
	OSStateInfo[0].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	关	*/

	OSStateInfo[1].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_BEDROOM_LIGHT;		/*	卧室灯	*/
	OSStateInfo[1].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	开关	*/
	OSStateInfo[1].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	关	*/

	OSStateInfo[2].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AIRCONDITION;		/*	空调	*/
	OSStateInfo[2].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	开关	*/
	OSStateInfo[2].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	关	*/

	OSStateInfo[3].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_CALORIFIER;			/*	热水器	*/
	OSStateInfo[3].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SWITCH;  			/*	开关	*/
	OSStateInfo[3].uiOSStateContent 	= OS_ELEC_SWITCH_STATE_OFF;				/*	关	*/

	OSStateInfo[4].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AIRCONDITION;		/*	空调	*/
	OSStateInfo[4].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_TEMP;  			/*	温度	*/
	OSStateInfo[4].uiOSStateContent 	= 26;									/*	初始化为0	*/

	OSStateInfo[5].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_CALORIFIER;			/*	热水器	*/
	OSStateInfo[5].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_TEMP;  			/*	温度	*/
	OSStateInfo[5].uiOSStateContent 	= 50;									/*	初始化为0	*/

	OSStateInfo[6].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_SYS;				/*	系统	*/
	OSStateInfo[6].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_MODEL;  			/*	模式	*/
	OSStateInfo[6].uiOSStateContent 	= OS_MODEL_STATE_COMMON;				/*	普通模式	*/

	OSStateInfo[7].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AD;					/*	AD	*/
	OSStateInfo[7].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SENTEMP;  			/*	感温	*/
	OSStateInfo[7].uiOSStateContent 	= 30;									/*	初始化为0	*/

	OSStateInfo[8].uiOSStateCtrlObj 	= OS_STATE_CTRL_OBJ_AD;					/*	AD	*/
	OSStateInfo[8].uiOSStateInfoType 	= OS_STATE_INFO_TYPE_SENLIGHT;  		/*	感光	*/
	OSStateInfo[8].uiOSStateContent 	= 45;									/*	初始化为0	*/
}

/******************************************************************************
*						函数命名：	TASK_TimingTblInit	
*                       参数说明：  无		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块定时任务表初始化函数，
*									
******************************************************************************/
void TASK_TimingTblInit (void)
{
	INT8U 	uiTempCount;						/*	定时任务表遍历下标	*/
	
	/*	定时任务表中：数组下标为 0 表示定时对象为	门灯
					  数组下标为 1 表示定时对象为	卧室灯
					  数组下表为 2 表示定时对象为	空调
					  数组下表为 3 表示定时对象为	热水器	*/
	for(uiTempCount = 0; uiTempCount < TIMING_TBL_SIZE; uiTempCount++)
	{
		TimingTbl[uiTempCount].uiTimeYear		= OSCurrentTime.uiTimeYear;			
		TimingTbl[uiTempCount].uiTimeMonth		= OSCurrentTime.uiTimeMonth;		
		TimingTbl[uiTempCount].uiTimeDay		= OSCurrentTime.uiTimeDay;		
		TimingTbl[uiTempCount].uiTimeHour		= 0;			
		TimingTbl[uiTempCount].uiTimeMinute		= 0;		
		TimingTbl[uiTempCount].uiTimeSecond		= 0;		
		TimingSW[uiTempCount]					= OS_ELEC_SWITCH_STATE_OFF;	  /*初始化为关	*/

	}
}


/******************************************************************************
*						函数命名：	TASK_DisplayMain	
*                       参数说明：  无		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块定时任务表初始化函数，
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
*						函数命名：	TASK_DisplaySelectSet	
*                       参数说明：  无		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块定时任务表初始化函数，
*									
******************************************************************************/
void TASK_DisplaySelectSet (void)
{
	LCD_DisplayMenuSet();
}

/******************************************************************************
*						函数命名：	TASK_LcdPageTreeInit	
*                       参数说明：  无		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块LCD界面树初始化函数，
*									
******************************************************************************/
//void TASK_LcdPageTreeInit(void)
//{
///*	创建LCD门灯设置页面	*/
//	LCD_PAGE		*LCDPageSetingDoorLight;			/*	指向LCD门灯设置界面的指针	*/
///*	创建LCD卧室灯设置页面	*/
//	LCD_PAGE		*LCDPageSetingBedroomLight;			/*	指向LCD卧室灯设置界面的指针	*/
///*	创建LCD空调设置页面	*/
//	LCD_PAGE		*LCDPageSetingAircondition;			/*	指向LCD空调设置界面的指针	*/
///*	创建LCD热水器设置页面	*/
//	LCD_PAGE		*LCDPageSetingCalorifier;			/*	指向LCD热水器设置界面的指针	*/
///*	创建LCD家电选择页面	*/
//	LCD_PAGE		*LCDPageSelectElec;				/*	指向LCD家电选择界面的指针	*/
///*	创建LCD模式选择页面	*/
//	LCD_PAGE		*LCDPageSelectModel;				/*	指向LCD模式选择界面的指针	*/
///*	创建LCD系统开关机选择页面	*/
//	LCD_PAGE		*LCDPageSelectSys;				/*	指向LCD系统开关机选择界面的指针	*/
///*	创建LCD时间设置页面	*/
//	LCD_PAGE		*LCDPageSetingTime;				/*	指向LCD时间设置界面的指针	*/
///*	创建LCD设置选择页面	*/
//	LCD_PAGE		*LCDPageSelectSeting;				/*	指向LCD设置选择界面的指针	*/
///*	创建LCD主界面	*/
//	LCD_PAGE		*LCDPageMain;				/*	指向LCD主界面的指针	*/
//
///********************************第四层***************************************************/
///*	创建LCD门灯设置页面	*/
//	//LCD_PAGE		*LCDPageSetingDoorLight;			/*	指向LCD门灯设置界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSetingDoorLight  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingDoorLight->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSetingDoorLight->uiLcdPageID	= LCD_PAGE_SETING_DOOR_LIGHT;
//	LCDPageSetingDoorLight->uiSubPageNum	= 4;
//	LCDPageSetingDoorLight->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingDoorLight->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingDoorLight->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
///*	创建LCD卧室灯设置页面	*/
//	//LCD_PAGE		*LCDPageSetingBedroomLight;			/*	指向LCD卧室灯设置界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSetingBedroomLight  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingBedroomLight->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSetingBedroomLight->uiLcdPageID	= LCD_PAGE_SETING_BEDROOM_LIGHT;
//	LCDPageSetingBedroomLight->uiSubPageNum	= 4;
//	LCDPageSetingBedroomLight->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingBedroomLight->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingBedroomLight->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
///*	创建LCD空调设置页面	*/
//	//LCD_PAGE		*LCDPageSetingAircondition;			/*	指向LCD空调设置界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSetingAircondition  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSetingAircondition->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingAircondition->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingAircondition->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingAircondition->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingAircondition->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingAircondition->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingAircondition->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSetingAircondition->uiLcdPageID	= LCD_PAGE_SETING_AIRCONDITION;
//	LCDPageSetingAircondition->uiSubPageNum	= 5;
//	LCDPageSetingAircondition->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingAircondition->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingAircondition->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingAircondition->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingAircondition->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingAircondition->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingAircondition->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
///*	创建LCD热水器设置页面	*/
//	//LCD_PAGE		*LCDPageSetingCalorifier;			/*	指向LCD热水器设置界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSetingCalorifier  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingCalorifier->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSetingCalorifier->uiLcdPageID	= LCD_PAGE_SETING_CALORIFIER;
//	LCDPageSetingCalorifier->uiSubPageNum	= 5;
//	LCDPageSetingCalorifier->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingCalorifier->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingCalorifier->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
///**********************第三层********************************************************/
//
///*	创建LCD家电选择页面	*/
//	//LCD_PAGE		*LCDPageSelectElec;				/*	指向LCD家电选择界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSelectElec  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSelectElec->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectElec->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectElec->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectElec->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectElec->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectElec->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectElec->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSelectElec->uiLcdPageID	= LCD_PAGE_SELECT_ELEC;
//	LCDPageSelectElec->uiSubPageNum	= 4;
//	LCDPageSelectElec->lcdPageNextPage[0]  = LCDPageSetingDoorLight; 		/*	指向为门灯设置界面	*/
//	LCDPageSelectElec->lcdPageNextPage[1]  = LCDPageSetingBedroomLight; 	/*	指向为卧室灯设置界面	*/
//	LCDPageSelectElec->lcdPageNextPage[2]  = LCDPageSetingAircondition; 	/*	指向为空调设置界面	*/
//	LCDPageSelectElec->lcdPageNextPage[3]  = LCDPageSetingCalorifier; 		/*	指向为热水器设置界面	*/
//	LCDPageSelectElec->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectElec->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectElec->lcdPagePrePage  	 = (struct lcd_page_t*)0; 			/*	指向为空	*/
//
//	LCDPageSetingDoorLight->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	指向为家电选择界面	*/
//	LCDPageSetingBedroomLight->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	指向为家电选择界面	*/
//	LCDPageSetingAircondition->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	指向为家电选择界面	*/
//	LCDPageSetingCalorifier->lcdPagePrePage  	 = LCDPageSelectElec; 		/*	指向为家电选择界面	*/
//
//
///*	创建LCD模式选择页面	*/
//	//LCD_PAGE		*LCDPageSelectModel;				/*	指向LCD模式选择界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSelectModel  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSelectModel->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectModel->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectModel->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectModel->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectModel->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectModel->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectModel->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSelectModel->uiLcdPageID	= LCD_PAGE_SELECT_MODEL;
//	LCDPageSelectModel->uiSubPageNum	= 4;
//	LCDPageSelectModel->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectModel->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectModel->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectModel->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectModel->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectModel->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectModel->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
///*	创建LCD系统开关机选择页面	*/
//	//LCD_PAGE		*LCDPageSelectSys;				/*	指向LCD系统开关机选择界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSelectSys  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSelectSys->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSys->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSys->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSys->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSys->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSys->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSys->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSelectSys->uiLcdPageID	= LCD_PAGE_SELECT_SYS;
//	LCDPageSelectSys->uiSubPageNum	= 3;
//	LCDPageSelectSys->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSys->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSys->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSys->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSys->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSys->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSys->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
///*	创建LCD时间设置页面	*/
//	//LCD_PAGE		*LCDPageSetingTime;				/*	指向LCD时间设置界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSetingTime  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSetingTime->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingTime->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingTime->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingTime->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingTime->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingTime->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSetingTime->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSetingTime->uiLcdPageID	= LCD_PAGE_SETING_TIME;
//	LCDPageSetingTime->uiSubPageNum	= 5;
//	LCDPageSetingTime->lcdPageNextPage[0]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingTime->lcdPageNextPage[1]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingTime->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingTime->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingTime->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingTime->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSetingTime->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
///************************第二层*************************************************************/
///*	创建LCD设置选择页面	*/
//	//LCD_PAGE		*LCDPageSelectSeting;				/*	指向LCD设置选择界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageSelectSeting  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageSelectSeting->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSeting->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSeting->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSeting->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSeting->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSeting->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageSelectSeting->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageSelectSeting->uiLcdPageID	= LCD_PAGE_SELECT_SETING;
//	LCDPageSelectSeting->uiSubPageNum	= 4;
//	LCDPageSelectSeting->lcdPageNextPage[0]  = LCDPageSelectModel; 		/*	指向为模式选择界面	*/
//	LCDPageSelectSeting->lcdPageNextPage[1]  = LCDPageSetingTime; 		/*	指向为时间设置界面	*/
//	LCDPageSelectSeting->lcdPageNextPage[2]  = LCDPageSelectElec; 		/*	指向为电器选择界面	*/
//	LCDPageSelectSeting->lcdPageNextPage[3]  = LCDPageSelectSys; 		/*	指向为系统开关机选择界面	*/
//	LCDPageSelectSeting->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSeting->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageSelectSeting->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
//	LCDPageSelectModel->lcdPagePrePage  	 = LCDPageSelectSeting; 		/*	指向为LCD设置选择页面	*/; 		/*	指向为模式选择界面	*/
//	LCDPageSetingTime->lcdPagePrePage  	   	 = LCDPageSelectSeting; 		/*	指向为LCD设置选择页面	*/;
//	LCDPageSelectElec->lcdPagePrePage  	 	 = LCDPageSelectSeting; 		/*	指向为LCD设置选择页面	*/;
//	LCDPageSelectSys->lcdPagePrePage  	 	 = LCDPageSelectSeting; 		/*	指向为LCD设置选择页面	*/;
//
///************************第一层*************************************************************/
///*	创建LCD主界面	*/
//	//LCD_PAGE		*LCDPageMain;				/*	指向LCD主界面的指针	*/
//	/*	分配空间	*/
//   	LCDPageMain  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD当前界面的指针	*/
//	LCDPageMain->lcdPageNextPage[0]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageMain->lcdPageNextPage[1]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageMain->lcdPageNextPage[2]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageMain->lcdPageNextPage[3]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageMain->lcdPageNextPage[4]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageMain->lcdPageNextPage[5]  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); /*	指向LCD下一级界面的指针	*/
//	LCDPageMain->lcdPagePrePage  = (struct lcd_page_t*)malloc(sizeof(struct lcd_page_t)); 	 /*	指向LCD上一级界面的指针	*/
//	/*	填入值	*/
//	LCDPageMain->uiLcdPageID	= LCD_PAGE_MAIN;
//	LCDPageMain->uiSubPageNum	= 2;
//	LCDPageMain->lcdPageNextPage[0]  = LCDPageSelectSeting; 		/*	指向为LCD设置选择页面	*/
//	LCDPageMain->lcdPageNextPage[1]  = LCDPageSelectElec; 			/*	指向为家电选择界面	*/
//	LCDPageMain->lcdPageNextPage[2]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageMain->lcdPageNextPage[3]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageMain->lcdPageNextPage[4]  = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageMain->lcdPageNextPage[5]	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//	LCDPageMain->lcdPagePrePage  	 = (struct lcd_page_t*)0; 		/*	指向为空	*/
//
//	LCDPageSelectSeting->lcdPagePrePage  	 = LCDPageMain; 		/*	指向为主界面	*/
//	//LCDPageSelectElec->lcdPagePrePage  	 = LCDPageMain; 		/*	指向为主界面	*/
//
///*	LCD界面树的头指针指向界面树主界面	*/
//   LCDPageTree = LCDPageMain;
//
//}

/******************************************************************************
*						函数命名：	TASK_RTCInit	
*                       参数说明：  无		
*											
*						返回类型：	void 	
*						功能说明：	TASK模块时钟初始化函数，
*									
******************************************************************************/
void TASK_RTCInit (void)
{
	PREINT = Fpclk / 32768 - 1;					// 设置基准时钟分频器
	PREFRAC = Fpclk - (Fpclk / 32768) * 32768;
	
	CCR   = 0x00;								// 禁止时间计数器
	
	YEAR  = 2013;
	MONTH = 8;
	DOM   = 9;
	DOW   = 5;
	HOUR  = 8;
	MIN   = 30;
	SEC   = 50;
	
	CIIR = 0x01;								// 设置秒值的增量产生1次中断
	CCR  = 0x01;								// 启动RTC
}

/******************************************************************************
*						函数命名：	TASK_GetRTCTimeYear	
*                       参数说明：  无		
*											
*						返回类型：	INT16U 返回年 	
*						功能说明：	TASK模块获取实时时钟	年
*									
******************************************************************************/
INT16U TASK_GetRTCTimeYear (void)
{
	INT32U uiDatas;
	INT32U uiBak;
												 	// 读取完整的时钟寄存器
	uiDatas = CTIME1;
	
	
	
	uiBak = (uiDatas >> 16) & 0xfff;				// 获取年

	return (INT16U)uiBak;
    	
}

/******************************************************************************
*						函数命名：	TASK_GetRTCTimeMonth	
*                       参数说明：  无		
*											
*						返回类型：	INT8U 返回月 	
*						功能说明：	TASK模块获取实时时钟	月
*									
******************************************************************************/
INT8U TASK_GetRTCTimeMonth (void)
{
	INT32U uiDatas;
	INT32U uiBak;
													// 读取完整的时钟寄存器
	uiDatas = CTIME1;
	    	
	uiBak = (uiDatas >> 8) & 0x0f;					// 获取月

	return (INT8U)uiBak;
    
}

/******************************************************************************
*						函数命名：	TASK_GetRTCTimeDay	
*                       参数说明：  无		
*											
*						返回类型：	INT8U 返回日 	
*						功能说明：	TASK模块获取实时时钟	日
*									
******************************************************************************/
INT8U TASK_GetRTCTimeDay (void)
{
	INT32U uiDatas;
	INT32U uiBak;
														// 读取完整的时钟寄存器
	uiDatas = CTIME1;
	    
	uiBak = uiDatas & 0x1f;							// 获取日

	return (INT8U)uiBak;    
}


/******************************************************************************
*						函数命名：	TASK_GetRTCTimeWeek	
*                       参数说明：  无		
*											
*						返回类型：	INT8U 返回星期 	
*						功能说明：	TASK模块获取实时时钟	星期
*									
******************************************************************************/
INT8U TASK_GetRTCTimeWeek (void)
{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// 读取完整的时钟寄存器
	    
	uiBak = (uiTimes >> 24) & 0x07;					// 获取星期
	
	return (INT8U)uiBak;	
}

/******************************************************************************
*						函数命名：	TASK_GetRTCTimeHour	
*                       参数说明：  无		
*											
*						返回类型：	INT8U 返回小时 	
*						功能说明：	TASK模块获取实时时钟	时
*									
******************************************************************************/
INT8U TASK_GetRTCTimeHour (void)
{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// 读取完整的时钟寄存器
		
	uiBak = (uiTimes >> 16) & 0x1f;					// 获取小时
    
	return (INT8U)uiBak;
}

/******************************************************************************
*						函数命名：	TASK_GetRTCTimeMin	
*                       参数说明：  无		
*											
*						返回类型：	INT8U 返回分钟 	
*						功能说明：	TASK模块获取实时时钟	分
*									
******************************************************************************/
INT8U TASK_GetRTCTimeMin (void)
{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// 读取完整的时钟寄存器
	    
	uiBak = (uiTimes >> 8) & 0x3f;					// 获取分钟
    
	return (INT8U)uiBak;
}

/******************************************************************************
*						函数命名：	TASK_GetRTCTimeSec	
*                       参数说明：  无		
*											
*						返回类型：	INT8U 返回秒 	
*						功能说明：	TASK模块获取实时时钟	秒
*									
******************************************************************************/
INT8U TASK_GetRTCTimeSec (void)

{
	INT32U uiTimes;
	INT32U uiBak;
	
	uiTimes = CTIME0;								// 读取完整的时钟寄存器
	    
	uiBak = uiTimes & 0x3f;							// 获取秒钟

	return (INT8U)uiBak;
}


/******************************************************************************
*						函数命名：	INT8U TASK_CharToNum(INT8U c)	
*                       参数说明：  无		
*											
*						返回类型：	INT8U 返回秒 	
*						功能说明：	TASK模块获取实时时钟	秒
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
*						函数命名：	void TASK_SendStatTbl(void)	
*                       参数说明：  无		
*											
*						返回类型：	无 	
*						功能说明：	发送状态信息表的内容给上位机
*									
******************************************************************************/
void TASK_SendStatTbl(void)
{
	INT8U cInstruction[9][14];    //保存翻译数据结果的数组
	INT8U  i;					  //循环计数变量
	
	//门灯开关
	cInstruction[0][0]='d';	  
	if(OSStateInfo[0].uiOSStateContent)	cInstruction[0][1]='1';
	else cInstruction[0][1]='0';
	for(i=2;i<13;i++) cInstruction[0][i]='0'; 
	//卧室灯开关
	cInstruction[1][0]='f';
	if(OSStateInfo[1].uiOSStateContent)	cInstruction[1][1]='1';
	else cInstruction[1][1]='0';
	for(i=2;i<13;i++) cInstruction[1][i]='0'; 
	//空调开关
	cInstruction[2][0]='h';
	if(OSStateInfo[2].uiOSStateContent)	cInstruction[2][1]='1';
	else cInstruction[2][1]='0';
	for(i=2;i<13;i++) cInstruction[2][i]='0'; 
	//热水器开关
	cInstruction[3][0]='k';
	if(OSStateInfo[3].uiOSStateContent)	cInstruction[3][1]='1';
	else cInstruction[3][1]='0';
	for(i=2;i<13;i++) cInstruction[3][i]='0'; 
	//空调温度
	cInstruction[4][0]='i';
	cInstruction[4][1]=TASK_CharToNum(OSStateInfo[4].uiOSStateContent/10);
	cInstruction[4][2]=TASK_CharToNum(OSStateInfo[4].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[4][i]='0';
	//热水器温度
	cInstruction[5][0]='l';
	cInstruction[5][1]=TASK_CharToNum(OSStateInfo[5].uiOSStateContent/10);
	cInstruction[5][2]=TASK_CharToNum(OSStateInfo[5].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[5][i]='0';
	//系统模式
	cInstruction[6][0]='n';
	cInstruction[6][1] = TASK_CharToNum(OSStateInfo[6].uiOSStateContent);
	for(i=2;i<13;i++) cInstruction[6][i]='0';		
	//光强
	cInstruction[7][0]='p';
	cInstruction[7][1]=TASK_CharToNum(OSStateInfo[7].uiOSStateContent/10);
	cInstruction[7][2]=TASK_CharToNum(OSStateInfo[7].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[7][i]='0';
	//室温
	cInstruction[8][0]='q';
	cInstruction[8][1]=TASK_CharToNum(OSStateInfo[8].uiOSStateContent/10);
	cInstruction[8][2]=TASK_CharToNum(OSStateInfo[8].uiOSStateContent%10);
	for(i=3;i<13;i++) cInstruction[8][i]='0';
	for(i=0;i<9;i++) cInstruction[i][13]='\0';
	//发送数据
	for(i=0;i<9;i++)
	{	
		COM_SendDataDown(cInstruction[i]);
		DelayNS(15);


	}

}

/******************************************************************************
*						函数命名：	void TASK_SendTimingTbl(void)	
*                       参数说明：  无		
*											
*						返回类型：	无 	
*						功能说明：	发送定时任务表的内容给上位机
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
		//使能
		for(j=6;j<13;j++) cInstruction[i][j] = '0';
		cInstruction[i][13]='\0';
			
	}
	COM_SendDataDown(cInstruction[0]);
	COM_SendDataDown(cInstruction[1]);
	COM_SendDataDown(cInstruction[2]);
	COM_SendDataDown(cInstruction[3]);
		
}

/*****************************************************************************
*名称: DelayNS()
*功能: 软件延时
*****************************************************************************/

void  DelayNS(INT32U nDly)
{  
    INT32U nLoop;

    for(; nDly>0; nDly--) 
        for(nLoop=0; nLoop<50000; nLoop++);
}

/****************************************************************************
* 函数名称：BeepCount()
* 功    能：蜂鸣器按指定次数缝鸣
****************************************************************************/

void BeepCount(INT8U count)
{
 	for(;count>0;count--)
    {
    	IOSET|=BEEP;                   		      //开蜂鸣器 
		DelayNS(10);
       	IOCLR|=BEEP;                   			  //关闭蜂鸣器
		DelayNS(10);
    }
}

/******************************************************************************
*                            End Of File
******************************************************************************/
