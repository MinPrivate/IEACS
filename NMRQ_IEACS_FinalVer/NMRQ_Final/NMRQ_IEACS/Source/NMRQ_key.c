/****************************************************************************
*                         �ļ����� 	NMRQ_key.c
*                         �ļ�������KEYģ��ĺ����������ⰴ�������ͼ�ֵ��HIģ��
*                         ���ߣ�	������
*                         �������ڣ�2013-7-26
******************************************************************************/
 #include "..\Include\NMRQ_key.h"

 #include <lpc2103.h>
INT8U KEY_keyValue_whichKey;           //ȫ�ֱ�������ʾ���ĸ�����������
BOOLEAN KEY_keyValue_LongOrShort;      //ȫ�ֱ�������ʾ�ǳ������Ƕ̰�

 /****************************************************************************
*                    ������: KEY_DelayNS();   
*                    �������ͣ�void
*                    ����˵����INT16U ��ʾҪ��ʱ��ʱ��(ms)
*                    ���ܣ������ʱ
******************************************************************************/
void KEY_DelayNS(INT16U uiDly)
{ 
		 INT16U uiLoop;	                //�ֲ�������ִ��������ʱ��
		 for(;uiDly>0;uiDly--)
		 {
		   for(uiLoop=0;uiLoop<5000;uiLoop++) ;
		 }
}
/***************************************************************************************
*		          ������ BeepCount(count)
*			      �������ͣ�void
*                 ����˵��:INT16U	 ��ʾҪ��Ĵ���
*			      ���ܣ��÷���������һ���Ĵ���
***************************************************************************************/

void KEY_Beep(INT16U count)  //���������죬����Ϊ����
{	 
   	 PINSEL0 &= 0xffcfffff;         //��p0.10����ΪGPIO��
  	//  IODIR |=BEEP;				  //����Beep��Ϊ����� (Ӧд�ڳ�ʼ��������)
 	 //  IOCLR |=BEEP;				  //��ʼ������
	for(;count>0;count--)
  	{
		 IOSET |=BEEP;
		 KEY_DelayNS(40);
		 IOCLR |=BEEP;
		 KEY_DelayNS(40);
  	 }
}

/****************************************************************************
*                     ������: KEY_IfClicked();   
*                     �������ͣ�BOOLEAN	 ��ʾ�����Ƿ񱻰��µĺ궨��
*                     ����˵�����޲���
*                     ���ܣ�����Ƿ��а������£��ĸ��������£��������߶̰���
******************************************************************************/

BOOLEAN KEY_IfClicked()
{ 
  	   PINSEL1 &= 0xffff00ff;         //��p0.20~p0.23����ΪGPIO��
     
		 IODIR |= KH0+KH1;				 //��������Ϊ�����
		 IOCLR |= KH0+KH1;	           //����ȫ���õ�λ

		 IODIR &= 0xffcfffff;		   //��������Ϊ�����
		 KEY_keyValue_LongOrShort = KEY_SHORTCLICKED;//��Ĭ������Ϊ�̰�
		 if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))
		 {
	 	    KEY_DelayNS(30);							 //��ʱ��������
			 if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	 //�ٴζ�ȡ����״̬
			 {						                     //�������������߶���Ϊ0��˵���а���������
	  	 		 //��ʼ�ж����ĸ�����������
	  		 {
		 		 IOSET|=KC0+KC1;											  //�������ø�λ
				 IOCLR|=KH0;												  //����1�õ�λ������2�ø�λ
				 IOSET|=KH1;
	  
	  			 IODIR &= 0xffcfffff;										  //��������Ϊ�����
				 if((IOPIN & KC0)==0){KEY_keyValue_whichKey=KEY_SWI1;}  //����1Ϊ��λ���򰴼�1������
	  			 if((IOPIN & KC1)==0){KEY_keyValue_whichKey=KEY_SWI2;}  //  ����2Ϊ��λ���򰴼�2������

				 IOCLR |=KH1;												   //����1�ø�λ������2�õ�λ
				 IOSET |=KH0;

				 if((IOPIN & KC0)==0){KEY_keyValue_whichKey=KEY_SWI3;}  //  ����1Ϊ��λ���򰴼�3������
				 if((IOPIN & KC1)==0){KEY_keyValue_whichKey=KEY_SWI4;}   // ����2Ϊ��λ���򰴼�4������
			}
				//��ʼ�ж��ǳ������Ƕ̰�
				  
				  IOCLR |=KH0+KH1;	                                //����ȫ���õ�λ
				 KEY_DelayNS(100);
		 		  if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //����ʱ����������Ϊ0��������ʱ
					  {
					    KEY_DelayNS(100);
		      	   if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //����ʱ����������Ϊ0��������ʱ
			   	   {
						  KEY_DelayNS(100);
		        	      if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //����ʱ����������Ϊ0��������ʱ
			     	     {
							 KEY_DelayNS(200);
		           	      if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //����ʱ����������Ϊ0��������ʱ
			        	     {
							   KEY_DelayNS(300);
		              	     if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //����ʱ����������Ϊ0��˵���ǳ���
			          	     {
								   KEY_keyValue_LongOrShort = KEY_LONGCLICKED;
			           	    }
							   else  KEY_keyValue_LongOrShort = KEY_SHORTCLICKED;
			         	    }
			         	    else KEY_keyValue_LongOrShort = KEY_SHORTCLICKED;
			      	    }
			      	    else KEY_keyValue_LongOrShort = KEY_SHORTCLICKED;
			    	  }	
			    	  else KEY_keyValue_LongOrShort = KEY_SHORTCLICKED;
				  }

			 while(((IOPIN&KC0)==0)||((IOPIN&KC1)==0));	        //ֱ������û������,���˳�����������һ�ΰ��±���μ�⵽
			    
				IODIR |=KC0+KC1; 								 //����KEY_CLICKED��ͬʱ��������Ϊ�����
			   return KEY_CLICKED;
			   
			 }			   
			 else										
			 {IODIR |=KC0+KC1;return KEY_UNCLICKED;}			 //����KEY_UNCLICKED��ͬʱ��������Ϊ�����
	 
	 	}
		 else
		 {IODIR |=KC0+KC1;return KEY_UNCLICKED;}				 //����KEY_UNCLICKED��ͬʱ��������Ϊ�����

}

/****************************************************************************
*                      ������: KEY_SendKeyValue_whichKey();   
*                      �������ͣ�INT8U  ��ʾ�ĸ����������µĺ궨��
*                      ����˵�����޲���
*                      ���ܣ�����ֵ1���ĸ��������£����͸�HIģ��
******************************************************************************/

INT8U KEY_SendKeyValue_whichKey()
{
   		 return KEY_keyValue_whichKey;	    //����KEY_IfClicked()�б���ֵ
}

/****************************************************************************
*                     ������: KEY_SendKeyValue_LongOrShort();   
*                     �������ͣ�BOOLEAN  ��ʾ�ǳ������Ƕ̰��ĺ궨��
*                     ����˵�����޲���
*                     ���ܣ�����ֵ2���������Ƕ̰������͸�HIģ��
******************************************************************************/

BOOLEAN KEY_SendKeyValue_LongOrShort()
{
   		return KEY_keyValue_LongOrShort;         //����KEY_IfClicked()�б���ֵ
}

 

 /***********************************************************************************
 *
 *								END OF FILE
 *
 *************************************************************************************/

