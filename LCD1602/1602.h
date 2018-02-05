#ifndef  __1602_H
#define  __1602_H

#include<reg52.h>
#define LCD1602_DB P0
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
	
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_E = P2^7;

void LcdWriteCmd(uchar cmd);
void InitLcd1602();
void LcdSetCursor(uchar x,uchar y);
void LcdWriteDat(uchar dat);
void LcdShowStr(uchar x,uchar y,uchar *str);
void LcdOpenCursor();
void LcdCloseCursor();
void LcdShowDat(uchar x,uchar y,uchar num);
#endif