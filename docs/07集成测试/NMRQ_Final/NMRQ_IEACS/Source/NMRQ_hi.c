/*****************************************************************************************************
*              文件名：	NMRQ_hi.c
*              描述：	HI模块的代码，负责衔接TASK和硬件，接收TASK的指令并传给硬件
*                    	同时接收硬件模块传来的反馈信息并传递给TASK模块 
*              作者：	杨林龙
*              创建日期：2013-7-26
*              修改日期1:2013-7-29 删除了HI_SendMsgToTask()，增加了HI_SwapTempAndLight()，HI_PageSwitch(), HI_ErrorDisplay函数
*******************************************************************************************************/
#include"..\Include\NMRQ_hi.h"


extern OS_STATE_INFO	OSStateInfo[OS_STATE_INFO_SIZE];
/******************************************************************************************************
*            函数名：HI_Control(info_Type,ctrl_Obj,content)
*            返回类型：INT8U 表示成功或者错误类型的宏定义    
*            参数类型：1、INT8U     表示要执行的动作的类型（比如开关家电还是设置温度、连接状态等）
*                      2、INT8U   	表示要对哪个对象执行动作（比如门灯、空调还是热水器等）
*                      3、INT8U  	表示执行动作需要的数据等 
*             功能：  通过TASK传来的四个参数判断是哪个底层函数需要被调用，调用之，并返回反馈信息
*********************************************************************************************************/

INT8U HI_Control(INT8U info_Type,INT8U ctrl_Obj,INT8U content)
{
   	   INT8U   HI_tempNumber;
	   switch(info_Type)								//判断信息类型
	   {
	   	 case OS_STATE_INFO_TYPE_INT:				    //若信息类型为中断类型，则判断对象     
		 {
		   if(ctrl_Obj==OS_STATE_CTRL_OBJ_THIEF)		//对象是小偷中断
		     HI_tempNumber = EAC_THF;
			 else if(ctrl_Obj==OS_STATE_CTRL_OBJ_GASLEAK) //对象是煤气泄漏中断
			    HI_tempNumber = EAC_GAL;
				break;
		 }
		 case OS_STATE_INFO_TYPE_SWITCH:				  //若信息类型为开关类型，则判断对象
		   {
		   	  switch(ctrl_Obj)
			  {
			     case OS_STATE_CTRL_OBJ_DOOR_LIGHT:		   //对象是门灯，则判断是开灯动作还是关灯动作
				 { if(content==OS_ELEC_SWITCH_STATE_ON)
				   HI_tempNumber = EAC_ODL;
				   else if(content==OS_ELEC_SWITCH_STATE_OFF)
				   HI_tempNumber = EAC_CDL;
				   break;
				  }
				  case OS_STATE_CTRL_OBJ_BEDROOM_LIGHT:		//对象是卧室灯，则直接返回SUCCESS
				   if(content==OS_ELEC_SWITCH_STATE_ON)
					OSStateInfo[1].uiOSStateContent= OS_ELEC_SWITCH_STATE_ON;
					else OSStateInfo[1].uiOSStateContent= OS_ELEC_SWITCH_STATE_OFF;
				   return SUCCESS;
				  case OS_STATE_CTRL_OBJ_AIRCONDITION :		//对象是空调，则判断是开空调还是关空调
				  {
				  	 if(content==OS_ELEC_SWITCH_STATE_ON)
					  HI_tempNumber = EAC_OAC;
					  else if(content==OS_ELEC_SWITCH_STATE_OFF)
					  HI_tempNumber = EAC_CAC;
					  break;
				  }
				  case OS_STATE_CTRL_OBJ_CALORIFIER:		 //对象是热水器，则判断是开热水器还是关热水器
				  {
				  	if(content==OS_ELEC_SWITCH_STATE_ON)
					  HI_tempNumber = EAC_OWH;
					  else if(content==OS_ELEC_SWITCH_STATE_OFF)
					  HI_tempNumber = EAC_CWH;
					  break;
				  }
				  default : break;
			  }
			  break;
		   }
		   case OS_STATE_INFO_TYPE_TEMP:					  //若信息类型是温度类型
		   {												    //则判断对象是设置空调温度还是设置热水器温度
		   	  if(ctrl_Obj==OS_STATE_CTRL_OBJ_AIRCONDITION)	 //对象是空调，调用设置空调温度函数 
			  return EAC_SendFeedbackMsg2(EAC_SAT,content);
			  else if(ctrl_Obj==OS_STATE_CTRL_OBJ_CALORIFIER)	  //对象是热水器，调用设置热水器温度函数
			  return EAC_SendFeedbackMsg2(EAC_SWT,content);
		   }
		   default:break;
	   }
		return EAC_SendFeedbackMsg(HI_tempNumber);            //调用相应函数，获取返回值
}

/**********************************************************************************************************
*        函数名：HI_SendMsgToTask(functionNumber，EAC_temperature)
*        返回类型：INT16U  表示成功或者错误类型的宏定义
*         参数类型：1、INT16U  表示需要被执行的EAC或者LCD函数的编号的宏定义
*                   2、INT16U  表示部分需要被执行的函数需要的温度参数
*        功能：   调用底层的EAC控制函数或者LCD控制函数，并返回函数执行的错误或成功信息
************************************************************************************************************/
	 //该函数已取消

/*
INT16U HI_SendMsgToTask(functionNumber,EAC_temperature)
{
	//判断functionNumber是属于EAC函数还是LCD函数
	//如果属于EAC函数
	return EAC_SendFeedbackMsg(functionNumber,EAC_temperature);
    //如果属于LCD函数
	return LCD_SendFeedbackMsg(functionNumber);
} 
*/

  
/*************************************************************************************************************
*                     函数名：HI_SwapTempAndLight()
*                     返回类型：INT8U  表示错误类型的宏定义
*                     参数类型：无
*                     功能：    调用切换感温感光的函数，获取返回值并返回
**************************************************************************************************************/

INT8U HI_SwapTempAndLight()
{
   return EAC_SendFeedbackMsg(EAC_STL);
}

/*************************************************************************************************************
*                     函数名：HI_PageSwitch(pageID,focus)
*                     返回类型：void
*                     参数类型：1、INT8U 表示LCD页面编号
*                               2、INT8U 表示指向页面焦点
*                     功能：    调用LCD中切换界面和焦点的函数
**************************************************************************************************************/

void HI_PageSwitch(INT8U PageID,INT8U focus)
{
	  return;
}

/*************************************************************************************************************
*                     函数名：HI_ErrorDisplay(errorType)
*                     返回类型：void
*                     参数类型：1、INT8U 表示错误类型的宏定义
*                     功能：    调用LCD中显示错误的函数
**************************************************************************************************************/

void HI_ErrorDisplay(INT8U errorType)
{

}



/*************************************************************************************************************
*                     函数名：HI_IfKeyClicked()
*                     返回类型：BOLEAN  表示是否有按键被按下的宏定义
*                     参数类型： 无参数
*                     功能：    从KEY模块得到是否有键被按下的信息
**************************************************************************************************************/

BOOLEAN HI_IfKeyClicked()
{
  return KEY_IfClicked();
}


/*************************************************************************************************************
*                     函数名：HI_GetKeyValue_whichKey()
*                     返回类型：INT8U  表示哪个按键被按下的宏定义
*                     参数类型： 无参数
*                     功能：    从KEY模块得到键值1（哪个键被按下）
**************************************************************************************************************/

INT8U HI_GetKeyValue_whichKey()
{
	return KEY_SendKeyValue_whichKey();
}

/*************************************************************************************************************
*                     函数名：HI_GetKeyValue_LongOrShort()
*                     返回类型：BOOLEAN  表示长按还是短按的宏定义
*                     参数类型： 无参数
*                     功能：    从KEY模块得到键值2（长按还是短按）
**************************************************************************************************************/

BOOLEAN HI_GetKeyValue_LongOrShort()
{
   return KEY_SendKeyValue_LongOrShort();
}


 /***********************************************************************************
 *
 *								END OF FILE
 *
 *************************************************************************************/

