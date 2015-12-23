 //****************************************************************************************
//*																						  *
//*		 ***************************LCD12864��������************************			  *
//*																						  *
//*****************************************************************************************

#include  "..\Include\config.h"

#define     LEDCON    0x00000800     //P0.11 ���ſ���LED,�͵�ƽ����
#define     LCDBK     0x00008000     //P0.15 ���ſ���LCDBK,�ߵ�ƽʹ��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864_WIDTH 128  		//���
#define LCD12864_HIGH  64   		//�߶�
#define LCD12864_PAGE  8    		//ҳ��
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
#define LCD12864_CSA (1<<11)		//CSA
#define LCD12864_CSB (1<<12)		//CSB
#define LCD12864_RS	 (1<<13)   		//RS
#define LCD12864_RW	 (1<<14)		//RW
#define LCD12864_EN	 (1<<15)		//EN
*/

#define LCD12864_CSA (1<<19)		//CSA
#define LCD12864_CSB (1<<24)		//CSB
#define LCD12864_RS	 (1<<18)   		//RS
#define LCD12864_RW	 (1<<16)		//RW
#define LCD12864_EN	 (1<<17)		//EN


#define LCD12864_BUSY (1<<26)		//BUSY

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864_CLR IOCLR			//��������
#define LCD12864_SET IOSET			//������һ
#define LCD12864_DIR IODIR			//�˿ڷ���
#define LCD12864_PIN IOPIN			//�˿�״̬

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864_SEL0 PINSEL0
#define LCD12864_SEL1 PINSEL1		//�˿ڹ���

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD_STARTROW 0xC0			//������ʼ��ָ��
#define LCD_PAGE 	 0xB8			//����ҳָ��
#define LCD_LINE 	 0x40			//������ָ��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

extern INT8U CM[];
extern INT8U number[12][16];   
extern INT8U hanzi[8][32]; 
extern INT8U Bmp12864[];
extern INT8U Bmp4030[];

/*******************************************************************************
*����:Delay()
*����:��ʱ����
*******************************************************************************/
void Delay(INT32U x)
{
 	unsigned int i1,j1;
 	for(j1=0;j1<100;j1++)
   	{
    	for(i1=0;i1<x;i1++);
    }
}

//****************************************************************************
//* ���ƣ�vCheckBusy
//* ���ܣ����LCD�Ƿ�æ
//****************************************************************************
void vCheckBusy(void)     
{
	/*LCD12864_DIR &= 0xF9FFFF03;	    //������Ϊ����
	
	while(1)
	{
		LCD12864_CLR=LCD12864_RS;
		LCD12864_SET=LCD12864_RW;
		//LCD12864_SET=0x00FF0000;
		
		LCD12864_SET=LCD12864_EN;
		if(!(LCD12864_PIN & LCD12864_BUSY))
			break;
		LCD12864_CLR=LCD12864_EN;
	} 

	LCD12864_DIR |= 0x060000FC;      	//������Ϊ���*/ 	
	//Delay(100);
}

//****************************************************************************
//* ���ƣ�vWriteCMD
//* ���ܣ�д����
//****************************************************************************
void vWriteCMD(INT8U ucCMD)
{
	vCheckBusy();	             
	
	LCD12864_CLR=LCD12864_RS;
	LCD12864_CLR=LCD12864_RW;

	LCD12864_CLR=0x060000FC;
	LCD12864_SET=((ucCMD & 0x3F)<<2)+((ucCMD & 0xC0)<<19);
	
	LCD12864_SET=LCD12864_EN;
	LCD12864_CLR=LCD12864_EN;
}

//****************************************************************************
//* ���ƣ�vWriteData
//* ���ܣ�д����
//****************************************************************************
void vWriteData(INT8U ucData)
{
	vCheckBusy();	              

	LCD12864_SET=LCD12864_RS;
	LCD12864_CLR=LCD12864_RW;

	LCD12864_CLR=0x060000FC;
	LCD12864_SET=((ucData & 0x3F)<<2)+((ucData & 0xC0)<<19);
	
	LCD12864_SET=LCD12864_EN;
	LCD12864_CLR=LCD12864_EN;
}  

//****************************************************************************
//* ���ƣ�vCleanAll
//* ���ܣ�����
//****************************************************************************
void vCleanAll(void)
{
	INT8U ucPage,ucLine,nLoop;
	
	/*LCD12864_SET=LCD12864_CSA;
	LCD12864_SET=LCD12864_CSB;

	for(ucPage=0;ucPage<8;ucPage++)
	{
		vWriteCMD(LCD_PAGE+ucPage);
		vWriteCMD(LCD_LINE);
		for(ucLine=0;ucLine<64;ucLine++)
			vWriteData(0x55);
	}*/    
   
    for(ucPage=0;ucPage<8;ucPage++)
    {
        for(ucLine=0;ucLine<16;ucLine++)
        {
            if(ucLine<8) 
    		{
         		LCD12864_SET=LCD12864_CSA;
         		LCD12864_CLR=LCD12864_CSB;
    		}
    		else 
    		{
         		LCD12864_CLR=LCD12864_CSA;
         		LCD12864_SET=LCD12864_CSB;         
    		}  
    		vWriteCMD(ucPage+0xb8);
    		vWriteCMD((ucLine<8?ucLine:ucLine-8)*8+0x40);    
    		for(nLoop=0;nLoop<8;nLoop++) 
        		vWriteData(0); 	           
        }
    } 
}

//****************************************************************************
//* ���ƣ�vLCDInit
//* ���ܣ���ʼ��
//****************************************************************************
void vLCDInit(void)
{    
	PINSEL0 &= 0xFFFF000F;		   	//P0.2~P0.7ΪGPIO
    PINSEL1 &= 0xFFC0FF00;		   	//P0.16~P0.19��P0.24~P0.26ΪGPIO
	IODIR   |= 0x070F00FC;         	//P0.2~P0.7��P0.24~P0.26��P0.16~P0.19���
	IOCLR   |= 0x070F00FC;         	//�����ʼ����         
		
	vWriteCMD(0x3F);                //����ʾ
	vWriteCMD(0xC0);                //������ʼ��ַ
	
	vCleanAll();					//����  
}

//****************************************************************************
//* ���ƣ�Show88
//* ���ܣ���ʾ8*8�����ַ�
//* ������x_add:��(0-7), y_add: ��(0-15)��*po : ��ģ��ַ
//****************************************************************************
void Show88(INT8U x_add,INT8U y_add,INT8U *po)
{ 
    INT8U nLoop,ucPage,ucLine;

    ucPage=x_add+0xb8;
    ucLine=(y_add<8?y_add:y_add-8)*8+0x40;

    if(y_add>16) 
        return;

    if(y_add<8) 
    {
         LCD12864_SET=LCD12864_CSA;
         LCD12864_CLR=LCD12864_CSB;
    }
    else 
    {
         LCD12864_CLR=LCD12864_CSA;
         LCD12864_SET=LCD12864_CSB;         
    }

    vWriteCMD(ucPage);
    vWriteCMD(ucLine); 
    
    
    for(nLoop=0;nLoop<8;nLoop++) 
        vWriteData(*po++); 	
        
    LCD12864_CLR=LCD12864_CSA;
    LCD12864_CLR=LCD12864_CSB;  
}

//****************************************************************************
//* ���ƣ�ShowFullScreenBmp
//* ���ܣ���ʾ128*64ͼƬ
//* ������*po : ��ģ��ַ
//****************************************************************************
void ShowFullScreenBmp(INT8U *po)
{ 
    INT8U nChar,ucPage;      
  
    for(ucPage=0;ucPage<8;ucPage++)
    {
        for(nChar=0;nChar<16;nChar++)
        {
            Show88(ucPage,nChar,&po[nChar*8+ucPage*128]);             
        }
    }   
} 

//****************************************************************************
//* ���ƣ�ShowPicture
//* ���ܣ���ָ��λ����ʾ�����СͼƬ
//* ������PageAddr : ��ʼҳ��ַ
//*       YAddr    : ��ʼ�е�ַ
//*       pixelsX  : ���ص���
//*       pixelsY  : ���ص���
//*       *po      : ��ģ��ַ
//****************************************************************************
void ShowPicture(INT8U PageAddr,INT8U YAddr,INT8U pixelsX,INT8U pixelsY,INT8U *po)
{ 
    INT8U nLoop1,nLoop2;
    INT8U ZScrFlag;
    
    //vWriteCMD(PageAddr/8+0xb8);         
 
    for(nLoop2=0;nLoop2<(pixelsY/8+1);nLoop2++)
    {  
        if(YAddr<64)
        {
            LCD12864_SET=LCD12864_CSA;
            LCD12864_CLR=LCD12864_CSB;            
            vWriteCMD(YAddr+0x40);                    
            ZScrFlag=1;
        } 
        else
        { 
            LCD12864_CLR=LCD12864_CSA;
            LCD12864_SET=LCD12864_CSB;            
            vWriteCMD(YAddr-64+0x40);           
            ZScrFlag=0;
        }       

        for(nLoop1=0;nLoop1<pixelsX;nLoop1++)
        { 
            if(ZScrFlag)
            {
                if((nLoop1+YAddr)>63)
                {
                    LCD12864_CLR=LCD12864_CSA;
                    LCD12864_SET=LCD12864_CSB;
                    vWriteCMD(0x40);                  
                    ZScrFlag=0;
                }
            }
            vWriteCMD(PageAddr+nLoop2+0xb8);            
            vWriteData(*po++);                      
        }         
    }

    LCD12864_CLR=LCD12864_CSA;
    LCD12864_CLR=LCD12864_CSB; 
}

//****************************************************************************
//* ���ƣ�vShowNum
//* ���ܣ���ʾ8*16�ַ���16*16����
//****************************************************************************
void DispChOrCi(INT8U Flag,INT8U x_add,INT8U y_add,INT8U *po)
{
	INT8U nLoop,ucPage,ucLine;

	ucPage=x_add*2+0xb8;

    if(Flag==0)                                  // 16*16����
	{
    	ucLine=(y_add<4?y_add:y_add-4)*16+0x40;
       	
        if(y_add<4)
        {
            LCD12864_SET=LCD12864_CSA;
            LCD12864_CLR=LCD12864_CSB;
        }
        else
        {
            LCD12864_SET=LCD12864_CSB;
            LCD12864_CLR=LCD12864_CSA;
        }
     }

     if(Flag==1)                                  // 8*16�ַ�
     {
        ucLine=(y_add<8?y_add:y_add-8)*8+0x40;
        
        if(y_add<8)
        {
            LCD12864_SET=LCD12864_CSA;
            LCD12864_CLR=LCD12864_CSB;
        }
        else
        {
            LCD12864_SET=LCD12864_CSB;
            LCD12864_CLR=LCD12864_CSA;
        }
     }
	 vWriteCMD(ucPage);
     vWriteCMD(ucLine);
     
     if(Flag==0)
     {
        for(nLoop=0;nLoop<32;nLoop++)
	    {
	        if(nLoop==16)
	        {
		        vWriteCMD(ucPage+1);
                vWriteCMD(ucLine);
	        }
            vWriteData(*po++); 	        
	    }
     }

     if(Flag==1)
     {
        for(nLoop=0;nLoop<16;nLoop++)
	    { 
            if(nLoop==8)
	        {
		        vWriteCMD(ucPage+1);
                vWriteCMD(ucLine);
	        }
            vWriteData(*po++);             
        }
     }
	 
     LCD12864_CLR=LCD12864_CSA;
     LCD12864_CLR=LCD12864_CSB;
}

//////////////////////////////////////////////////////////////////////////////
/// ���ƣ�main
/// ���ܣ�������
//////////////////////////////////////////////////////////////////////////////
/*
int main()
{
	INT8U nLoop;

    PINSEL0=0x00000000;              			 //����IO�ڹ���ģʽ
   	PINSEL1=0x00000000;
   	IODIR|=LEDCON+LCDBK;     	       
   	IOCLR|=LEDCON;	
   	Delay(5000);
   	IOSET|=LEDCON;	
   	IOCLR|=LCDBK;	
   	
    vLCDInit(); 
    for(nLoop=0;nLoop<8;nLoop++)
    {
        DispChOrCi(0,1,nLoop,hanzi[nLoop]);
        DispChOrCi(1,2,nLoop,number[nLoop+4]);
    } 
    Delay(20000);
    
    vCleanAll();
    for(nLoop=0;nLoop<11;nLoop++)
    	Show88(4,nLoop+2,&CM[nLoop*8]);
    Delay(20000);
    
    vCleanAll();
    ShowFullScreenBmp(Bmp12864);
    Delay(20000);
    
    //vCleanAll(); 
    ShowPicture(2,50,40,30,Bmp4030);
    IOSET|=LCDBK;	
    while(1);
}
*/
//////////////////////////////////////////////////////////////////////////////
