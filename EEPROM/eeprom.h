#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "reg52.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
	

uchar E2ReadByte(uchar addr);
void E2WriteByte(uchar addr,uchar dat);
void E2P_Read(uchar *buf,uchar addr,uchar len);
void E2P_Write(uchar *buf,uchar addr,uchar len);

#endif