/****************************************************************************
*                         文件名： 	NMRQ_key.c
*                         文件描述：KEY模块的函数，负责检测按键并发送键值给HI模块
*                         作者：	杨林龙
*                         创建日期：2013-7-26
******************************************************************************/
 #include "..\Include\NMRQ_key.h"

 #include <lpc2103.h>
INT8U KEY_keyValue_whichKey;           //全局变量，表示是哪个按键被按下
BOOLEAN KEY_keyValue_LongOrShort;      //全局变量，表示是长按还是短按

 /****************************************************************************
*                    函数名: KEY_DelayNS();   
*                    返回类型：void
*                    参数说明：INT16U 表示要延时的时间(ms)
*                    功能：软件延时
******************************************************************************/
void KEY_DelayNS(INT16U uiDly)
{ 
		 INT16U uiLoop;	                //局部变量，执行以消耗时间
		 for(;uiDly>0;uiDly--)
		 {
		   for(uiLoop=0;uiLoop<5000;uiLoop++) ;
		 }
}
/***************************************************************************************
*		          函数名 BeepCount(count)
*			      返回类型：void
*                 参数说明:INT16U	 表示要响的次数
*			      功能：让蜂鸣器鸣响一定的次数
***************************************************************************************/

void KEY_Beep(INT16U count)  //蜂鸣器鸣响，参数为次数
{	 
   	 PINSEL0 &= 0xffcfffff;         //将p0.10设置为GPIO口
  	//  IODIR |=BEEP;				  //设置Beep口为输出口 (应写在初始化函数中)
 	 //  IOCLR |=BEEP;				  //开始不鸣响
	for(;count>0;count--)
  	{
		 IOSET |=BEEP;
		 KEY_DelayNS(40);
		 IOCLR |=BEEP;
		 KEY_DelayNS(40);
  	 }
}

/****************************************************************************
*                     函数名: KEY_IfClicked();   
*                     返回类型：BOOLEAN	 表示按键是否被按下的宏定义
*                     参数说明：无参数
*                     功能：检测是否有按键按下（哪个键被按下，长按或者短按）
******************************************************************************/

BOOLEAN KEY_IfClicked()
{ 
  	   PINSEL1 &= 0xffff00ff;         //将p0.20~p0.23设置为GPIO口
     
		 IODIR |= KH0+KH1;				 //将行线设为输出口
		 IOCLR |= KH0+KH1;	           //行线全部置低位

		 IODIR &= 0xffcfffff;		   //设置列线为输入口
		 KEY_keyValue_LongOrShort = KEY_SHORTCLICKED;//先默认设置为短按
		 if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))
		 {
	 	    KEY_DelayNS(30);							 //延时消除抖动
			 if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	 //再次读取列线状态
			 {						                     //若还有任意列线读数为0，说明有按键被按下
	  	 		 //开始判断是哪个按键被按下
	  		 {
		 		 IOSET|=KC0+KC1;											  //将列线置高位
				 IOCLR|=KH0;												  //行线1置低位，行线2置高位
				 IOSET|=KH1;
	  
	  			 IODIR &= 0xffcfffff;										  //设置列线为输入口
				 if((IOPIN & KC0)==0){KEY_keyValue_whichKey=KEY_SWI1;}  //列线1为低位，则按键1被按下
	  			 if((IOPIN & KC1)==0){KEY_keyValue_whichKey=KEY_SWI2;}  //  列线2为低位，则按键2被按下

				 IOCLR |=KH1;												   //行线1置高位，行线2置低位
				 IOSET |=KH0;

				 if((IOPIN & KC0)==0){KEY_keyValue_whichKey=KEY_SWI3;}  //  列线1为低位，则按键3被按下
				 if((IOPIN & KC1)==0){KEY_keyValue_whichKey=KEY_SWI4;}   // 列线2为低位，则按键4被按下
			}
				//开始判断是长按还是短按
				  
				  IOCLR |=KH0+KH1;	                                //行线全部置低位
				 KEY_DelayNS(100);
		 		  if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //再延时，若读数还为0，继续延时
					  {
					    KEY_DelayNS(100);
		      	   if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //再延时，若读数还为0，继续延时
			   	   {
						  KEY_DelayNS(100);
		        	      if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //再延时，若读数还为0，继续延时
			     	     {
							 KEY_DelayNS(200);
		           	      if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //再延时，若读数还为0，继续延时
			        	     {
							   KEY_DelayNS(300);
		              	     if(((IOPIN&KC0)==0)||((IOPIN&KC1)==0))	      //再延时，若读数还为0，说明是长按
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

			 while(((IOPIN&KC0)==0)||((IOPIN&KC1)==0));	        //直到按键没被按下,才退出函数，避免一次按下被多次检测到
			    
				IODIR |=KC0+KC1; 								 //返回KEY_CLICKED，同时重置列线为输出口
			   return KEY_CLICKED;
			   
			 }			   
			 else										
			 {IODIR |=KC0+KC1;return KEY_UNCLICKED;}			 //返回KEY_UNCLICKED，同时重置列线为输出口
	 
	 	}
		 else
		 {IODIR |=KC0+KC1;return KEY_UNCLICKED;}				 //返回KEY_UNCLICKED，同时重置列线为输出口

}

/****************************************************************************
*                      函数名: KEY_SendKeyValue_whichKey();   
*                      返回类型：INT8U  表示哪个按键被按下的宏定义
*                      参数说明：无参数
*                      功能：将键值1（哪个键被按下）发送给HI模块
******************************************************************************/

INT8U KEY_SendKeyValue_whichKey()
{
   		 return KEY_keyValue_whichKey;	    //已在KEY_IfClicked()中被赋值
}

/****************************************************************************
*                     函数名: KEY_SendKeyValue_LongOrShort();   
*                     返回类型：BOOLEAN  表示是长按还是短按的宏定义
*                     参数说明：无参数
*                     功能：将键值2（长按还是短按）发送给HI模块
******************************************************************************/

BOOLEAN KEY_SendKeyValue_LongOrShort()
{
   		return KEY_keyValue_LongOrShort;         //已在KEY_IfClicked()中被赋值
}

 

 /***********************************************************************************
 *
 *								END OF FILE
 *
 *************************************************************************************/

