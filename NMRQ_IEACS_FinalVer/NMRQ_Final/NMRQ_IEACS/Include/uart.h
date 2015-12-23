#ifndef __UART_H__
#define __UART_H__
#include "config.h"
void UART_Init(void);
void UART_SendByte(INT8U data,INT8U num);
void UART_SendStr(INT8U *str,INT8U num);
INT8U UART1_RecvByte(void);

#endif
