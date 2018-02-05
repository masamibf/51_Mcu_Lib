#ifndef __SMG_H__
#define __SMG_H__

#include "reg52.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
	
#define SMGDUAN P0                        //宏定义控制数码管段选的端口为P0
#define SMGWEI P2                         //宏定义控制数码管位选的端口为P2（P2低三位P2.0 P2.1 P2.2）



void LedScan();
void LedShowNum(ulong num);
void Timer0Init(uint ms);

#endif