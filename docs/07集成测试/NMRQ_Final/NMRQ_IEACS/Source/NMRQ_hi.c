/*****************************************************************************************************
*              �ļ�����	NMRQ_hi.c
*              ������	HIģ��Ĵ��룬�����ν�TASK��Ӳ��������TASK��ָ�����Ӳ��
*                    	ͬʱ����Ӳ��ģ�鴫���ķ�����Ϣ�����ݸ�TASKģ�� 
*              ���ߣ�	������
*              �������ڣ�2013-7-26
*              �޸�����1:2013-7-29 ɾ����HI_SendMsgToTask()��������HI_SwapTempAndLight()��HI_PageSwitch(), HI_ErrorDisplay����
*******************************************************************************************************/
#include"..\Include\NMRQ_hi.h"


extern OS_STATE_INFO	OSStateInfo[OS_STATE_INFO_SIZE];
/******************************************************************************************************
*            ��������HI_Control(info_Type,ctrl_Obj,content)
*            �������ͣ�INT8U ��ʾ�ɹ����ߴ������͵ĺ궨��    
*            �������ͣ�1��INT8U     ��ʾҪִ�еĶ��������ͣ����翪�ؼҵ绹�������¶ȡ�����״̬�ȣ�
*                      2��INT8U   	��ʾҪ���ĸ�����ִ�ж����������ŵơ��յ�������ˮ���ȣ�
*                      3��INT8U  	��ʾִ�ж�����Ҫ�����ݵ� 
*             ���ܣ�  ͨ��TASK�������ĸ������ж����ĸ��ײ㺯����Ҫ�����ã�����֮�������ط�����Ϣ
*********************************************************************************************************/

INT8U HI_Control(INT8U info_Type,INT8U ctrl_Obj,INT8U content)
{
   	   INT8U   HI_tempNumber;
	   switch(info_Type)								//�ж���Ϣ����
	   {
	   	 case OS_STATE_INFO_TYPE_INT:				    //����Ϣ����Ϊ�ж����ͣ����ж϶���     
		 {
		   if(ctrl_Obj==OS_STATE_CTRL_OBJ_THIEF)		//������С͵�ж�
		     HI_tempNumber = EAC_THF;
			 else if(ctrl_Obj==OS_STATE_CTRL_OBJ_GASLEAK) //������ú��й©�ж�
			    HI_tempNumber = EAC_GAL;
				break;
		 }
		 case OS_STATE_INFO_TYPE_SWITCH:				  //����Ϣ����Ϊ�������ͣ����ж϶���
		   {
		   	  switch(ctrl_Obj)
			  {
			     case OS_STATE_CTRL_OBJ_DOOR_LIGHT:		   //�������ŵƣ����ж��ǿ��ƶ������ǹصƶ���
				 { if(content==OS_ELEC_SWITCH_STATE_ON)
				   HI_tempNumber = EAC_ODL;
				   else if(content==OS_ELEC_SWITCH_STATE_OFF)
				   HI_tempNumber = EAC_CDL;
				   break;
				  }
				  case OS_STATE_CTRL_OBJ_BEDROOM_LIGHT:		//���������ҵƣ���ֱ�ӷ���SUCCESS
				   if(content==OS_ELEC_SWITCH_STATE_ON)
					OSStateInfo[1].uiOSStateContent= OS_ELEC_SWITCH_STATE_ON;
					else OSStateInfo[1].uiOSStateContent= OS_ELEC_SWITCH_STATE_OFF;
				   return SUCCESS;
				  case OS_STATE_CTRL_OBJ_AIRCONDITION :		//�����ǿյ������ж��ǿ��յ����ǹؿյ�
				  {
				  	 if(content==OS_ELEC_SWITCH_STATE_ON)
					  HI_tempNumber = EAC_OAC;
					  else if(content==OS_ELEC_SWITCH_STATE_OFF)
					  HI_tempNumber = EAC_CAC;
					  break;
				  }
				  case OS_STATE_CTRL_OBJ_CALORIFIER:		 //��������ˮ�������ж��ǿ���ˮ�����ǹ���ˮ��
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
		   case OS_STATE_INFO_TYPE_TEMP:					  //����Ϣ�������¶�����
		   {												    //���ж϶��������ÿյ��¶Ȼ���������ˮ���¶�
		   	  if(ctrl_Obj==OS_STATE_CTRL_OBJ_AIRCONDITION)	 //�����ǿյ����������ÿյ��¶Ⱥ��� 
			  return EAC_SendFeedbackMsg2(EAC_SAT,content);
			  else if(ctrl_Obj==OS_STATE_CTRL_OBJ_CALORIFIER)	  //��������ˮ��������������ˮ���¶Ⱥ���
			  return EAC_SendFeedbackMsg2(EAC_SWT,content);
		   }
		   default:break;
	   }
		return EAC_SendFeedbackMsg(HI_tempNumber);            //������Ӧ��������ȡ����ֵ
}

/**********************************************************************************************************
*        ��������HI_SendMsgToTask(functionNumber��EAC_temperature)
*        �������ͣ�INT16U  ��ʾ�ɹ����ߴ������͵ĺ궨��
*         �������ͣ�1��INT16U  ��ʾ��Ҫ��ִ�е�EAC����LCD�����ı�ŵĺ궨��
*                   2��INT16U  ��ʾ������Ҫ��ִ�еĺ�����Ҫ���¶Ȳ���
*        ���ܣ�   ���õײ��EAC���ƺ�������LCD���ƺ����������غ���ִ�еĴ����ɹ���Ϣ
************************************************************************************************************/
	 //�ú�����ȡ��

/*
INT16U HI_SendMsgToTask(functionNumber,EAC_temperature)
{
	//�ж�functionNumber������EAC��������LCD����
	//�������EAC����
	return EAC_SendFeedbackMsg(functionNumber,EAC_temperature);
    //�������LCD����
	return LCD_SendFeedbackMsg(functionNumber);
} 
*/

  
/*************************************************************************************************************
*                     ��������HI_SwapTempAndLight()
*                     �������ͣ�INT8U  ��ʾ�������͵ĺ궨��
*                     �������ͣ���
*                     ���ܣ�    �����л����¸й�ĺ�������ȡ����ֵ������
**************************************************************************************************************/

INT8U HI_SwapTempAndLight()
{
   return EAC_SendFeedbackMsg(EAC_STL);
}

/*************************************************************************************************************
*                     ��������HI_PageSwitch(pageID,focus)
*                     �������ͣ�void
*                     �������ͣ�1��INT8U ��ʾLCDҳ����
*                               2��INT8U ��ʾָ��ҳ�潹��
*                     ���ܣ�    ����LCD���л�����ͽ���ĺ���
**************************************************************************************************************/

void HI_PageSwitch(INT8U PageID,INT8U focus)
{
	  return;
}

/*************************************************************************************************************
*                     ��������HI_ErrorDisplay(errorType)
*                     �������ͣ�void
*                     �������ͣ�1��INT8U ��ʾ�������͵ĺ궨��
*                     ���ܣ�    ����LCD����ʾ����ĺ���
**************************************************************************************************************/

void HI_ErrorDisplay(INT8U errorType)
{

}



/*************************************************************************************************************
*                     ��������HI_IfKeyClicked()
*                     �������ͣ�BOLEAN  ��ʾ�Ƿ��а��������µĺ궨��
*                     �������ͣ� �޲���
*                     ���ܣ�    ��KEYģ��õ��Ƿ��м������µ���Ϣ
**************************************************************************************************************/

BOOLEAN HI_IfKeyClicked()
{
  return KEY_IfClicked();
}


/*************************************************************************************************************
*                     ��������HI_GetKeyValue_whichKey()
*                     �������ͣ�INT8U  ��ʾ�ĸ����������µĺ궨��
*                     �������ͣ� �޲���
*                     ���ܣ�    ��KEYģ��õ���ֵ1���ĸ��������£�
**************************************************************************************************************/

INT8U HI_GetKeyValue_whichKey()
{
	return KEY_SendKeyValue_whichKey();
}

/*************************************************************************************************************
*                     ��������HI_GetKeyValue_LongOrShort()
*                     �������ͣ�BOOLEAN  ��ʾ�������Ƕ̰��ĺ궨��
*                     �������ͣ� �޲���
*                     ���ܣ�    ��KEYģ��õ���ֵ2���������Ƕ̰���
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

