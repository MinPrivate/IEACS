/****************************************************************************
*                         文件名： 	NMRQ_eac.c
*                         文件描述：eac模块的函数，负责下位机的硬件控制
*                         作者：	杨林龙
*                         创建日期：2013-7-26
******************************************************************************/


#include	"..\Include\NMRQ_eac.h"
#include	<LPC2103.h>



INT8U EAC_ADState = EAC_AD_STATE_TEMP; //AD转换器状态，默认是感温状态
/***********************************************************************************************
*                  函数名： EAC_OpenDoorLight()
*                  返回类型： INT8U 成功或者错误信息的宏定义
*                  参数类型： 无参数
*                  功能：   打开门灯    
***********************************************************************************************/

INT8U EAC_OpenDoorLight()
{	 //	if中读取当前电灯状态，若已经打开，则直接返回
     if(OSStateInfo[0].uiOSStateContent ==OS_ELEC_SWITCH_STATE_ON)
	 	{
		 return SUCCESS;
		 }
	 else 
	 	{
		   PINSEL0 &= 0xff3fffff;         //p0.11引脚设为GPIO功能
		   IODIR  |= 0x00000800;         //p0.11设置为输出
	 	   IOCLR  |= 0x00000800;         //p0.11输出低电平，打开LED1
	    return SUCCESS;
	 	} 
}

/***********************************************************************************************
*                    函数名： EAC_CloseDoorLight()
*                    返回类型： INT8U 成功或者错误信息的宏定义
*                    参数类型： 无参数
*                    功能：   关闭门灯    
***********************************************************************************************/

INT8U EAC_CloseDoorLight()
{  //if中读取当前电灯状态，若已经关闭，则直接返回
   	if(OSStateInfo[0].uiOSStateContent==OS_ELEC_SWITCH_STATE_OFF)
		 {
	    return SUCCESS;
		}
	else 
		{
		   PINSEL0 &= 0xff3fffff;         //p0.11引脚设为GPIO功能
		   IODIR  |= 0x00000800;         //p0.11设置为输出
		   IOSET  |= 0x00000800;		   //p0.11输出高电平，关闭LED1
	   return SUCCESS;
		}
}

/***********************************************************************************************
*                    函数名： EAC_OpenAirCondition()
*                    返回类型：INT8U 成功或者错误信息的宏定义
*                    参数类型： 无参数
*                    功能：   开启空调    
***********************************************************************************************/

INT8U EAC_OpenAirCondition()
{  //if中读取当前空调状态，若已经打开，则直接返回
    if(OSStateInfo[2].uiOSStateContent==OS_ELEC_SWITCH_STATE_ON)
	{	
		return SUCCESS;
	}
	else
	{
	 	 PINSEL0 &= 0xfcffffff;            //p0.12引脚设为GPIO功能
		  IODIR  |= 0x00001000;            //p0.12设置为输出口
		  IOCLR  |= 0x00001000;            //p0.12输出低电平，打开LED2
		return SUCCESS;
	}
}

/***********************************************************************************************
*                      函数名： EAC_CloseAirCondition()
*                      返回类型：INT8U 成功或者错误信息的宏定义
*                      参数类型： 无参数
*                      功能：   关闭空调
***********************************************************************************************/

INT8U EAC_CloseAirCondition()
{	//if中读取当前空调状态，若已经关闭，则直接返回
	if(OSStateInfo[2].uiOSStateContent==OS_ELEC_SWITCH_STATE_OFF)
    	{	
		return SUCCESS;
		}
	else
		{
	  	PINSEL0 &= 0xfcffffff;            //p0.12引脚设为GPIO功能
	  	IODIR  |= 0x00001000;            //p0.12设置为输出口
	  	IOSET  |= 0x00001000;            //p0.12输出高电平，关闭LED2
		return SUCCESS;
		}    
}

/***********************************************************************************************
*                      函数名： EAC_SetAirCond_Temp(aTemp)
*                      返回类型： INT8U 成功或者错误信息的宏定义
*                      参数说明：  INT8U类型，表示温度 
*                      功能：   设置空调温度
***********************************************************************************************/

INT8U EAC_SetAirCond_Temp(INT8U aTemp)
{	//if中读取空调温度，若等于aTemp，则直接返回
      if(OSStateInfo[4].uiOSStateContent==aTemp)
	  	{
	 	 return SUCCESS;
	 	 }
	  else
	 	 {
	      //将温度设为aTemp
	  	 OSStateInfo[4].uiOSStateContent=aTemp;
		return SUCCESS;
	 	 }
}

/***********************************************************************************************
*                      函数名： EAC_OpenWaterheater()
*                      返回类型： INT8U 成功或者错误信息的宏定义
*                      参数类型： 无参数
*                      功能：   开启热水器
***********************************************************************************************/

INT8U EAC_OpenWaterheater()
{  //if中读取当前热水器状态，若已经打开，则直接返回
	 if(OSStateInfo[3].uiOSStateContent==OS_ELEC_SWITCH_STATE_ON)
		 {
		 return SUCCESS;
	 	}
	 else
		 {
	 	  PINSEL0 &= 0xf3ffffff;        //p0.13引脚设为GPIO功能
	 	  IODIR  |= 0x00002000;        //p0.13设置为输出口
	 	  IOCLR  |= 0x00002000;        //p0.13输出低电平，开启LED3
	 	  return SUCCESS;
		 }
}

/***********************************************************************************************
*                     函数名： EAC_CloseWaterheater()
*                     返回类型： INT8U 成功或者错误信息的宏定义
*                     参数类型： 无参数
*                     功能：   关闭热水器
***********************************************************************************************/

INT8U EAC_CloseWaterheater()
{	//	if中读取当前热水器状态，若已经关闭，则直接返回
	 if(OSStateInfo[3].uiOSStateContent==OS_ELEC_SWITCH_STATE_OFF )
		{
		 return SUCCESS;
		 }
	 else
		 {
		  PINSEL0 &= 0xf3ffffff;        //p0.13引脚设为GPIO功能
		  IODIR  |= 0x00002000;        //p0.13设置为输出口
	   	  IOSET  |= 0x00002000;        //p0.13输出高电平，关闭LED3
	 	  return SUCCESS;
		 }
}

/***********************************************************************************************
*                    函数名： EAC_SetWaterheater_Temp(wTemp)
*                    返回类型：INT8U 成功或者错误信息的宏定义
*                    参数类型：INT8U 表示温度 
*                    功能：   设置热水器温度
***********************************************************************************************/

INT8U EAC_SetWaterheater_Temp(INT8U wTemp)
{	//if中读取当前热水器温度，若等于wTemp，则直接返回
    if(OSStateInfo[5].uiOSStateContent==wTemp)
		{
		return SUCCESS;
		}
	else 
		{
	  //将温度设置为wTemp
	 	 OSStateInfo[5].uiOSStateContent=wTemp;
		  return SUCCESS;
		}
}
/****************************************************************************
*                 函数名: EAC_DelayNS(nDly);   
*                 返回类型：void
*                 参数类型：INT16U,表示要延时的时间ms
*                 功能：软件延时
******************************************************************************/
void EAC_DelayNS(INT16U nDly)
{ 
	 int nLoop;
	 for(;nDly>0;nDly--)
	 {
	   for(nLoop=0;nLoop<5000;nLoop++) ;
	 }
}


/******************************************************************
*			      函数名： EAC_Bell(count)
*			      返回类型：void
*                 参数类型： INT16U 表示报警灯闪烁次数
*				  功能：使报警灯闪烁
***********************************************************************/
 /*
void EAC_Bell(INT16U count)
{ 
    PINSEL0 &= 0xcfffffff;         //p0.14引脚设置为GPIO功能
	IODIR  |= 0x00004000;         //p0.14设置为输出口
	IOCLR  |= 0x00004000;          //开始时先不闪烁
	for(;count>0;count--)
	{
	  IOSET |= 0x00004000;			//开始闪烁
	  EAC_DelayNS(5);
	  IOCLR |= 0x00004000;
	  EAC_DelayNS(5);
	}

}
  */

/***************************************************************************************
*		     函数名 EAC_BeepAndBell(count)
*			 返回类型：void
*            参数类型:INT16U	 表示要蜂鸣器响的次数和LED4闪烁的次数
*			 功能：让蜂鸣器鸣响一定的次数并让LED4闪烁一定的次数
***************************************************************************************/

void EAC_BeepAndBell(INT16U count)         //蜂鸣器鸣响，参数为次数
{	 
   	 PINSEL0 &= 0xffcfffff;            //将p0.10设置为GPIO口
  	  IODIR |=0x000000400 ;				  //设置Beep口为输出口
  	  IOCLR |=0x000000400 ;				  //开始不鸣响

		PINSEL0 &= 0xcfffffff;         //p0.14引脚设置为GPIO功能
		IODIR  |= 0x00004000;         //p0.14设置为输出口
		IOCLR  |= 0x00004000;          //开始时先不闪烁
   for(;count>0;count--)
  	  {
		 IOSET |=0x000000400 ;			    //响
		 IOCLR |= 0x00004000;			    //开始亮
		 EAC_DelayNS(80);
		 IOCLR |=0x000000400;
		 IOSET |= 0x00004000;
		 EAC_DelayNS(80);
   	 }
}
/***********************************************************************************************
*                     函数名： EAC_GetTemperatureInfo()
*                     返回类型： void
*                     参数类型： 无参数
*                     功能：   获取温度信息
**********************************************************************************************/

void EAC_GetTemperatureInfo()
{
       INT8U tempMsg;
   	  INT32U ADDRData;
  	  PINSEL0 = (PINSEL0 & 0xffcfffff)|0x00300000;     //将p0.10端口设置为AIN3
		ADCR = 0x00200408;                              //设置AD，10-bits,3MHz
		ADCR |= 0x01000000;                               //开启AD转换器
		do{
		  ADDRData = ADDR3;
		}while((ADDRData&0x80000000)==0);					 //等待转换完成
		ADCR &= ~0x01000000;                            //关闭AD转换器
		ADDRData =(ADDRData>>6)&0x03ff;                 //读出数据

		 ADDRData /=10;                         //此时0=<ADDRData<=1023,对其进行操作使其符合正常温度信息
		 if(ADDRData>40)
		 {
		    ADDRData /=2;			          //此时ADDRData介于0~40之间
		 }
	
		OSStateInfo[7].uiOSStateContent = ADDRData;     //将所得数据赋给系统状态表的温度信息
		if(ADDRData <12)								 //温度太低，则打开空调，设置高温
		{
		   tempMsg = EAC_OpenAirCondition();
		   EAC_SetAirCond_Temp(ADDRData+15);
	 	  if(tempMsg==SUCCESS)
	 	  {
		   OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;			 //修改状态表
	 	  }
		}
		 if(ADDRData>30)							  //温度太高，则打开空调，设置低温
		 {
	 		tempMsg = EAC_CloseAirCondition();
			 EAC_SetAirCond_Temp(ADDRData-10);
     	    if(tempMsg==SUCCESS) 			                 //修改状态表
	 	   {
	  	   OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
	  	   }
		 }

}

/***********************************************************************************************
*                     函数名： EAC_GetLightInfo()
*                     返回类型：void
*                     参数类型： 无参数
*                     功能：   获取亮度信息
***********************************************************************************************/

void EAC_GetLightInfo()
{	 
    	INT16U tempMsg;
		INT32U ADDRData;
   	 PINSEL0 = (PINSEL0 & 0xffcfffff)|0x00300000;     //将p0.10端口设置为AIN3
		ADCR = 0x00200408;                              //设置AD，10-bits,3MHz
		ADCR |= 0x01000000;                               //开启AD转换器
		do{
		  ADDRData = ADDR3;
		}while((ADDRData&0x80000000)==0);					 //等待转换完成
		ADCR &= ~0x01000000;                            //关闭AD转换器
		ADDRData =(ADDRData>>6)&0x03ff;                 //读出数据
		//此时ADDRData介于0~1023之间

		ADDRData /=10;          //缩小10倍后，介于0~102之间
   	   OSStateInfo[8].uiOSStateContent = ADDRData;     //将所得数据赋给系统状态表的光强信息
		if(ADDRData <40)								 //亮度太低，则打开门灯
		{
		   tempMsg = EAC_OpenDoorLight();
	 	  if(tempMsg==SUCCESS)
	 	  {
		   OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;			 //修改状态表
	 	  }
		}
		 if(ADDRData>70)							  //亮度太高，则关闭门灯
		 {
	 		tempMsg = EAC_CloseDoorLight();
     	    if(tempMsg==SUCCESS) 			                 //修改状态表
	 	   {
	  	   OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
	  	  }
		 }
}


/***********************************************************************************************
*                     函数名： EAC_SwapTempAndLight()
*                     返回类型： INT16U 成功或者错误信息的宏定义
*                     参数类型： 无参数
*                     功能：   切换感温和感光功能
***********************************************************************************************/

INT8U EAC_SwapTempAndLight()
{
		 if(EAC_ADState == EAC_AD_STATE_TEMP)  //若此时是感温状态，则切换成感光状态
		  {
	 	  EAC_GetLightInfo();
	 	  EAC_ADState = EAC_AD_STATE_LIGHT;
	 	  }
	 	  else 							   //否则切换成感温状态
	 	  {
	  	 	 EAC_GetTemperatureInfo();
			 EAC_ADState = EAC_AD_STATE_TEMP;
	  	 }
		return SUCCESS;
}

/***********************************************************************************************
*                     函数名： EAC_ThiefFound()
*                     返回类型： INT16U 成功或者错误信息的宏定义
*                     参数类型： 无参数
*                     功能：   检测到小偷后执行的函数（中断处理函数）
***********************************************************************************************/

INT8U EAC_ThiefFound()
{
    
		EAC_BeepAndBell(100);				 //蜂鸣器鸣响 报警灯闪烁
		//EAC_Bell(1);				        	 
   		 return SUCCESS;
}

/***********************************************************************************************
*                     函数名： EAC_GasLeak()
*                     返回类型： INT16U 成功或者错误信息的宏定义
*                     参数类型： 无参数
*                     功能：   检测到煤气泄漏后执行的函数（中断处理函数）
***********************************************************************************************/

INT8U EAC_GasLeak()
{	//关闭所有电器，并报警三分钟
   		 INT8U tempMsg;
		tempMsg = EAC_CloseDoorLight();
    	//if(tempMsg==SUCCESS) 			                 //关闭门灯，修改状态表
		  //{
		  OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
		   OSStateInfo[1].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
		 // }
		 tempMsg = EAC_CloseAirCondition();
		//if(tempMsg==SUCCESS)						 //关闭空调，修改状态表
		//{
		   OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
		//}
		tempMsg = EAC_CloseWaterheater(); 
		//if(tempMsg==SUCCESS)							 //关闭热水器，修改状态表
		//{
		   OSStateInfo[3].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF; 
		//}

   		 EAC_BeepAndBell(100);							 //蜂鸣器鸣响 报警灯闪烁
		return SUCCESS;
}
  

/***********************************************************************************************
*                   函数名： EAC_GetFeedbackMsg(EAC_functionNumber)
*                   返回类型： INT8U 成功或者错误信息的宏定义
*                   参数类型： INT8U 表示具体的某个函数的编号
*                   功能：   获取某一个函数执行后的成功或者错误信息
***********************************************************************************************/

INT8U EAC_GetFeedbackMsg(INT8U EAC_functionNumber)
{   	INT8U tempErrorMsg;
 	switch(EAC_functionNumber){//根据EAC_functionNumber判断执行哪个函数并获取反馈内容
 	 case EAC_ODL:
		tempErrorMsg = EAC_OpenDoorLight();		  //根据参数判断得出该执行开灯函数
		if(tempErrorMsg != SUCCESS){
       tempErrorMsg = EAC_OPENLIGHT_ERROR;	  //函数执行不成功，返回错误类型
		  }
		  else 
		OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;    //函数执行成功，则修改状态表
		break;
 	 case EAC_CDL:
		tempErrorMsg = EAC_CloseDoorLight();	   //根据参数判断得出该执行关灯函数
		if(tempErrorMsg != SUCCESS){				   //函数执行不成功，返回错误类型
			tempErrorMsg = EAC_CLOSELIGHT_ERROR;
     		}
			else 
		OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;//函数执行成功，修改状态表
		break;
 	 case EAC_OAC:
		tempErrorMsg = EAC_OpenAirCondition();	   //根据参数判断得出该执行开空调函数
		if(tempErrorMsg != SUCCESS){					 //函数执行不成功，返回错误类型
			tempErrorMsg = EAC_OPENAIRCOND_ERROR;  
		    }
			else 
		  OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;//函数执行成功，修改状态表
		break;
  	case EAC_CAC:
		tempErrorMsg = EAC_CloseAirCondition();	   //根据参数判断得出该执行关空调函数
   		 if(tempErrorMsg != SUCCESS){				   //函数执行不成功，返回错误类型
			tempErrorMsg = EAC_CLOSEAIRCOND_ERROR;
			}
			else
			 OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF; //函数执行成功，修改状态表
		break;
 	case EAC_OWH:
		tempErrorMsg = EAC_OpenWaterheater();		//根据参数判断得出该执行开热水器函数
		if(tempErrorMsg != SUCCESS){					//函数执行不成功，返回错误类型
			tempErrorMsg = EAC_OPENWATERHEATER_ERROR;
			}
			else 
			OSStateInfo[3].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON; //函数执行成功，修改状态表
			break;
 	 case EAC_CWH:
		tempErrorMsg = EAC_CloseWaterheater();		//根据参数判断得出该执行关热水器函数
		if(tempErrorMsg != SUCCESS){					//函数执行不成功，返回错误类型
			tempErrorMsg = EAC_CLOSEWATERHEATER_ERROR;
			}
			else
			 OSStateInfo[3].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF; //函数执行成功，修改状态表
		break;
 	 case EAC_STL:
		tempErrorMsg = EAC_SwapTempAndLight();		 //根据参数判断得出该执行切换感温感光函数
  	   if(tempErrorMsg != SUCCESS){
			tempErrorMsg = EAC_SWAPTANDL_ERROR;
			}
		 break;
 	/*case GTI:
		tempErrorMsg = EAC_GetTemperatureInfo();
		if(tempErrorMsg != SUCCESS)
			tempErrorMsg = EAC_GETTEMPINFI_ERROR;
		break;
 	case GLI:
		tempErrorMsg = EAC_GETLightInfo();
		if(tempErrorMsg != SUCCESS)
			tempErrorMsg = EAC_GETLIGHTINFO_ERROR;
		break;	*/
 	 case EAC_THF:
		tempErrorMsg = EAC_ThiefFound();		  //根据参数判断得出该执行发现小偷的函数
		if(tempErrorMsg != SUCCESS){
			tempErrorMsg = EAC_THIEFFOUND_ERROR;
			}
		break;
 	 case EAC_GAL:
		tempErrorMsg = EAC_GasLeak();			   //根据参数判断得出该执行煤气泄漏的函数
		if(tempErrorMsg != SUCCESS){
			tempErrorMsg = EAC_GASLEAK_ERROR;
			}
		break;
 	 default:break;
	}
 	 return tempErrorMsg;

}

/***********************************************************************************************
*                函数名： EAC_GetFeedbackMsg2(EAC_functionNumber,EAC_temperature)
*                返回类型： INT8U 成功或者错误信息的宏定义
*                参数类型：1、 INT8U 表示具体的某个函数的编号,
*                          2、INT8U 表示要调用的函数需要的温度参数
*                功能：   获取某一个函数执行后的成功或者错误信息
***********************************************************************************************/

INT8U EAC_GetFeedbackMsg2(INT8U EAC_functionNumber,INT8U EAC_temperature)
{
    	 INT8U tempErrorMsg;
		switch(EAC_functionNumber){
		case EAC_SAT:
			tempErrorMsg = EAC_SetAirCond_Temp(EAC_temperature);	//根据参数判断该执行设置空调温度的函数
      	   if(tempErrorMsg != SUCCESS){
			   tempErrorMsg = EAC_SETAIRCONDTEMP_ERROR;
			   }
			 break;
		case EAC_SWT:
			tempErrorMsg = EAC_SetWaterheater_Temp(EAC_temperature); //根据参数判断该执行设置热水器温度的函数
			if(tempErrorMsg != SUCCESS){
			tempErrorMsg = EAC_SETWATERHEATERTEMP_ERROR;
			}
			break;
		default:break;
	
	}
   return tempErrorMsg;

}

/***********************************************************************************************
*                   函数名： EAC_SendFeedbackMsg(EAC_functionNumber)
*                   返回类型： INT8U 成功或者错误信息的宏定义
*                   参数类型： INT8U 表示具体的某个函数的编号
*                   功能：   将获取到的某一个函数执行后的成功或者错误信息发送给HI模块
***********************************************************************************************/
INT8U EAC_SendFeedbackMsg(INT8U EAC_functionNumber)
{
   	  return EAC_GetFeedbackMsg(EAC_functionNumber);
}

/***********************************************************************************************
*                  函数名： EAC_SendFeedbackMsg2(EAC_functionNumber，EAC_temperature )
*                  返回类型： INT16U 成功或者错误信息的宏定义
*                  参数类型：1、 INT16U 表示具体的某个函数的编号
                             2、 INT16U 表示需要调用的函数的温度信息
*                  功能：   将获取到的某一个函数执行后的成功或者错误信息发送给HI模块
***********************************************************************************************/

INT8U EAC_SendFeedbackMsg2(INT8U EAC_functionNumber,INT8U EAC_temperature )
{
  	  return EAC_GetFeedbackMsg2(EAC_functionNumber,EAC_temperature);
}

 /***********************************************************************************
 *
 *								END OF FILE
 *
 *************************************************************************************/

