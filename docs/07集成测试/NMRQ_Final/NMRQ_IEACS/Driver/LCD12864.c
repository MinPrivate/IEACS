 //****************************************************************************************
//*																						  *
//*		 ***************************LCD12864驱动程序************************			  *
//*																						  *
//*****************************************************************************************

#include  "..\Include\config.h"

#define     LEDCON    0x00000800     //P0.11 引脚控制LED,低电平点亮
#define     LCDBK     0x00008000     //P0.15 引脚控制LCDBK,高电平使能

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864_WIDTH 128  		//宽度
#define LCD12864_HIGH  64   		//高度
#define LCD12864_PAGE  8    		//页数
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
#define LCD12864_CLR IOCLR			//数据清零
#define LCD12864_SET IOSET			//数据置一
#define LCD12864_DIR IODIR			//端口方向
#define LCD12864_PIN IOPIN			//端口状态

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864_SEL0 PINSEL0
#define LCD12864_SEL1 PINSEL1		//端口功能

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD_STARTROW 0xC0			//设置起始行指令
#define LCD_PAGE 	 0xB8			//设置页指令
#define LCD_LINE 	 0x40			//设置列指令

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

extern INT8U CM[];
extern INT8U number[12][16];   
extern INT8U hanzi[8][32]; 
extern INT8U Bmp12864[];
extern INT8U Bmp4030[];

/*******************************************************************************
*名称:Delay()
*功能:延时函数
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
//* 名称：vCheckBusy
//* 功能：检查LCD是否忙
//****************************************************************************
void vCheckBusy(void)     
{
	/*LCD12864_DIR &= 0xF9FFFF03;	    //数据线为输入
	
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

	LCD12864_DIR |= 0x060000FC;      	//数据线为输出*/ 	
	//Delay(100);
}

//****************************************************************************
//* 名称：vWriteCMD
//* 功能：写命令
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
//* 名称：vWriteData
//* 功能：写数据
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
//* 名称：vCleanAll
//* 功能：清屏
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
//* 名称：vLCDInit
//* 功能：初始化
//****************************************************************************
void vLCDInit(void)
{    
	PINSEL0 &= 0xFFFF000F;		   	//P0.2~P0.7为GPIO
    PINSEL1 &= 0xFFC0FF00;		   	//P0.16~P0.19、P0.24~P0.26为GPIO
	IODIR   |= 0x070F00FC;         	//P0.2~P0.7、P0.24~P0.26、P0.16~P0.19输出
	IOCLR   |= 0x070F00FC;         	//输出初始化零         
		
	vWriteCMD(0x3F);                //开显示
	vWriteCMD(0xC0);                //设置起始地址
	
	vCleanAll();					//清屏  
}

//****************************************************************************
//* 名称：Show88
//* 功能：显示8*8点阵字符
//* 参数：x_add:行(0-7), y_add: 列(0-15)，*po : 字模首址
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
//* 名称：ShowFullScreenBmp
//* 功能：显示128*64图片
//* 参数：*po : 字模首址
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
//* 名称：ShowPicture
//* 功能：在指定位置显示任意大小图片
//* 参数：PageAddr : 开始页地址
//*       YAddr    : 开始列地址
//*       pixelsX  : 像素点行
//*       pixelsY  : 像素点列
//*       *po      : 字模首址
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
//* 名称：vShowNum
//* 功能：显示8*16字符或16*16汉字
//****************************************************************************
void DispChOrCi(INT8U Flag,INT8U x_add,INT8U y_add,INT8U *po)
{
	INT8U nLoop,ucPage,ucLine;

	ucPage=x_add*2+0xb8;

    if(Flag==0)                                  // 16*16汉字
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

     if(Flag==1)                                  // 8*16字符
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
/// 名称：main
/// 功能：主函数
//////////////////////////////////////////////////////////////////////////////
/*
int main()
{
	INT8U nLoop;

    PINSEL0=0x00000000;              			 //设置IO口工作模式
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
