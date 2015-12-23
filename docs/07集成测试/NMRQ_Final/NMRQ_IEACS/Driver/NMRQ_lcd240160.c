/******************************************************************************
*						�ļ�����	NMRQ_lcd240160.c	
*                       �ļ�������	���ļ�����LCDģ�����������ڲ������Լ��ӿں�������Ҫ������λ���˵���ʾ  
*                       ���ߣ�		����
*						����ʱ�䣺 	2013-8-1
******************************************************************************/


#include <lpc2103.h>
#include "..\Include\helper.h"
#include "..\Include\NMRQ_config.h"
#include "..\Include\NMRQ_lcd_zimo.h"

extern	TIME			*LCDSetTime;					/*	ʱ������ʱʹ�õ�ȫ�ֱ���	*/
extern	INT8U			 LCDSetElecSW;					/*	��������ʱʹ�õĵ������ر���	*/
extern	INT8U			 LCDSetElecTemp;				/*	��������ʱʹ�õĵ����¶ȱ���	*/
extern	INT8U			 LCDSetElecTimingHour;			/*	��������ʱʹ�õĵ�����ʱ����	*/
extern	INT8U			 LCDSetElecTimingMin;			/*	��������ʱʹ�õĵ�����ʱ����	*/
extern	INT8U			 LCDSetElecTimingSW;			/*	��������ʱʹ�õĵ�����ʱ����	*/
extern	BOOLEAN			 LCDSetElecTimingEnable;		/*	��������ʱʹ�õĵ�����ʱ����	*/

void LCD_WriteCommand(INT8U cmd);
void LCD_WriteData(INT8U data);
void LCD_Init(void);
void LCD_Clear(void);
//void LCD_PutHZ(INT8U col,INT8U row,INT8U HZcode);
//void LCD_Locatexy(INT8U x,INT8U y);
//========================================================================
// ����: void LCD_Init(void)
// ����: LCD��ʼ������
// ����: ��
// ����: ��
// �汾:
//========================================================================
void LCD_Init(void)
{
	PINSEL0 = PINSEL0&0xFFFFFF00;
	IODIR |= (0x1<<24)|(0x1<<25)|(0x1<<26)|(0xF<<16)|(0x3F<<2);
	H_LCD_RES;
}
//========================================================================
// ����: void LCD_Clear(void)
// ����: LCD��������
// ����: ��
// ����: ��
// �汾:
//========================================================================
void LCD_Clear(void)
{
	INT32U i;
	H_LCD_RES;
	delay_ms(3);
	L_LCD_A0;
	H_LCD_WR;
	H_LCD_RD;
	H_LCD_CS;
	L_LCD_RES;
	delay_ms(200);
	H_LCD_RES;
	delay_ms(500);
	for(i = 32765;i>0;i--)
	{
		LCD_WriteCommand(0x42);
		LCD_WriteData(0x00);	
	}
	LCD_WriteCommand(0x40);
	LCD_WriteData(0x10); //p1
	LCD_WriteData(0x07);  //p2
	LCD_WriteData(0x07); //p3
	LCD_WriteData(29);   //p4
	LCD_WriteData(90);  //p5
	LCD_WriteData(159);  //p6
	LCD_WriteData(30);  //p7
	LCD_WriteData(0);  //p8
	//scroll set
	LCD_WriteCommand(0x44);  
	LCD_WriteData(0x0);   //p1 sad1l
	LCD_WriteData(0x0);   //p2 sad1h
	LCD_WriteData(160);  //p3 sl1
	LCD_WriteData(0x58);  //p4 sad2l
	LCD_WriteData(0x02);  //p5 sad2h
	LCD_WriteData(160);  //p6 sl2
	LCD_WriteData(0x0);   //p7
	LCD_WriteData(0x0);   //p8
	LCD_WriteData(0x0);   //p9
	LCD_WriteData(0x0);   //p10
	//H D O T  S C R
	LCD_WriteCommand(0x5A);
	LCD_WriteData(0x0);
	//ovly set
	LCD_WriteCommand(0x5b);
	LCD_WriteData(0x0c);  //p1  Ĭ��00
	//display off
	LCD_WriteCommand(0x58);
	LCD_WriteData(0x06);
	//display on 
	LCD_WriteCommand(0x59);
}
//========================================================================
// ����: void LCD_Locatexy(INT8U x,INT8U y)
// ����: ��λһ����,��LCD�����еĵ�ת��Ϊ�Դ��еĶ�Ӧ��ֵ
// ����: x X ������ y Y ������  
// ����: ��
// �汾:
//========================================================================
void LCD_Locatexy(INT8U x,INT8U y)
{
	INT32U  temp;
	temp = (INT32U )y*PARAP9+x;
	LCD_WriteCommand(0x46);
	LCD_WriteData( (INT8U)(temp & 0xff) );
	LCD_WriteData( (INT8U)(temp /256 ) );
}
//========================================================================
// ����: void LCD_WriteCommand(INT8U cmd)
// ����: ��LCD�Ĵ�����д��ֵ
// ����: cmd д��Ĵ�����ֵ
// ����: ��
// �汾:
//========================================================================
void LCD_WriteCommand(INT8U cmd)
{
	INT32U command;
	command = (INT32U)cmd;
	command = ((command&0x3F)<<2)|((((command>>6)&0x3)<<25));
	IOCLR = LCD_DATA;
	IOSET = command;
	H_LCD_A0;
	L_LCD_CS;
	H_LCD_RD;
	L_LCD_WR;
	delay_ns(2); 
	H_LCD_WR;
	H_LCD_A0;
	H_LCD_CS;
	
}
//========================================================================
// ����: void LCD_WriteData(INT8U data)
// ����: ��LCD������RAM��д��һ���Լ�������
// ����: date д��RAM��ֵ
// ����: ��
// �汾:
//========================================================================
void LCD_WriteData(INT8U data)
{
	INT32U a;
	a = (INT32U)data;
	a = (((data&0x3F)<<2)|((((data>>6)&0x3)<<25)));
	IOCLR = LCD_DATA;
	IOSET = a;
	//LCD_CheckBusy();
	L_LCD_A0;
	L_LCD_CS;
	H_LCD_RD;
	L_LCD_WR;
	delay_ns(2);
	H_LCD_WR;
	H_LCD_A0;
	H_LCD_CS;
}
////==============================================================================
//// ����: void LCD_PutHZ(INT8U uicol,INT8U uirow,INT8U uiHZcode)
//// ����: �Ժ�����Ϊcol,������Ϊrow�ĵ�Ϊ�����ʾһ������ ���ִ�СΪ22X22
//// ����: col X ������ row Y ������  HZcode �ַ����ַ����е�ƫ����
//// ����: ��
//// �汾:
////========================================================================
//void LCD_PutHZ(INT8U uicol,INT8U uirow,const INT8U uiHZcode)
//{
//	INT8U i,j;
//	INT32U  x;
//	x = 0x42*uiHZcode;
//	LCD_WriteCommand(0x4c);
//	for(i=0;i<22;i++)
//	{
//		LCD_Locatexy(uicol,uirow);
//		LCD_WriteCommand(0x42);
//		for(j=0;j<3;j++)
//		{
//			LCD_WriteData(bmp_HZTable[x]);
//			x++;
//		}
//		uirow++;
//	}
//}
//=====================================================================================================================================
// ����: void LCD_Displaybmp (unsigned char uibmpx,unsignedchar uibmpy,unsigned char uirow,unsigned char uicol)
// ����: ��LCD ����ʵ����ϵ������
// ����:  uirow  ������  uicol ������ uibmpx ����  uibmpy ����
// ����: ��
// �汾:
//======================================================================================================================================
void LCD_Displayemptybmp (unsigned char uibmpx,unsigned char uibmpy,unsigned char uirow,unsigned char uicol)
{
	unsigned char k,yu;
	unsigned char i,j;
	unsigned short m=0;
	yu=(uibmpx)%8;
	k=(uibmpx)/8;
	if (yu==0)
	{
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k;j++)
			{
				LCD_WriteData(0x00);
				m++;
			}
			uicol++;
		 }
	}
	else
	{   
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k+1;j++)
			{
				LCD_WriteData(0x00);
				m++;
			}
			uicol++;
		 }
	}
}
//=====================================================================================================================================
// ����: void LCD_Displaybmp (INT8U uibmpx,unsignedchar uibmpy,INT8U uirow,INT8U uicol,INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��ͼƬ
// ����: *putbmp ͼƬ�����ַָ�� uirow  ������  uicol ������ uibmpx ͼ�ĳ�  uibmpy ͼ�Ŀ�
// ����: ��
// �汾:
//======================================================================================================================================
void LCD_Displaybmp (INT8U uibmpx,INT8U uibmpy,INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m,k,yu;
	INT8U i,j;
	m=0;
	yu=(uibmpx)%8;
	k=(uibmpx)/8;
	if (yu==0)
	{
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k;j++)
			{
				LCD_WriteData(putbmp[m]);
				m++;
			}
			uicol++;
		 }
	}
	else
	{   
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k+1;j++)
			{
				LCD_WriteData(putbmp[m]);
				m++;
			}
			uicol++;
		 }
	}
}
//=====================================================================================================================================
// ����: void LCD_Displaybmp (INT8U uibmpx,unsignedchar uibmpy,INT8U uirow,INT8U uicol,INT8U  *putbmp)
// ����: ��LCD ����ʵ����ϵ�ϻ���һ��ͼƬ��ȡ��
// ����: *putbmp ͼƬ�����ַָ�� uirow  ������  uicol ������ uibmpx ͼ�ĳ�  uibmpy ͼ�Ŀ�
// ����: ��
// �汾:
//======================================================================================================================================
void LCD_Displaybmpf (INT8U uibmpx,INT8U uibmpy,INT8U uirow,INT8U uicol,const INT8U  *putbmp)
{
	INT8U m,k,yu;
	INT8U i,j;
	m=0;
	yu=(uibmpx)%8;
	k=(uibmpx)/8;
	if (yu==0)
	{
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k;j++)
			{
				LCD_WriteData(~putbmp[m]);
				m++;
			}
			uicol++;
		 }
	}
	else
	{   
	for(i=0;i<uibmpy;i++)
		{
		LCD_Locatexy(uirow,uicol);
	    LCD_WriteCommand(0x4c);
	    LCD_WriteCommand(0x42);
			for(j=0;j<k+1;j++)
			{
				LCD_WriteData(~putbmp[m]);
				m++;
			}
			uicol++;
		 }
	}
}
//==============================================================================
// ����: void LCD_PutNumberOnMS(INT8U uicol,INT8U uirow,INT8U NumberOnMS)
// ����: ����������ʾʱ������һ������
// ����: col X ������ row Y ������   NumberOnMS �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
//========================================================================
void LCD_PutNumberOnMS(INT8U uicol,INT8U uirow,const INT8U uinumberonMS)
{
	INT8U i,j;
	INT32U  x;
	x = 0x3a*uinumberonMS;
	for(i=0;i<29;i++)
	{
		LCD_Locatexy(uicol,uirow);
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_zds[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// ����: void LCD_PutWeek(INT8U col,INT8U row,INT8U uiweek)
// ����: ����������ʾ���ڿ����һ����������
// ����: col X ������ row Y ������  uiweek �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
//========================================================================
void LCD_PutWeek(INT8U uicol,INT8U uirow,const INT8U uiweek)
{
	INT8U i,j;
	INT32U  x;
	x = 0x18*uiweek;				 //�����week����������ʼλ��
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //��λ��ʼ��ַ
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<2;j++)
		{
			LCD_WriteData(bmp_week[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// ����: void LCD_PutNumberOnData(INT8U uicol,INT8U uirow,INT8U uinumberondata)
// ����: ��һ��8X16������
// ����: uicol X ������ uirow Y ������   uinumberondata �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
//========================================================================
void LCD_PutNumberOnData(INT8U uicol,INT8U uirow,const INT8U uinumberondata)
{
	INT8U i,j;
	INT32U  x;
	x = 0x0c*uinumberondata;				 //�����uinumberondata����������ʼλ��
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //��λ��ʼ��ַ
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<1;j++)
		{
			LCD_WriteData(bmp_zsr[x]);
			x++;
		}
		uirow++;
	}
}
//==============================================================================
// ����: void LCD_PutNumberOnDataf(INT8U uicol,INT8U uirow,INT8U uinumberondata)
// ����: ��һ��8X16�����ֵ�ȡ��
// ����: uicol X ������ uirow Y ������   uinumberondata �ַ����ַ����е�ƫ����
// ����: ��
// �汾:
//========================================================================
void LCD_PutNumberOnDataf(INT8U uicol,INT8U uirow,const INT8U uinumberondata)
{
	INT8U i,j;
	INT32U  x;
	x = 0x0c*uinumberondata;				 //�����uinumberondata����������ʼλ��
	for(i=0;i<12;i++)
	{
		LCD_Locatexy(uicol,uirow);   //��λ��ʼ��ַ
		LCD_WriteCommand(0x4c);
		LCD_WriteCommand(0x42);
		for(j=0;j<1;j++)
		{
			LCD_WriteData(~bmp_zsr[x]);
			x++;
		}
		uirow++;
	}
}
////========================================================================
//// ����: INT16U LCD_PowerOn()
//// ����: ������ʾ����
//// ����: ��  
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////========================================================================
//INT8U LCD_PowerOn()
//{
//	LCD_Clear();
//	LCD_PutHZ(3,48,0); //��ʾ��
//	LCD_PutHZ(6,48,1); //��ʾ��
//	LCD_PutHZ(9,48,2); //��ʾ��
//	LCD_PutHZ(12,48,3);//��ʾ��
//	LCD_PutHZ(15,48,4);//��ʾ��
//	LCD_PutHZ(18,48,5);//��ʾ��
//	LCD_PutHZ(21,48,6);//��ʾϵ
//	LCD_PutHZ(24,48,7);//��ʾͳ
//	LCD_PutHZ(9,71,8); //��ʾ��
//	LCD_PutHZ(12,71,9);//��ʾӭ
//	LCD_PutHZ(15,71,10);//��ʾ��
//	LCD_PutHZ(18,71,15);//��ʾ��
//	return 1;
//}
////========================================================================
//// ����: INT8U LCD_PowerOff()
//// ����: ��ʾ�ػ�ҳ��
//// ����: ��
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////========================================================================
//INT8U LCD_PowerOff()
//{
//	LCD_Clear();
//	LCD_PutHZ(3,48,0); //��ʾ��
//	LCD_PutHZ(6,48,1); //��ʾ��
//	LCD_PutHZ(9,48,2); //��ʾ��
//	LCD_PutHZ(12,48,3);//��ʾ��
//	LCD_PutHZ(15,48,4);//��ʾ��
//	LCD_PutHZ(18,48,5);//��ʾ��
//	LCD_PutHZ(21,48,6);//��ʾϵ
//	LCD_PutHZ(24,48,7);//��ʾͳ
//	LCD_PutHZ(3,71,8); //��ʾ��
//	LCD_PutHZ(6,71,9); //��ʾӭ
//	LCD_PutHZ(9,71,10);//��ʾ��
//	LCD_PutHZ(12,71,11);//��ʾ��
//	LCD_PutHZ(15,71,12);//��ʾ��
//	LCD_PutHZ(18,71,13);//��ʾʹ
//	LCD_PutHZ(21,71,14);//��ʾ��
//	LCD_PutHZ(24,71,15);//��ʾ��
//	return 1;	
//}
//========================================================================
// ����: INT8U LCD_DispalyMainScreen()
// ����: ��ʾ��λ����������
// ����: ��
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_DisplayMainScreen()
 {
    LCD_Clear();
	LCD_Displaybmp(8,26,6,12,bmp_zf);	    //������ʱ��ֺ�
	LCD_Displaybmp(24,12,4,41,bmp_xq);		//����������
	LCD_Displaybmp(12,12,5,55,bmp_n);		//��������
	LCD_Displaybmp(12,12,9,55,bmp_y);		//��������
	LCD_Displaybmp(12,12,13,55,bmp_r);		//��������
    LCD_Displaybmp(128,19,13,16,bmp_znz);	//�������ܼҵ����ϵͳ
	LCD_Displaybmp(42,14,17,38,bmp_wd);		//�������¶�
	LCD_Displaybmp(16,14,25,38,bmp_wdf);	//�������¶ȷ���
	LCD_Displaybmp(42,14,17,55,bmp_gq);		//�������ǿ
	LCD_Displaybmp(7,14,25,55,bmp_gqf);		//�������ǿ����
	LCD_Displaybmp(60,12,3,80,bmp_md);		//�������ŵ�״̬
	LCD_Displaybmp(60,12,3,96,bmp_kt);		//������յ�״̬
	LCD_Displaybmp(78,12,16,80,bmp_wsd);	//���������ҵ�״̬
	LCD_Displaybmp(78,12,16,96,bmp_rsq);	//��������ˮ��
	LCD_Displaybmp(64,24,3,119,bmp_cd);		//������˵�����
	LCD_Displaybmp(64,24,17,119,bmp_dq);	//�������������
	return 1;
 }
//========================================================================
// ����: INT8U LCD_UpdateApplianceState(INT8U uiair_state,INT8U uiwaterh_state,INT8U uidoorl_state,INT8U uibedl_state)
// ����: ������λ���˵���״̬��Ϣ
// ����: uiair_state �յ�״̬��Ϣ 1��0��		  1Ϊ����0Ϊ��
//		 uiwaterh_state ��ˮ��״̬��Ϣ 1��0
//		 uidoorl_state  �ŵ�״̬��Ϣ 1��0
//       uibedl_state	���ҵ�״̬��Ϣ 1��0
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
INT8U LCD_UpdateApplianceState (INT8U uidoorl_state,INT8U uibedl_state,INT8U uiair_state,INT8U uiwaterh_state)
{	
	if (uidoorl_state == OS_ELEC_SWITCH_STATE_ON)
	{
		LCD_Displayemptybmp(16,16,10,78);
		LCD_Displaybmp(16,16,10,78,bmp_16y);//�ŵ�״̬��
	}
	else
	{
		LCD_Displayemptybmp(16,16,10,78);
	}
	if (uibedl_state ==OS_ELEC_SWITCH_STATE_ON)
	{
		LCD_Displayemptybmp(16,16,25,78);
		LCD_Displaybmp(16,16,25,78,bmp_16y);//���ҵ�״̬��    
	}
	else
	{
	    LCD_Displayemptybmp(16,16,25,78);
	}
	if (uiair_state == OS_ELEC_SWITCH_STATE_ON )
	{
		LCD_Displayemptybmp(16,16,10,93);
		LCD_Displaybmp(16,16,10,93,bmp_16y);//�յ�״̬��
	}
	else
	{
	    LCD_Displayemptybmp(16,16,10,93);
	}
	if(uiwaterh_state == OS_ELEC_SWITCH_STATE_ON)
	{
		LCD_Displayemptybmp(16,16,25,93);
		LCD_Displaybmp(16,16,25,93,bmp_16y);//��ˮ��״̬��
	}
	else
	{
		LCD_Displayemptybmp(16,16,25,93);
	}
	return 1;
}
//========================================================================
// ����: INT8U LCD_UpdateConnect(INT8U uiConnectdata)
// ����: ��ʾԶ��������ҳ��
// ����: uiConnectdata ��ǰ��PC������״̬ 1Ϊ���� 0Ϊ�Ͽ�
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_UpdateConnect(INT8U uiConnectdata)
 {
 	if (uiConnectdata == 1 )		   
	{
		LCD_Displayemptybmp(16,16,0,0);
		LCD_Displaybmp(16,16,0,0,bmp_9y);//ˢ��״̬ͼƬ
		LCD_Displaybmp(68,10,2,0,bmp_ycl);//��ʾԶ�̿���������
	}
	else 
	{
		LCD_Displaybmp(68,10,2,0,bmp_ycw); //��ʾδ����
	}
	return 	1;
 }	
//========================================================================
// ����: INT8U LCD_UpdateTIME(INT8U uihourfirst,INT8U uihoursecond,INT8U uiminutefirst,INT8U uiminutesecond)
// ����: ������ҳ��ʱ�䣬����
// ����: uihourfirst Сʱ��һλ
//       uihoursecond Сʱ�ڶ�λ
//       uiminutefirst ���ӵ�һλ
//		 uiminutesecond ���ӵڶ�λ	
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_UpdateTime(INT8U uihourfirst,INT8U uihoursecond,INT8U uiminutefirst,INT8U uiminutesecond)
 {
 	LCD_PutNumberOnMS(2,12,uihourfirst);
	LCD_PutNumberOnMS(4,12,uihoursecond);
	LCD_PutNumberOnMS(7,12,uiminutefirst);
	LCD_PutNumberOnMS(9,12,uiminutesecond);
	return 1;
 }
//========================================================================
// ����: INT8U LCD_UpdateWeek(INT8U uiweek)
// ����: ������ҳ�����ڼ�
// ����: uiweek ���ڼ�	
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_UpdateWeek(INT8U uiweek)
 {
 	LCD_PutWeek(7,41,uiweek);
	return 1;
 }
//===================================================================================================================================================================================================================================================
// ����: INT8U LCD_Update(INT8U uiyearfirst,INT8U uiyearsecond,INT8U uiyearthird,INT8U uiyearforth,INT8U uimonthfirst,INT8U uimonthsecond,INT8U uidayfirst,INT8U uidaysecond)
// ����: ������ҳ������
// ����: uinianfirst ��ĵ�һλ
//		 uiyearsecond ��ĵڶ�λ
//		 uiyearthird  ��ĵ���λ
//		 uiyearforth ��ĵ���λ
//		 uimonthfirst �µĵ�һλ
//		 uimonthsecond �µĵڶ�λ
//		 uidayfirst ��ĵ�һλ
//		 uidaysecond ��ĵڶ�λ
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//===================================================================================================================================================================================================================================================
 INT8U LCD_UpdateDate(INT8U uiyearfirst,INT8U uiyearsecond,INT8U uiyearthird,INT8U uiyearforth,INT8U uimonthfirst,INT8U uimonthsecond,INT8U uidayfirst,INT8U uidaysecond)
 {
 	LCD_PutNumberOnData(1,54,uiyearfirst);
	LCD_PutNumberOnData(2,54,uiyearsecond);
	LCD_PutNumberOnData(3,54,uiyearthird);
	LCD_PutNumberOnData(4,54,uiyearforth);
	LCD_PutNumberOnData(7,54,uimonthfirst);
	LCD_PutNumberOnData(8,54,uimonthsecond);
	LCD_PutNumberOnData(11,54,uidayfirst);
	LCD_PutNumberOnData(12,54,uidaysecond);
	return 1;
 }

//==========================================================================
// ����: INT8U LCD_UpdateCircumstance(INT8U uitem,INT8U uihum)
// ����: ���������滷����Ϣҳ��
// ����: uitem   �¶���Ϣ   uihum  ������Ϣ  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//===========================================================================
INT8U LCD_UpdateCircumstance(INT8U uitemfirst,INT8U uitemsecond,INT8U uihumfirst,INT8U uihumsecond)
{
	LCD_PutNumberOnData(22,37,uitemfirst);
	LCD_PutNumberOnData(23,37,uitemsecond);
	LCD_PutNumberOnData(22,55,uihumfirst);
	LCD_PutNumberOnData(23,55,uihumsecond);
	return 1;
}
//===================================================================================================================================================================================================================================================
// ����: INT8U LCD_Update(INT8U uicsyearfirst,INT8U uicsyearsecond,INT8U uicsyearthird,INT8U uicsyearforth,INT8U uicsmonthfirst,INT8U uicsmonthsecond,INT8U uicsdayfirst,INT8U uicsdaysecond)
// ����: ����ʱ�ӽ�����������
// ����: uinianfirst ��ĵ�һλ	 
//		 uicsyearsecond ��ĵڶ�λ 	 
//		 uicsyearthird ��ĵ���λ	 
//       uicsyearforth ��ĵ���λ
//       uicsmonthfirst �µĵ�һλ
//       uicsmonthsecond �µĵڶ�λ
//       uicsdayfirst    ��ĵ�һλ
//		 uicsdayfirst    ��ĵڶ�λ
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//===================================================================================================================================================================================================================================================
 INT8U LCD_UpdateClockSetDate(INT8U uicsyearfirst,INT8U uicsyearsecond,INT8U uicsyearthird,INT8U uicsyearforth,INT8U uicsmonthfirst,INT8U uicsmonthsecond,INT8U uicsdayfirst,INT8U uicsdaysecond)
 {
 	LCD_PutNumberOnData(10,48,uicsyearfirst);
	LCD_PutNumberOnData(11,48,uicsyearsecond);
	LCD_PutNumberOnData(12,48,uicsyearthird);
	LCD_PutNumberOnData(13,48,uicsyearforth);
	LCD_PutNumberOnData(16,48,uicsmonthfirst);
	LCD_PutNumberOnData(17,48,uicsmonthsecond);
	LCD_PutNumberOnData(20,48,uicsdayfirst);
	LCD_PutNumberOnData(21,48,uicsdaysecond);
	return 1;
}
//========================================================================
// ����: INT8U  LCD_UpdateClockSetTime(INT8U uicshourfirst,INT8U uicshoursecond,INT8U uicsminutefirst,INT8U uicsminutesecond)
// ����: ����ʱ������ʱ��
// ����: uicshourfirst Сʱ��һλ
//       uicshoursecond Сʱ�ڶ�λ
//       uicsminutefirst ���ӵ�һλ
//		 uicsminutesecond ���ӵڶ�λ	
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_UpdateClockSetTime(INT8U uicshourfirst,INT8U uicshoursecond,INT8U uicsminutefirst,INT8U uicsminutesecond)
 {
 	LCD_PutNumberOnData(10,65,uicshourfirst);
	LCD_PutNumberOnData(11,65,uicshoursecond);
	LCD_PutNumberOnData(14,65,uicsminutefirst);
	LCD_PutNumberOnData(15,65,uicsminutesecond);
	return 1;
 }
////==========================================================================
//// ����: INT8U LCD_UpdateTemSetAir(INT8U uitemsetfirst_air,INT8U uitemsetsecond_air)
//// ����: ���¿յ���Ϣҳ���¶��趨
//// ����: uitemsetfirst_air  �¶����õ�һλ   uitemsetsecond_air  �¶����õڶ�λ 
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////===========================================================================
//INT8U LCD_UpdateTemSetTem(INT8U uitemsetfirst,INT8U uitemsetsecond)
//{
//	LCD_PutNumberOnData(14,52,uitemsetfirst);
//	LCD_PutNumberOnData(15,52,uitemsetsecond);
//	return 1;
//}
////==========================================================================
//// ����: INT8U LCD_UpdateTimingSet(INT8U uitshourfirst,INT8U uitshoursecond,INT8U uitsminutefirst,INT8U uitsminutesecond,INT8U uitimingsetswitch)
//// ����: ���µ�����Ϣҳ�涨ʱʱ��
//// ����: uitshourfirst   ��ʱʱ��Сʱ��һλ   uitshoursecond  ��ʱʱ��Сʱ�ڶ�λ  uitsminutefirst ��ʱ���ӵ�һλ  uitsminutesecond ��ʱ���ӵڶ�λ  
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////===========================================================================
//INT8U LCD_UpdateTimingSet(INT8U uitshourfirst,INT8U uitshoursecond,INT8U uitsminutefirst,INT8U uitsminutesecond,INT8U uitimingsetswitch)
//{
//	LCD_PutNumberOnData(10,84,uitshourfirst);
//	LCD_PutNumberOnData(11,84,uitshoursecond);
//	LCD_PutNumberOnData(14,84,uitsminutefirst);
//	LCD_PutNumberOnData(15,84,uitsminutesecond);
//	if ( uitimingsetswitch ==1 )
//	{
//		LCD_Displaybmp(16,16,19,84,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,19,84,bmp_dqg);
//	}
//	return 1;
//}
//========================================================================
// ����: INT8U LCD_DisplayMenuSet()
// ����: ��ʾ�˵�����ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_DisplayMenuSet()
 {
 	LCD_Clear();
	LCD_Displaybmp(16,16,11,29,bmp_x1);
	LCD_Displaybmp(32,16,13,29,bmp_moshi);
	LCD_Displaybmp(32,16,17,29,bmp_m1);		//��ʾģʽѡ��

	LCD_Displaybmp(16,16,11,45,bmp_x2);
	LCD_Displaybmp(32,16,13,45,bmp_m2sz);
	LCD_Displaybmp(32,16,17,45,bmp_m3sz);  	//��ʾʱ������

	LCD_Displaybmp(16,16,11,61,bmp_x3);
	LCD_Displaybmp(32,16,13,61,bmp_m3dq);
	LCD_Displaybmp(32,16,17,61,bmp_m3sz);  //��ʾ��������

	LCD_Displaybmp(16,16,11,77,bmp_x4);
	LCD_Displaybmp(32,16,13,77,bmp_m4);
	LCD_Displaybmp(32,16,17,77,bmp_m1);	   	//��ʾ�ػ�ѡ��

	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
	return 	1;
 }

//========================================================================
// ����: INT8U LCD_DisplayModeSelect()
// ����: ��ʾģʽѡ��ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_DisplayModeSelect()
 {
 	LCD_Clear();
	LCD_Displaybmp(16,16,11,29,bmp_x1);
	LCD_Displaybmp(32,16,13,29,bmp_ms1);
	LCD_Displaybmp(32,16,17,29,bmp_moshi);	//��ʾ����ģʽ
	
	LCD_Displaybmp(16,16,11,45,bmp_x2);
	LCD_Displaybmp(32,16,13,45,bmp_ms2);
	LCD_Displaybmp(32,16,17,45,bmp_moshi);	//��ʾ�ؼ�ģʽ

	LCD_Displaybmp(16,16,11,61,bmp_x3);
	LCD_Displaybmp(32,16,13,61,bmp_ms3);
	LCD_Displaybmp(32,16,17,61,bmp_moshi);	//��ʾ����ģʽ

	LCD_Displaybmp(16,16,11,77,bmp_x4);
	LCD_Displaybmp(32,16,13,77,bmp_ms4);
	LCD_Displaybmp(32,16,17,77,bmp_moshi);	//��ʾ���ģʽ
	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
	return 	1;
 }
//========================================================================
// ����: INT8U LCD_DisplayTimeSet()
// ����: ��ʾʱ������ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
// �汾:
//========================================================================
 INT8U LCD_DisplayTimeSet()
 {
 	LCD_Clear();
	LCD_Displaybmp(32,16,5,48,bmp_szrq);		  //��ʾ����
 	LCD_Displaybmp(8,16,9,48,bmp_szfh);		  //��ʾ��
	LCD_Displaybmp(16,16,14,48,bmp_dqn); 	//��ʾ��
	LCD_Displaybmp(16,16,18,48,bmp_dqy);		 //��ʾ��
	LCD_Displaybmp(16,16,22,48,bmp_dqr);		 //��ʾ��
	LCD_Displaybmp(32,16,5,65,bmp_szsj);		 //��ʾʱ��
	LCD_Displaybmp(8,16,9,65,bmp_szfh);		  //��ʾ��
	LCD_Displaybmp(16,16,12,65,bmp_dqs);		 //��ʾʱ
	LCD_Displaybmp(16,16,16,65,bmp_dqf);		 //��ʾ��
	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
	return 	1;
 }
////========================================================================
//// ����: INT8U LCD_DisplayApplianceSet()
//// ����: ��ʾ��������ҳ��  ��Ϊ��ʾѡ���ĸ�������ҳ��
//// ����: ��  
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////========================================================================
// INT8U LCD_DisplayApplianceSet()
// {
// 	LCD_Clear();
//	LCD_Displaybmp(16,16,11,29,bmp_x1);
//	LCD_Displaybmp(32,16,13,29,bmp_as1);
//
//	LCD_Displaybmp(16,16,11,45,bmp_x2);
//	LCD_Displaybmp(48,16,13,45,bmp_as2);
//
//	LCD_Displaybmp(16,16,11,61,bmp_x3);
//	LCD_Displaybmp(32,16,13,61,bmp_as3);
//
//	LCD_Displaybmp(16,16,11,77,bmp_x4);
//	LCD_Displaybmp(48,16,13,77,bmp_as4);
//
//	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// ����: INT8U LCD_DisplayDoorl(INT8U uidoorl_state_display)
//// ����: ��ʾ�ŵ�ҳ��
//// ����: uidoorl_state_disaplay    ��ʾ�ŵƵ�����ǰ��״̬
////       ����ֱ�Ӷ�ȡϵͳ״̬�� ���������ʾ������ѵ�����ǰ״̬�����������  
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////========================================================================
// INT8U LCD_DisplayDoorl(INT8U uidoorl_state_display)
// {
// 	LCD_Clear();
// 	LCD_Displaybmp(32,16,9,20,bmp_as1);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uidoorl_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//��ʾ��ʱ
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //��ʾʱ��
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//��ʾ��
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //��ʾ��
//	LCD_Displaybmp(38,21,22,115,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// ����: INT8U LCD_DisplayBedl(INT8U uibedl_state_display)
//// ����: ��ʾ���ҵ�ҳ��
//// ����: uibedl_state_display ���ҵƵ�����ǰ��״̬  
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////========================================================================
// INT8U LCD_DisplayBedl(INT8U uibedl_state_display)
// {
// 	LCD_Clear();
//	LCD_Displaybmp(48,16,9,20,bmp_as2);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uibedl_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//��ʾ��ʱ
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //��ʾʱ��
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//��ʾ��
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //��ʾ��
//	LCD_Displaybmp(38,21,22,115,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// ����: INT8U LCD_DisplayAir_condition(INT8U uiair_state_display)
//// ����: ��ʾ�յ�ҳ��
//// ����: uiair_state_display �յ���ǰ״̬ 
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////========================================================================
// INT8U LCD_DisplayAir_condition(INT8U uiair_state_display)
// {
// 	LCD_Clear();
//	LCD_Displaybmp(32,16,9,20,bmp_as3);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uiair_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,52,bmp_dqwd);	   //��ʾ�¶�����
//	LCD_Displaybmp(8,16,13,52,bmp_szfh);	   //��ʾ��
//	LCD_Displaybmp(16,14,16,52,bmp_wdf);		//��ʾ�¶ȷ���
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//��ʾ��ʱ
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //��ʾʱ��
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//��ʾ��
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //��ʾ��
//	LCD_Displaybmp(38,21,22,115,bmp_fhjk);
//	return 	1;
// }
////========================================================================
//// ����: INT8U LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
//// ����: ��ʾ��ˮ��ҳ��
//// ����: uiwaterh_state_display ��ˮ����ǰ״̬ 
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
//// �汾:
////========================================================================
// INT8U  LCD_DisplayWaterHeater(INT8U uiwaterh_state_display)
// {
//	LCD_Clear();
//	LCD_Displaybmp(48,16,9,20,bmp_as4);//LCD_Display48bmp(9,20,bmp_dqrsq);
//	LCD_Displaybmp(32,16,9,36,bmp_dqdq);
//	LCD_Displaybmp(32,16,13,36,bmp_dqzt);
//	LCD_Displaybmp(8,16,17,36,bmp_szfh);
//	if (uiwaterh_state_display == 1)
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqk);
//	}
//	else 
//	{
//		LCD_Displaybmp(16,16,18,36,bmp_dqg);
//	}
//	LCD_Displaybmp(32,16,9,52,bmp_dqwd);	   //��ʾ�¶�����
//	LCD_Displaybmp(8,16,13,52,bmp_szfh);	   //��ʾ��
//	LCD_Displaybmp(16,14,16,52,bmp_wdf);		//��ʾ�¶ȷ���
//	LCD_Displaybmp(32,16,9,68,bmp_dqds);	//��ʾ��ʱ
//	LCD_Displaybmp(32,16,13,68,bmp_szsj);  //��ʾʱ��
//	LCD_Displaybmp(8,16,17,68,bmp_szfh);	//��ʾ��
//	LCD_Displaybmp(16,16,12,84,bmp_dqs);
//	LCD_Displaybmp(16,16,16,84,bmp_dqf);		 //��ʾ��
//	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
//	return 	1;
// }
//========================================================================
// ����: INT8U LCD_DisplayPowerOffSelect()
// ����: ��ʾ�ػ�ѡ��ҳ��
// ����: ��  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
//========================================================================
 INT8U LCD_DisplayPowerOffSelect()
 {
 	LCD_Clear();
	LCD_Displaybmp(16,16,11,34,bmp_x1);
	LCD_Displaybmp(32,16,13,34,bmp_m4);	  //��ʾ�ػ�
	LCD_Displaybmp(16,16,11,50,bmp_x2);
	LCD_Displaybmp(32,16,13,50,bmp_p2);	  //��ʾ����
	LCD_Displaybmp(16,16,11,66,bmp_x3);
	LCD_Displaybmp(32,16,13,66,bmp_p3);	  //��ʾ����
	LCD_Displaybmp(38,21,22,120,bmp_fhjk);
	return 	1;
 }
//==================================================================================
// ����: INT8U LCD_SelectMenuSetItem(INT8U menupagenumber,INT8U itemnumber)
// ����: ��ʾ�˵����õ�ǰ�Ĳ˵���
// ����: menunumber �˵���� itemnumber �˵�����  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
//=====================================================================================
INT8U LCD_SelectMenuSetItem(INT8U uimenupagenumber,INT8U uiitemnumber)
{
	switch(uimenupagenumber)
	{
	 	case 1:	  //�˵�����ҳ��
			if (uiitemnumber == 0)
				{
					LCD_Displaybmp(38,21,22,120,bmp_fhjk); 	  //�ָ����ذ�ť
					LCD_Displaybmpf(16,16,11,29,bmp_x1);	  
					LCD_Displaybmpf(32,16,13,29,bmp_moshi);
					LCD_Displaybmpf(32,16,17,29,bmp_m1);	 //��ʾģʽѡ��
						 
				}
			if (uiitemnumber == 1)
				{
					LCD_Displaybmp(16,16,11,29,bmp_x1);		  //�ָ�ģʽѡ��
					LCD_Displaybmp(32,16,13,29,bmp_moshi);
					LCD_Displaybmp(32,16,17,29,bmp_m1);
					LCD_Displaybmpf(16,16,11,45,bmp_x2);
					LCD_Displaybmpf(32,16,13,45,bmp_m2sz);
					LCD_Displaybmpf(32,16,17,45,bmp_m3sz);	  //��ʾʱ������
				}
			if (uiitemnumber == 2)
				{
					LCD_Displaybmp(16,16,11,45,bmp_x2);		 //�ָ�ʱ������
					LCD_Displaybmp(32,16,13,45,bmp_m2sz);
					LCD_Displaybmp(32,16,17,45,bmp_m3sz);
					LCD_Displaybmpf(16,16,11,61,bmp_x3);
					LCD_Displaybmpf(32,16,13,61,bmp_m3dq);
					LCD_Displaybmpf(32,16,17,61,bmp_m3sz);  //��ʾ��������
				}
			if (uiitemnumber == 3)
				{
					LCD_Displaybmp(16,16,11,61,bmp_x3);
					LCD_Displaybmp(32,16,13,61,bmp_m3dq);
					LCD_Displaybmp(32,16,17,61,bmp_m3sz);  //�ָ���������
					LCD_Displaybmpf(16,16,11,77,bmp_x4);
					LCD_Displaybmpf(32,16,13,77,bmp_m4);
					LCD_Displaybmpf(32,16,17,77,bmp_m1);	 //��ʾ�ػ�ѡ��	
				}
			if (uiitemnumber == 4)
				{
					LCD_Displaybmp(16,16,11,77,bmp_x4);
					LCD_Displaybmp(32,16,13,77,bmp_m4);
					LCD_Displaybmp(32,16,17,77,bmp_m1);	     //�ָ��ػ�ѡ��
					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //��ʾ���ذ�ť
				}
			break;
		default:
			break;
	}
}
//==================================================================================
// ����: INT8U LCD_SelectMedelSelectItem(INT8U menupagenumber,INT8U itemnumber)
// ����: ��ʾģʽѡ��ǰ�Ĳ˵���
// ����: menunumber �˵���� itemnumber �˵�����  
// ����: success ����ִ�гɹ�
//		 fault   ����ִ��ʧ��
//=====================================================================================
//INT8U LCD_SelectMedelSelectItem(INT8U uimenupagenumber,INT8U uiitemnumber)
//{
//	switch(uimenupagenumber)
//	{
//	 	case 2:			/////ģʽѡ��ҳ��
//			if (uiitemnumber == 0)
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //�ָ����ذ�ť
//					LCD_Displaybmpf(16,16,11,29,bmp_x1);
//					LCD_Displaybmpf(32,16,13,29,bmp_ms1);
//					LCD_Displaybmpf(32,16,17,29,bmp_moshi);	//��ʾ����ģʽ	
//				}
//			if (uiitemnumber == 1)							  //�ؼ�ģʽ
//				{
//					LCD_Displaybmp(16,16,11,29,bmp_x1);
//					LCD_Displaybmp(32,16,13,29,bmp_ms1);
//					LCD_Displaybmp(32,16,17,29,bmp_moshi);	//�ָ�����ģʽ
//					LCD_Displaybmpf(16,16,11,45,bmp_x2);
//					LCD_Displaybmpf(32,16,13,45,bmp_ms2);
//					LCD_Displaybmpf(32,16,17,45,bmp_moshi);	//��ʾ�ؼ�ģʽ	
//				}
//			if (uiitemnumber == 2)							 //����ģʽ
//				{
//					LCD_Displaybmp(16,16,11,45,bmp_x2);
//					LCD_Displaybmp(32,16,13,45,bmp_ms2);
//					LCD_Displaybmp(32,16,17,45,bmp_moshi);	//�ָ��ؼ�ģʽ
//					LCD_Displaybmpf(16,16,11,61,bmp_x3);
//					LCD_Displaybmpf(32,16,13,61,bmp_ms3);
//					LCD_Displaybmpf(32,16,17,61,bmp_moshi);	//��ʾ����ģʽ	
//				}
//			if (uiitemnumber == 3)							 //���ģʽ
//				{
//					LCD_Displaybmp(16,16,11,61,bmp_x3);
//					LCD_Displaybmp(32,16,13,61,bmp_ms3);
//					LCD_Displaybmp(32,16,17,61,bmp_moshi);	//�ָ�����ģʽ
//					LCD_Displaybmpf(16,16,11,77,bmp_x4);
//					LCD_Displaybmpf(32,16,13,77,bmp_ms4);
//					LCD_Displaybmpf(32,16,17,77,bmp_moshi);	//��ʾ���ģʽ	
//				}
//			if (uiitemnumber == 4)							 //���ذ�ť
//				{
//					LCD_Displaybmp(16,16,11,77,bmp_x4);
//					LCD_Displaybmp(32,16,13,77,bmp_ms4);
//					LCD_Displaybmp(32,16,17,77,bmp_moshi);	//�ָ����ģʽ
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//��ʾ���ذ�ť
//				}
//			break;
//		default:
//			break;
//	}
//}
////==================================================================================
//// ����: INT8U LCD_SelectMenuItem(INT8U menupagenumber,INT8U itemnumber)
//// ����: ��ʾ��ǰ�Ĳ˵���
//// ����: menunumber �˵���� itemnumber �˵�����  
//// ����: success ����ִ�гɹ�
////		 fault   ����ִ��ʧ��
////=====================================================================================
//INT8U LCD_SelectMenuItem(INT8U uimenupagenumber,INT8U uiitemnumber)
//{
//	switch(uimenupagenumber)
//	{
//	 	case 1:	  //�˵�����ҳ��
//			if (uiitemnumber == 0)
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk); 	  //�ָ����ذ�ť
//					LCD_Displaybmpf(16,16,11,29,bmp_x1);	  
//					LCD_Displaybmpf(32,16,13,29,bmp_moshi);
//					LCD_Displaybmpf(32,16,17,29,bmp_m1);	 //��ʾģʽѡ��
//						 
//				}
//			if (uiitemnumber == 1)
//				{
//					LCD_Displaybmp(16,16,11,29,bmp_x1);		  //�ָ�ģʽѡ��
//					LCD_Displaybmp(32,16,13,29,bmp_moshi);
//					LCD_Displaybmp(32,16,17,29,bmp_m1);
//					LCD_Displaybmpf(16,16,11,45,bmp_x2);
//					LCD_Displaybmpf(32,16,13,45,bmp_m2sz);
//					LCD_Displaybmpf(32,16,17,45,bmp_m3sz);	  //��ʾʱ������
//				}
//			if (uiitemnumber == 2)
//				{
//					LCD_Displaybmp(16,16,11,45,bmp_x2);		 //�ָ�ʱ������
//					LCD_Displaybmp(32,16,13,45,bmp_m2sz);
//					LCD_Displaybmp(32,16,17,45,bmp_m3sz);
//					LCD_Displaybmpf(16,16,11,61,bmp_x3);
//					LCD_Displaybmpf(32,16,13,61,bmp_m3dq);
//					LCD_Displaybmpf(32,16,17,61,bmp_m3sz);  //��ʾ��������
//				}
//			if (uiitemnumber == 3)
//				{
//					LCD_Displaybmp(16,16,11,61,bmp_x3);
//					LCD_Displaybmp(32,16,13,61,bmp_m3dq);
//					LCD_Displaybmp(32,16,17,61,bmp_m3sz);  //�ָ���������
//					LCD_Displaybmpf(16,16,11,77,bmp_x4);
//					LCD_Displaybmpf(32,16,13,77,bmp_m4);
//					LCD_Displaybmpf(32,16,17,77,bmp_m1);	 //��ʾ�ػ�ѡ��	
//				}
//			if (uiitemnumber == 4)
//				{
//					LCD_Displaybmp(16,16,11,77,bmp_x4);
//					LCD_Displaybmp(32,16,13,77,bmp_m4);
//					LCD_Displaybmp(32,16,17,77,bmp_m1);	     //�ָ��ػ�ѡ��
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //��ʾ���ذ�ť
//				}
//			break;
//		case 2:			/////ģʽѡ��ҳ��
//			if (uiitemnumber == 0)
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //�ָ����ذ�ť
//					LCD_Displaybmpf(16,16,11,29,bmp_x1);
//					LCD_Displaybmpf(32,16,13,29,bmp_ms1);
//					LCD_Displaybmpf(32,16,17,29,bmp_moshi);	//��ʾ����ģʽ	
//				}
//			if (uiitemnumber == 1)							  //�ؼ�ģʽ
//				{
//					LCD_Displaybmp(16,16,11,29,bmp_x1);
//					LCD_Displaybmp(32,16,13,29,bmp_ms1);
//					LCD_Displaybmp(32,16,17,29,bmp_moshi);	//�ָ�����ģʽ
//					LCD_Displaybmpf(16,16,11,45,bmp_x2);
//					LCD_Displaybmpf(32,16,13,45,bmp_ms2);
//					LCD_Displaybmpf(32,16,17,45,bmp_moshi);	//��ʾ�ؼ�ģʽ	
//				}
//			if (uiitemnumber == 2)							 //����ģʽ
//				{
//					LCD_Displaybmp(16,16,11,45,bmp_x2);
//					LCD_Displaybmp(32,16,13,45,bmp_ms2);
//					LCD_Displaybmp(32,16,17,45,bmp_moshi);	//�ָ��ؼ�ģʽ
//					LCD_Displaybmpf(16,16,11,61,bmp_x3);
//					LCD_Displaybmpf(32,16,13,61,bmp_ms3);
//					LCD_Displaybmpf(32,16,17,61,bmp_moshi);	//��ʾ����ģʽ	
//				}
//			if (uiitemnumber == 3)							 //���ģʽ
//				{
//					LCD_Displaybmp(16,16,11,61,bmp_x3);
//					LCD_Displaybmp(32,16,13,61,bmp_ms3);
//					LCD_Displaybmp(32,16,17,61,bmp_moshi);	//�ָ�����ģʽ
//					LCD_Displaybmpf(16,16,11,77,bmp_x4);
//					LCD_Displaybmpf(32,16,13,77,bmp_ms4);
//					LCD_Displaybmpf(32,16,17,77,bmp_moshi);	//��ʾ���ģʽ	
//				}
//			if (uiitemnumber == 4)							 //���ذ�ť
//				{
//					LCD_Displaybmp(16,16,11,77,bmp_x4);
//					LCD_Displaybmp(32,16,13,77,bmp_ms4);
//					LCD_Displaybmp(32,16,17,77,bmp_moshi);	//�ָ����ģʽ
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//��ʾ���ذ�ť
//				}
//			break;
//		case 5:				 //ʱ�����ý���
//			if (uiitemnumber == 0)								///ѡ��ʱ�����ý�����
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);    		///�ָ����ذ�ť
//					LCD_PutNumberOnDataf(10,48,(LCDSetTime->uiTimeYear)/1000);	//ѡ����ĵ�һλ
//					LCD_PutNumberOnDataf(11,48,((LCDSetTime->uiTimeYear)%1000)/100);	//ѡ����ĵڶ�λ
//					LCD_PutNumberOnDataf(12,48,((LCDSetTime->uiTimeYear)%100)/10);	//ѡ����ĵ���λ
//					LCD_PutNumberOnDataf(13,48,(LCDSetTime->uiTimeYear)%10);	//ѡ����ĵ���λ			 	
//				}
//			if (uiitemnumber == 1)							   /////ѡ��ʱ�����ý�����
//				{
//					LCD_PutNumberOnData(10,48,(LCDSetTime->uiTimeYear)/1000);	//�ָ���ĵ�һλ
//					LCD_PutNumberOnData(11,48,((LCDSetTime->uiTimeYear)%1000)/100);	//�ָ���ĵڶ�λ
//					LCD_PutNumberOnData(12,48,((LCDSetTime->uiTimeYear)%100)/10);	//�ָ���ĵ���λ
//					LCD_PutNumberOnData(13,48,(LCDSetTime->uiTimeYear)%10);	//�ָ���ĵ���λ
//					LCD_PutNumberOnDataf(16,48,(LCDSetTime->uiTimeMonth)/10);	//ѡ���µĵ�һλ
//					LCD_PutNumberOnDataf(17,48,(LCDSetTime->uiTimeMonth)%10); //ѡ���µĵڶ�λ			 	
//				}
//			if (uiitemnumber ==2)	   ///��/////////
//				{
//				 	LCD_PutNumberOnData(16,48,(LCDSetTime->uiTimeMonth)/10);	//�ָ��µĵ�һλ
//					LCD_PutNumberOnData(17,48,(LCDSetTime->uiTimeMonth)%10); //�ָ��µĵڶ�λ
//					LCD_PutNumberOnDataf(20,48,(LCDSetTime->uiTimeDay)/10);	 //ѡ����ĵ�һλ
//					LCD_PutNumberOnDataf(21,48,(LCDSetTime->uiTimeDay)%10);	 //ѡ����ĵڶ�λ
//				}
//			if (uiitemnumber ==3)	 /////ʱ/////////
//				{
//				 	LCD_PutNumberOnData(20,48,(LCDSetTime->uiTimeDay)/10);	 //�ָ���ĵ�һλ
//					LCD_PutNumberOnData(21,48,(LCDSetTime->uiTimeDay)%10);	 //�ָ���ĵڶ�λ
//					LCD_PutNumberOnDataf(10,65,(LCDSetTime->uiTimeHour)/10);	 //ѡ��Сʱ�ĵ�һλ
//					LCD_PutNumberOnDataf(11,65,(LCDSetTime->uiTimeHour)%10);	 //ѡ��Сʱ�ĵڶ�λ
//				}
//			if (uiitemnumber ==4)  /////////��/////////////
//				{
//				 	LCD_PutNumberOnData(10,65,(LCDSetTime->uiTimeHour)/10);	 //�ָ�Сʱ�ĵ�һλ
//					LCD_PutNumberOnData(11,65,(LCDSetTime->uiTimeHour)%10);	 //�ָ�Сʱ�ĵڶ�λ
//					LCD_PutNumberOnDataf(14,65,(LCDSetTime->uiTimeMinute)/10);  //ѡ�����ӵĵ�һλ
//					LCD_PutNumberOnDataf(15,65,(LCDSetTime->uiTimeMinute)%10); //ѡ�����ӵĵڶ�λ
//				}
//			if (uiitemnumber ==5)  ///////���ذ�ť//////////
//				{
//					LCD_PutNumberOnData(14,65,(LCDSetTime->uiTimeMinute)/10);  //�ָ����ӵĵ�һλ
//					LCD_PutNumberOnData(15,65,(LCDSetTime->uiTimeMinute)%10); //�ָ����ӵĵڶ�λ
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);			  //ѡ�����ذ�ť
//				}	
//	 		break;
//		case 3:		   ///��������ҳ��
//			if (uiitemnumber == 0)						  
//			{
//						LCD_Displaybmp(38,21,22,120,bmp_fhjk);//�ָ����ذ�ť
//						LCD_Displaybmpf(16,16,11,29,bmp_x1);
//						LCD_Displaybmpf(32,16,13,29,bmp_as1);  //��ʾ�ŵ���
//			}
//			if (uiitemnumber == 1)						  
//			{				 
//						LCD_Displaybmp(16,16,11,29,bmp_x1);
//						LCD_Displaybmp(32,16,13,29,bmp_as1);  //�ָ��ŵ���
//						LCD_Displaybmpf(16,16,11,45,bmp_x2);
//						LCD_Displaybmpf(48,16,13,45,bmp_as2);   //ѡ�����ҵ�		
//			}
//			if (uiitemnumber == 2)						  
//			{
//						LCD_Displaybmp(16,16,11,45,bmp_x2);
//						LCD_Displaybmp(48,16,13,45,bmp_as2);   //�ָ����ҵ�
//						LCD_Displaybmpf(16,16,11,61,bmp_x3);
//						LCD_Displaybmpf(32,16,13,61,bmp_as3);   //ѡ���յ���	
//			}
//			if (uiitemnumber == 3)						  
//			{
//						LCD_Displaybmp(16,16,11,61,bmp_x3);
//						LCD_Displaybmp(32,16,13,61,bmp_as3);   //�ָ��յ���
//						LCD_Displaybmpf(16,16,11,77,bmp_x4);
//						LCD_Displaybmpf(48,16,13,77,bmp_as4);	//ѡ����ˮ����
//			}
//			if (uiitemnumber == 4)						  
//			{
//						LCD_Displaybmp(16,16,11,77,bmp_x4);
//						LCD_Displaybmp(48,16,13,77,bmp_as4);	//�ָ���ˮ����
//						LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//ѡ��������
//			}
//			break;
//		case 4:			//�ػ�ѡ��ҳ��
//			if (uiitemnumber == 0)						
//				{
//					LCD_Displaybmp(38,21,22,120,bmp_fhjk);//�ָ����ذ�ť
//					LCD_Displaybmpf(16,16,11,34,bmp_x1);
//					LCD_Displaybmpf(32,16,13,34,bmp_m4);	  //��ʾ�ػ�	
//				}
//			if (uiitemnumber == 1)					   
//				{
//					LCD_Displaybmp(16,16,11,34,bmp_x1);
//					LCD_Displaybmp(32,16,13,34,bmp_m4);	  //�ָ��ػ�
//					LCD_Displaybmpf(16,16,11,50,bmp_x2);
//					LCD_Displaybmpf(32,16,13,50,bmp_p2);	//��ʾ����	
//				}
//			if (uiitemnumber == 2)					   
//				{
//					LCD_Displaybmp(16,16,11,50,bmp_x2);
//					LCD_Displaybmp(32,16,13,50,bmp_p2);	//�ָ�����
//					LCD_Displaybmpf(16,16,11,66,bmp_x3);
//					LCD_Displaybmpf(32,16,13,66,bmp_p3);	  //��ʾ����	
//				}
//			if (uiitemnumber == 3)					   
//				{
//					LCD_Displaybmp(16,16,11,66,bmp_x3);
//					LCD_Displaybmp(32,16,13,66,bmp_p3);	  //�ָ�����
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	  //��ʾ����ѡ��
//				}
//	   	break;
//		case 6:	 //�ŵ�ҳ��˵�
//			if (uiitemnumber == 0)	//�ŵƿ���
//			   {
//				   	LCD_Displaybmpf(38,21,22,120,bmp_fhjk);//�ָ����ذ�ť
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1 )	//�ŵ�ҳ�涨ʱСʱλ
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);	////ʹ��������
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 2 )	//�ŵ�ҳ�涨ʱ����λ
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 3 )	//�ŵ�ҳ�涨ʱ�����λ
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )				 //ѡ����ʱ����
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//				}
//			
//			if (uiitemnumber == 4)
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )			   //�ָ���ʱ����
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);///ѡ�����ذ�ť
//				}
//		break;
//		case 7:	   ///////���ҵƽ���/////////////////////
//			if (uiitemnumber == 0)	//���ҵƿ���
//			   {
//				   	LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //�ָ����ذ�ť
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1 )	//���ҵ�ҳ�涨ʱСʱλ
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 2 )	//���ҵ�ҳ�涨ʱ����λ
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 3 )	//���ҵ�ҳ�涨ʱ�����λ
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//				}
//			if (uiitemnumber == 4)
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);   //���ذ�ť
//				}
//		break;
//	    case 8:	   ////�յ�����//////////////
//			if (uiitemnumber == 0)	//�յ�����
//			   {
//				   	LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //�ָ����ذ�ť
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1)	//�յ��¶�
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}                      
//					LCD_PutNumberOnDataf(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnDataf(15,52,LCDSetElecTemp%10);
//				}
//			if (uiitemnumber == 2 )	//�յ�ҳ�涨ʱСʱλ
//				{
//					LCD_PutNumberOnData(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnData(15,52,LCDSetElecTemp%10);
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 3 )	//�յ�ҳ�涨ʱλ
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 4 )	//�յ���ҳ�涨ʱ�����λ
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//				}
//			
//			if (uiitemnumber == 5)	//////////���ذ�ť/////////
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else
//					{
//					}
//						LCD_Displaybmpf(38,21,22,120,bmp_fhjk); ///ѡ�����ذ�ť
//				}
//		break;
//		case 9:
//			if (uiitemnumber == 0)	//��ˮ������
//			   {
//				   	LCD_Displaybmp(38,21,22,120,bmp_fhjk);   //�ָ����ذ�ť
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmpf(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//				}
//			if (uiitemnumber == 1)	//��ˮ���¶�
//				{
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_OFF)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqg);
//						}
//					if (LCDSetElecSW ==OS_ELEC_SWITCH_STATE_ON)
//						{
//							LCD_Displaybmp(16,16,18,36,bmp_dqk);
//						}
//					else 
//						{
//						}
//					LCD_PutNumberOnDataf(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnDataf(15,52,LCDSetElecTemp%10);
//				}
//			if (uiitemnumber == 2 )	//��ˮ��ҳ�涨ʱСʱλ
//				{
//					LCD_PutNumberOnData(14,52,LCDSetElecTemp/10);
//					LCD_PutNumberOnData(15,52,LCDSetElecTemp%10);////////ʹ�¶Ȼָ�
//					LCD_PutNumberOnDataf(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnDataf(11,84,LCDSetElecTimingHour%10);	
//				}
//			if (uiitemnumber == 3 )	//��ˮ��ҳ�涨ʱ����λ
//				{
//					LCD_PutNumberOnData(10,84,LCDSetElecTimingHour/10);
//					LCD_PutNumberOnData(11,84,LCDSetElecTimingHour%10);
//					LCD_PutNumberOnDataf(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnDataf(15,84,LCDSetElecTimingMin%10);
//				}
//			if (uiitemnumber == 4 )	//��ˮ��ҳ�涨ʱ�����λ
//				{
//					LCD_PutNumberOnData(14,84,LCDSetElecTimingMin/10);
//					LCD_PutNumberOnData(15,84,LCDSetElecTimingMin%10);
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmpf(16,16,19,84,bmp_dqg);
//					}
//					else 
//						{
//						}
//				}
//			
//			if (uiitemnumber == 5)	//////////���ذ�ť/////////
//				{
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_ON )
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqk);
//					}
//					if ( LCDSetElecTimingSW ==OS_ELEC_SWITCH_STATE_OFF ) 
//					{
//						LCD_Displaybmp(16,16,19,84,bmp_dqg);
//					}
//					else 
//						{
//						}
//					LCD_Displaybmpf(38,21,22,120,bmp_fhjk);///ѡ�����ذ�ť
//				}
//		break;
//		default:
//		break;
//	}	
//}
////========================================================================
//// ����: INT8U LCD_DisplayWarning(INT8U uiwarningtype)
//// ����: ��ʾ����ҳ��
//// ����: uiwarningtype ���������
//// ����: success ����ִ�гɹ�
////========================================================================
// INT8U LCD_DisplayWarning(INT8U uiwarningtype)
// {
//	LCD_Clear();
//	switch (uiwarningtype)
//	{
//	case 1:		 //ú��й©����
////		LCD_Displaybmp(72,60,11,20,bmp_jg);//��ʾ����ͼƬ
//	    LCD_Displaybmp(88,21,10,84,bmp_mq); 	//��ʾú��й©��������
//		LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//��ʾ���������水ť
//		break;
//	case 2:	 //С͵���뾯��
////		LCD_Displaybmp(68,60,11,20,bmp_jg);//��ʾ����ͼƬ
//		LCD_Displaybmp(88,21,10,84,bmp_xt);	//��ʾС͵����
//		LCD_Displaybmpf(38,21,22,120,bmp_fhjk);	//��ʾ���������水ť
//		break;
//	default:
//		break;
//	}
//	return 	1;
//}
/******************************************************************************
*							
*                      END   FILE 
*                      
******************************************************************************/
