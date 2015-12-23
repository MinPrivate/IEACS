;/****************************************Copyright (c)**************************************************
;**                              		南蛮入侵开发组
;**
;**--------------File Info-------------------------------------------------------------------------------
;** File Name: IRQ.s
;** Last modified Date:  2004-06-14
;** Last Version: 1.1
;** Descriptions: The irq handle that what allow the interrupt nesting. 
;**
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/


		    INCLUDE		..\Include\irq.inc			; Inport the head file 引入头文件

    CODE32
			 PRESERVE8

    AREA    IRQ,CODE,READONLY


;/* 以下添加中断句柄，用户根据实际情况改变 */
;/* Add interrupt handler here，user could change it as needed */

;/*中断*/
;/*Interrupt*/
IRQ_Handler	HANDLER IRQ_Exception


;/*定时器0中断*/
;/*Time0 Interrupt*/
Timer0_Handler  HANDLER Timer0_Exception

    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
