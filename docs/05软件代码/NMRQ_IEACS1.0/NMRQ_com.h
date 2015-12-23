//�������Ͷ���
typedef  unsigned char INT8U;
typedef  unsigned short INT16U;

#include <LPC2103.H>
#include <cstring>

//�궨��
#define  LINK_ERROR   	0                           //
#define  LINK_SUCCESS 	1						    //

#define Fosc            11059200                    //Crystal frequence,10MHz~25MHz��should be the same as actual status. 
						                            //Ӧ����ʵ��һ������Ƶ��,10MHz~25MHz��Ӧ����ʵ��һ��
#define Fcclk           (Fosc * 2)                  //System frequence,should be (1~32)multiples of Fosc,and should be equal or less  than 60MHz. 
					                        	    //ϵͳƵ�ʣ�����ΪFosc��������(1~32)����<=60MHZ
#define Fcco            (Fcclk * 8)                 //CCO frequence,should be 2��4��8��16 multiples of Fcclk, ranged from 156MHz to 320MHz. 
					                        	    //CCOƵ�ʣ�����ΪFcclk��2��4��8��16������ΧΪ156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 1             //VPB clock frequence , must be 1��2��4 multiples of (Fcclk / 4).

#define  UART_BPS  9600

//�ӿں�������
void COM_SendDataDown(INT8U const *str);
INT8U COM_RecvDataDown(void);
void COM_InitDown(void);

//�ڲ���������
void COM_StatFresh(void);
void COM_PllPvbInit(void);
void COM_PortInit(void);
void COM_SendByteDown(INT8U data);
/***************************************************************
**************************End of File***************************
****************************************************************/
