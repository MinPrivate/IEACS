/****************************************************************************
*                         �ļ����� 	NMRQ_eac.c
*                         �ļ�������eacģ��ĺ�����������λ����Ӳ������
*                         ���ߣ�	������
*                         �������ڣ�2013-7-26
******************************************************************************/


#include	"..\Include\NMRQ_eac.h"
#include	<LPC2103.h>



INT8U EAC_ADState = EAC_AD_STATE_TEMP; //ADת����״̬��Ĭ���Ǹ���״̬
/***********************************************************************************************
*                  �������� EAC_OpenDoorLight()
*                  �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                  �������ͣ� �޲���
*                  ���ܣ�   ���ŵ�    
***********************************************************************************************/

INT8U EAC_OpenDoorLight()
{	 //	if�ж�ȡ��ǰ���״̬�����Ѿ��򿪣���ֱ�ӷ���
     if(OSStateInfo[0].uiOSStateContent ==OS_ELEC_SWITCH_STATE_ON)
	 	{
		 return SUCCESS;
		 }
	 else 
	 	{
		   PINSEL0 &= 0xff3fffff;         //p0.11������ΪGPIO����
		   IODIR  |= 0x00000800;         //p0.11����Ϊ���
	 	   IOCLR  |= 0x00000800;         //p0.11����͵�ƽ����LED1
	    return SUCCESS;
	 	} 
}

/***********************************************************************************************
*                    �������� EAC_CloseDoorLight()
*                    �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                    �������ͣ� �޲���
*                    ���ܣ�   �ر��ŵ�    
***********************************************************************************************/

INT8U EAC_CloseDoorLight()
{  //if�ж�ȡ��ǰ���״̬�����Ѿ��رգ���ֱ�ӷ���
   	if(OSStateInfo[0].uiOSStateContent==OS_ELEC_SWITCH_STATE_OFF)
		 {
	    return SUCCESS;
		}
	else 
		{
		   PINSEL0 &= 0xff3fffff;         //p0.11������ΪGPIO����
		   IODIR  |= 0x00000800;         //p0.11����Ϊ���
		   IOSET  |= 0x00000800;		   //p0.11����ߵ�ƽ���ر�LED1
	   return SUCCESS;
		}
}

/***********************************************************************************************
*                    �������� EAC_OpenAirCondition()
*                    �������ͣ�INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                    �������ͣ� �޲���
*                    ���ܣ�   �����յ�    
***********************************************************************************************/

INT8U EAC_OpenAirCondition()
{  //if�ж�ȡ��ǰ�յ�״̬�����Ѿ��򿪣���ֱ�ӷ���
    if(OSStateInfo[2].uiOSStateContent==OS_ELEC_SWITCH_STATE_ON)
	{	
		return SUCCESS;
	}
	else
	{
	 	 PINSEL0 &= 0xfcffffff;            //p0.12������ΪGPIO����
		  IODIR  |= 0x00001000;            //p0.12����Ϊ�����
		  IOCLR  |= 0x00001000;            //p0.12����͵�ƽ����LED2
		return SUCCESS;
	}
}

/***********************************************************************************************
*                      �������� EAC_CloseAirCondition()
*                      �������ͣ�INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                      �������ͣ� �޲���
*                      ���ܣ�   �رտյ�
***********************************************************************************************/

INT8U EAC_CloseAirCondition()
{	//if�ж�ȡ��ǰ�յ�״̬�����Ѿ��رգ���ֱ�ӷ���
	if(OSStateInfo[2].uiOSStateContent==OS_ELEC_SWITCH_STATE_OFF)
    	{	
		return SUCCESS;
		}
	else
		{
	  	PINSEL0 &= 0xfcffffff;            //p0.12������ΪGPIO����
	  	IODIR  |= 0x00001000;            //p0.12����Ϊ�����
	  	IOSET  |= 0x00001000;            //p0.12����ߵ�ƽ���ر�LED2
		return SUCCESS;
		}    
}

/***********************************************************************************************
*                      �������� EAC_SetAirCond_Temp(aTemp)
*                      �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                      ����˵����  INT8U���ͣ���ʾ�¶� 
*                      ���ܣ�   ���ÿյ��¶�
***********************************************************************************************/

INT8U EAC_SetAirCond_Temp(INT8U aTemp)
{	//if�ж�ȡ�յ��¶ȣ�������aTemp����ֱ�ӷ���
      if(OSStateInfo[4].uiOSStateContent==aTemp)
	  	{
	 	 return SUCCESS;
	 	 }
	  else
	 	 {
	      //���¶���ΪaTemp
	  	 OSStateInfo[4].uiOSStateContent=aTemp;
		return SUCCESS;
	 	 }
}

/***********************************************************************************************
*                      �������� EAC_OpenWaterheater()
*                      �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                      �������ͣ� �޲���
*                      ���ܣ�   ������ˮ��
***********************************************************************************************/

INT8U EAC_OpenWaterheater()
{  //if�ж�ȡ��ǰ��ˮ��״̬�����Ѿ��򿪣���ֱ�ӷ���
	 if(OSStateInfo[3].uiOSStateContent==OS_ELEC_SWITCH_STATE_ON)
		 {
		 return SUCCESS;
	 	}
	 else
		 {
	 	  PINSEL0 &= 0xf3ffffff;        //p0.13������ΪGPIO����
	 	  IODIR  |= 0x00002000;        //p0.13����Ϊ�����
	 	  IOCLR  |= 0x00002000;        //p0.13����͵�ƽ������LED3
	 	  return SUCCESS;
		 }
}

/***********************************************************************************************
*                     �������� EAC_CloseWaterheater()
*                     �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                     �������ͣ� �޲���
*                     ���ܣ�   �ر���ˮ��
***********************************************************************************************/

INT8U EAC_CloseWaterheater()
{	//	if�ж�ȡ��ǰ��ˮ��״̬�����Ѿ��رգ���ֱ�ӷ���
	 if(OSStateInfo[3].uiOSStateContent==OS_ELEC_SWITCH_STATE_OFF )
		{
		 return SUCCESS;
		 }
	 else
		 {
		  PINSEL0 &= 0xf3ffffff;        //p0.13������ΪGPIO����
		  IODIR  |= 0x00002000;        //p0.13����Ϊ�����
	   	  IOSET  |= 0x00002000;        //p0.13����ߵ�ƽ���ر�LED3
	 	  return SUCCESS;
		 }
}

/***********************************************************************************************
*                    �������� EAC_SetWaterheater_Temp(wTemp)
*                    �������ͣ�INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                    �������ͣ�INT8U ��ʾ�¶� 
*                    ���ܣ�   ������ˮ���¶�
***********************************************************************************************/

INT8U EAC_SetWaterheater_Temp(INT8U wTemp)
{	//if�ж�ȡ��ǰ��ˮ���¶ȣ�������wTemp����ֱ�ӷ���
    if(OSStateInfo[5].uiOSStateContent==wTemp)
		{
		return SUCCESS;
		}
	else 
		{
	  //���¶�����ΪwTemp
	 	 OSStateInfo[5].uiOSStateContent=wTemp;
		  return SUCCESS;
		}
}
/****************************************************************************
*                 ������: EAC_DelayNS(nDly);   
*                 �������ͣ�void
*                 �������ͣ�INT16U,��ʾҪ��ʱ��ʱ��ms
*                 ���ܣ������ʱ
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
*			      �������� EAC_Bell(count)
*			      �������ͣ�void
*                 �������ͣ� INT16U ��ʾ��������˸����
*				  ���ܣ�ʹ��������˸
***********************************************************************/
 /*
void EAC_Bell(INT16U count)
{ 
    PINSEL0 &= 0xcfffffff;         //p0.14��������ΪGPIO����
	IODIR  |= 0x00004000;         //p0.14����Ϊ�����
	IOCLR  |= 0x00004000;          //��ʼʱ�Ȳ���˸
	for(;count>0;count--)
	{
	  IOSET |= 0x00004000;			//��ʼ��˸
	  EAC_DelayNS(5);
	  IOCLR |= 0x00004000;
	  EAC_DelayNS(5);
	}

}
  */

/***************************************************************************************
*		     ������ EAC_BeepAndBell(count)
*			 �������ͣ�void
*            ��������:INT16U	 ��ʾҪ��������Ĵ�����LED4��˸�Ĵ���
*			 ���ܣ��÷���������һ���Ĵ�������LED4��˸һ���Ĵ���
***************************************************************************************/

void EAC_BeepAndBell(INT16U count)         //���������죬����Ϊ����
{	 
   	 PINSEL0 &= 0xffcfffff;            //��p0.10����ΪGPIO��
  	  IODIR |=0x000000400 ;				  //����Beep��Ϊ�����
  	  IOCLR |=0x000000400 ;				  //��ʼ������

		PINSEL0 &= 0xcfffffff;         //p0.14��������ΪGPIO����
		IODIR  |= 0x00004000;         //p0.14����Ϊ�����
		IOCLR  |= 0x00004000;          //��ʼʱ�Ȳ���˸
   for(;count>0;count--)
  	  {
		 IOSET |=0x000000400 ;			    //��
		 IOCLR |= 0x00004000;			    //��ʼ��
		 EAC_DelayNS(80);
		 IOCLR |=0x000000400;
		 IOSET |= 0x00004000;
		 EAC_DelayNS(80);
   	 }
}
/***********************************************************************************************
*                     �������� EAC_GetTemperatureInfo()
*                     �������ͣ� void
*                     �������ͣ� �޲���
*                     ���ܣ�   ��ȡ�¶���Ϣ
**********************************************************************************************/

void EAC_GetTemperatureInfo()
{
       INT8U tempMsg;
   	  INT32U ADDRData;
  	  PINSEL0 = (PINSEL0 & 0xffcfffff)|0x00300000;     //��p0.10�˿�����ΪAIN3
		ADCR = 0x00200408;                              //����AD��10-bits,3MHz
		ADCR |= 0x01000000;                               //����ADת����
		do{
		  ADDRData = ADDR3;
		}while((ADDRData&0x80000000)==0);					 //�ȴ�ת�����
		ADCR &= ~0x01000000;                            //�ر�ADת����
		ADDRData =(ADDRData>>6)&0x03ff;                 //��������

		 ADDRData /=10;                         //��ʱ0=<ADDRData<=1023,������в���ʹ����������¶���Ϣ
		 if(ADDRData>40)
		 {
		    ADDRData /=2;			          //��ʱADDRData����0~40֮��
		 }
	
		OSStateInfo[7].uiOSStateContent = ADDRData;     //���������ݸ���ϵͳ״̬����¶���Ϣ
		if(ADDRData <12)								 //�¶�̫�ͣ���򿪿յ������ø���
		{
		   tempMsg = EAC_OpenAirCondition();
		   EAC_SetAirCond_Temp(ADDRData+15);
	 	  if(tempMsg==SUCCESS)
	 	  {
		   OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;			 //�޸�״̬��
	 	  }
		}
		 if(ADDRData>30)							  //�¶�̫�ߣ���򿪿յ������õ���
		 {
	 		tempMsg = EAC_CloseAirCondition();
			 EAC_SetAirCond_Temp(ADDRData-10);
     	    if(tempMsg==SUCCESS) 			                 //�޸�״̬��
	 	   {
	  	   OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
	  	   }
		 }

}

/***********************************************************************************************
*                     �������� EAC_GetLightInfo()
*                     �������ͣ�void
*                     �������ͣ� �޲���
*                     ���ܣ�   ��ȡ������Ϣ
***********************************************************************************************/

void EAC_GetLightInfo()
{	 
    	INT16U tempMsg;
		INT32U ADDRData;
   	 PINSEL0 = (PINSEL0 & 0xffcfffff)|0x00300000;     //��p0.10�˿�����ΪAIN3
		ADCR = 0x00200408;                              //����AD��10-bits,3MHz
		ADCR |= 0x01000000;                               //����ADת����
		do{
		  ADDRData = ADDR3;
		}while((ADDRData&0x80000000)==0);					 //�ȴ�ת�����
		ADCR &= ~0x01000000;                            //�ر�ADת����
		ADDRData =(ADDRData>>6)&0x03ff;                 //��������
		//��ʱADDRData����0~1023֮��

		ADDRData /=10;          //��С10���󣬽���0~102֮��
   	   OSStateInfo[8].uiOSStateContent = ADDRData;     //���������ݸ���ϵͳ״̬��Ĺ�ǿ��Ϣ
		if(ADDRData <40)								 //����̫�ͣ�����ŵ�
		{
		   tempMsg = EAC_OpenDoorLight();
	 	  if(tempMsg==SUCCESS)
	 	  {
		   OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;			 //�޸�״̬��
	 	  }
		}
		 if(ADDRData>70)							  //����̫�ߣ���ر��ŵ�
		 {
	 		tempMsg = EAC_CloseDoorLight();
     	    if(tempMsg==SUCCESS) 			                 //�޸�״̬��
	 	   {
	  	   OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
	  	  }
		 }
}


/***********************************************************************************************
*                     �������� EAC_SwapTempAndLight()
*                     �������ͣ� INT16U �ɹ����ߴ�����Ϣ�ĺ궨��
*                     �������ͣ� �޲���
*                     ���ܣ�   �л����º͸й⹦��
***********************************************************************************************/

INT8U EAC_SwapTempAndLight()
{
		 if(EAC_ADState == EAC_AD_STATE_TEMP)  //����ʱ�Ǹ���״̬�����л��ɸй�״̬
		  {
	 	  EAC_GetLightInfo();
	 	  EAC_ADState = EAC_AD_STATE_LIGHT;
	 	  }
	 	  else 							   //�����л��ɸ���״̬
	 	  {
	  	 	 EAC_GetTemperatureInfo();
			 EAC_ADState = EAC_AD_STATE_TEMP;
	  	 }
		return SUCCESS;
}

/***********************************************************************************************
*                     �������� EAC_ThiefFound()
*                     �������ͣ� INT16U �ɹ����ߴ�����Ϣ�ĺ궨��
*                     �������ͣ� �޲���
*                     ���ܣ�   ��⵽С͵��ִ�еĺ������жϴ�������
***********************************************************************************************/

INT8U EAC_ThiefFound()
{
    
		EAC_BeepAndBell(100);				 //���������� ��������˸
		//EAC_Bell(1);				        	 
   		 return SUCCESS;
}

/***********************************************************************************************
*                     �������� EAC_GasLeak()
*                     �������ͣ� INT16U �ɹ����ߴ�����Ϣ�ĺ궨��
*                     �������ͣ� �޲���
*                     ���ܣ�   ��⵽ú��й©��ִ�еĺ������жϴ�������
***********************************************************************************************/

INT8U EAC_GasLeak()
{	//�ر����е�����������������
   		 INT8U tempMsg;
		tempMsg = EAC_CloseDoorLight();
    	//if(tempMsg==SUCCESS) 			                 //�ر��ŵƣ��޸�״̬��
		  //{
		  OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
		   OSStateInfo[1].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
		 // }
		 tempMsg = EAC_CloseAirCondition();
		//if(tempMsg==SUCCESS)						 //�رտյ����޸�״̬��
		//{
		   OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;
		//}
		tempMsg = EAC_CloseWaterheater(); 
		//if(tempMsg==SUCCESS)							 //�ر���ˮ�����޸�״̬��
		//{
		   OSStateInfo[3].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF; 
		//}

   		 EAC_BeepAndBell(100);							 //���������� ��������˸
		return SUCCESS;
}
  

/***********************************************************************************************
*                   �������� EAC_GetFeedbackMsg(EAC_functionNumber)
*                   �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                   �������ͣ� INT8U ��ʾ�����ĳ�������ı��
*                   ���ܣ�   ��ȡĳһ������ִ�к�ĳɹ����ߴ�����Ϣ
***********************************************************************************************/

INT8U EAC_GetFeedbackMsg(INT8U EAC_functionNumber)
{   	INT8U tempErrorMsg;
 	switch(EAC_functionNumber){//����EAC_functionNumber�ж�ִ���ĸ���������ȡ��������
 	 case EAC_ODL:
		tempErrorMsg = EAC_OpenDoorLight();		  //���ݲ����жϵó���ִ�п��ƺ���
		if(tempErrorMsg != SUCCESS){
       tempErrorMsg = EAC_OPENLIGHT_ERROR;	  //����ִ�в��ɹ������ش�������
		  }
		  else 
		OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;    //����ִ�гɹ������޸�״̬��
		break;
 	 case EAC_CDL:
		tempErrorMsg = EAC_CloseDoorLight();	   //���ݲ����жϵó���ִ�йصƺ���
		if(tempErrorMsg != SUCCESS){				   //����ִ�в��ɹ������ش�������
			tempErrorMsg = EAC_CLOSELIGHT_ERROR;
     		}
			else 
		OSStateInfo[0].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF;//����ִ�гɹ����޸�״̬��
		break;
 	 case EAC_OAC:
		tempErrorMsg = EAC_OpenAirCondition();	   //���ݲ����жϵó���ִ�п��յ�����
		if(tempErrorMsg != SUCCESS){					 //����ִ�в��ɹ������ش�������
			tempErrorMsg = EAC_OPENAIRCOND_ERROR;  
		    }
			else 
		  OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON;//����ִ�гɹ����޸�״̬��
		break;
  	case EAC_CAC:
		tempErrorMsg = EAC_CloseAirCondition();	   //���ݲ����жϵó���ִ�йؿյ�����
   		 if(tempErrorMsg != SUCCESS){				   //����ִ�в��ɹ������ش�������
			tempErrorMsg = EAC_CLOSEAIRCOND_ERROR;
			}
			else
			 OSStateInfo[2].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF; //����ִ�гɹ����޸�״̬��
		break;
 	case EAC_OWH:
		tempErrorMsg = EAC_OpenWaterheater();		//���ݲ����жϵó���ִ�п���ˮ������
		if(tempErrorMsg != SUCCESS){					//����ִ�в��ɹ������ش�������
			tempErrorMsg = EAC_OPENWATERHEATER_ERROR;
			}
			else 
			OSStateInfo[3].uiOSStateContent=OS_ELEC_SWITCH_STATE_ON; //����ִ�гɹ����޸�״̬��
			break;
 	 case EAC_CWH:
		tempErrorMsg = EAC_CloseWaterheater();		//���ݲ����жϵó���ִ�й���ˮ������
		if(tempErrorMsg != SUCCESS){					//����ִ�в��ɹ������ش�������
			tempErrorMsg = EAC_CLOSEWATERHEATER_ERROR;
			}
			else
			 OSStateInfo[3].uiOSStateContent=OS_ELEC_SWITCH_STATE_OFF; //����ִ�гɹ����޸�״̬��
		break;
 	 case EAC_STL:
		tempErrorMsg = EAC_SwapTempAndLight();		 //���ݲ����жϵó���ִ���л����¸й⺯��
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
		tempErrorMsg = EAC_ThiefFound();		  //���ݲ����жϵó���ִ�з���С͵�ĺ���
		if(tempErrorMsg != SUCCESS){
			tempErrorMsg = EAC_THIEFFOUND_ERROR;
			}
		break;
 	 case EAC_GAL:
		tempErrorMsg = EAC_GasLeak();			   //���ݲ����жϵó���ִ��ú��й©�ĺ���
		if(tempErrorMsg != SUCCESS){
			tempErrorMsg = EAC_GASLEAK_ERROR;
			}
		break;
 	 default:break;
	}
 	 return tempErrorMsg;

}

/***********************************************************************************************
*                �������� EAC_GetFeedbackMsg2(EAC_functionNumber,EAC_temperature)
*                �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                �������ͣ�1�� INT8U ��ʾ�����ĳ�������ı��,
*                          2��INT8U ��ʾҪ���õĺ�����Ҫ���¶Ȳ���
*                ���ܣ�   ��ȡĳһ������ִ�к�ĳɹ����ߴ�����Ϣ
***********************************************************************************************/

INT8U EAC_GetFeedbackMsg2(INT8U EAC_functionNumber,INT8U EAC_temperature)
{
    	 INT8U tempErrorMsg;
		switch(EAC_functionNumber){
		case EAC_SAT:
			tempErrorMsg = EAC_SetAirCond_Temp(EAC_temperature);	//���ݲ����жϸ�ִ�����ÿյ��¶ȵĺ���
      	   if(tempErrorMsg != SUCCESS){
			   tempErrorMsg = EAC_SETAIRCONDTEMP_ERROR;
			   }
			 break;
		case EAC_SWT:
			tempErrorMsg = EAC_SetWaterheater_Temp(EAC_temperature); //���ݲ����жϸ�ִ��������ˮ���¶ȵĺ���
			if(tempErrorMsg != SUCCESS){
			tempErrorMsg = EAC_SETWATERHEATERTEMP_ERROR;
			}
			break;
		default:break;
	
	}
   return tempErrorMsg;

}

/***********************************************************************************************
*                   �������� EAC_SendFeedbackMsg(EAC_functionNumber)
*                   �������ͣ� INT8U �ɹ����ߴ�����Ϣ�ĺ궨��
*                   �������ͣ� INT8U ��ʾ�����ĳ�������ı��
*                   ���ܣ�   ����ȡ����ĳһ������ִ�к�ĳɹ����ߴ�����Ϣ���͸�HIģ��
***********************************************************************************************/
INT8U EAC_SendFeedbackMsg(INT8U EAC_functionNumber)
{
   	  return EAC_GetFeedbackMsg(EAC_functionNumber);
}

/***********************************************************************************************
*                  �������� EAC_SendFeedbackMsg2(EAC_functionNumber��EAC_temperature )
*                  �������ͣ� INT16U �ɹ����ߴ�����Ϣ�ĺ궨��
*                  �������ͣ�1�� INT16U ��ʾ�����ĳ�������ı��
                             2�� INT16U ��ʾ��Ҫ���õĺ������¶���Ϣ
*                  ���ܣ�   ����ȡ����ĳһ������ִ�к�ĳɹ����ߴ�����Ϣ���͸�HIģ��
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

