#ifndef __INFRARED_H__
#define __INFRARED_H__

#include "reg52.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


void InitInfrared();
uint GetHighTime();
uint GetLowTime();
void InfraredDriver();





#endif