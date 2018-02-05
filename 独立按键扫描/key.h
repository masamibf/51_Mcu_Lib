#ifndef __KEY_H__
#define __KEY_H__

#include "reg52.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
	
sbit KEY_1 = P2^4;
sbit KEY_2 = P2^5;
sbit KEY_3 = P2^6;
sbit KEY_4 = P2^7;

//sbit KEY_1 = P1^0;
//sbit KEY_2 = P1^1;
//sbit KEY_3 = P1^2;
//sbit KEY_4 = P1^3;


void KeyDrive();
void KeyScan();

#endif