#include <lpc2103.h>
#include "..\Include\config.h"
#define BPS  115200


void UART_Init(void)
{  
		INT16U fdiv;
		fdiv = (Fpclk/16)/BPS;
		PINSEL0= (PINSEL0&~0x00050005)|0x00050005; 
    U1LCR=0x83;                       
    U1DLL=fdiv&0xFF;                          
    U1DLM=(fdiv>>8)&0xFF;                       
    U1LCR=0x03;                       

    U0LCR=0x83;                       
    U0DLL=fdiv&0xFF;
    U0DLM=(fdiv>>8)&0xFF;
    U0LCR=0x03;
}

/*******************************************************************************
*??: UART_SendByte()
*??: ?????????,???????
*******************************************************************************/

void UART_SendByte(INT8U data,INT8U num)
{   
    if(num==0)
    {
        U0THR=data;                      //???????
        while((U0LSR&0x20)==0);          //????????    
    }

    if(num==1)
    {
        U1THR=data;                      //???????
        while((U1LSR&0x20)==0);          //????????    
    }    
}

/*******************************************************************************
*??:UART_SendStr()
*??:?????????
*******************************************************************************/

void UART_SendStr(INT8U *str,INT8U num)
{  
    while(1)
    { 
        if(*str=='\0') 
        {
            if(num==0)
            {
                UART_SendByte('\r',0);
                UART_SendByte('\n',0);
            }
            if(num==1)
            {
                UART_SendByte('\r',1);
                UART_SendByte('\n',1);
            }
            break;
        } 
        if(num==0)
            UART_SendByte(*str++,0);           //????
        if(num==1)
            UART_SendByte(*str++,1);           //????
    }
}

/*******************************************************************************
*??:UART1_RecvByte()
*??:????????
*******************************************************************************/

INT8U UART1_RecvByte(void)
{  
    while(!(U1LSR&0x01));
    return U1RBR;                              //???????
}

