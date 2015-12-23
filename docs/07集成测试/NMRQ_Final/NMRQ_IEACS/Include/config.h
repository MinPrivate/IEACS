;/****************************************Copyright (c)**************************************************
;**                              		�������ֿ�����
;**                                                                 
**--------------File Info-------------------------------------------------------------------------------
********************************************************************************************************/
#ifndef __CONFIG_H 
#define __CONFIG_H
//��һ������Ķ�
//This segment should not be modified
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/********************************/
/*      uC/OS-II specital code  */
/*      uC/OS-II���������      */
/********************************/

#define     USER_USING_MODE    0x10                    /*  User mode ,ARM 32BITS CODE �û�ģʽ,ARM����                  */
// 
                                                     /*  Chosen one from 0x10,0x30,0x1f,0x3f.ֻ����0x10,0x30,0x1f,0x3f֮һ       */
#include "Includes.h"


/********************************/
/*      ARM���������           */
/*      ARM specital code       */
/********************************/
//��һ������Ķ�
//This segment should not be modify

#include    "LPC2103.h"
#include    "LCD240160.h"


/********************************/
/*     Ӧ�ó�������             */
/*Application Program Configurations*/
/********************************/
//���¸�����Ҫ�Ķ�
//This segment could be modified as needed.
#include    <stdio.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <setjmp.h>
#include    <rt_misc.h>


/********************************/
/*     �����ӵ�����             */
/*Configuration of the example */
/********************************/
/* System configuration .Fosc��Fcclk��Fcco��Fpclk must be defined */
/* ϵͳ����, Fosc��Fcclk��Fcco��Fpclk���붨��*/
#define Fosc            11059200                    //Crystal frequence,10MHz~25MHz��should be the same as actual status. 
						    //Ӧ����ʵ��һ������Ƶ��,10MHz~25MHz��Ӧ����ʵ��һ��
#define Fcclk           (Fosc * 4)                  //System frequence,should be (1~32)multiples of Fosc,and should be equal or less  than 60MHz. 
						    //ϵͳƵ�ʣ�����ΪFosc��������(1~32)����<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCO frequence,should be 2��4��8��16 multiples of Fcclk, ranged from 156MHz to 320MHz. 
						    //CCOƵ�ʣ�����ΪFcclk��2��4��8��16������ΧΪ156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 1             //VPB clock frequence , must be 1��2��4 multiples of (Fcclk / 4).
						    //VPBʱ��Ƶ�ʣ�ֻ��Ϊ(Fcclk / 4)��1��2��4��

#include    "target.h"              //This line may not be deleted ��һ�䲻��ɾ��
//#include    "..\..\Arm_Pc\pc.h"

#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
