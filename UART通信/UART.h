#ifndef __UATR_H__
#define __UART_H__


#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
	


extern void UART_Action(uchar *buf,uchar len);

void ConfigUART(uint baud);
void UART_Write(uchar *buf,uchar len);
signed char UART_Read(uchar *buf,uchar len);
void UART_RX_Monitor(uchar ms);
void UART_Driver();


#endif