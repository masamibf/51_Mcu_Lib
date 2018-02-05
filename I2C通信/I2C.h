#ifndef __I2C_H__
#define __I2C_H__

#include "reg52.h"
#include "intrins.h"

#define I2CDelay()  {_nop_();_nop_();_nop_();_nop_();}
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
	
void I2C_Start();
void I2C_Stop();
bit I2C_Write(uchar dat);
uchar I2CReadACK();
uchar I2CReadNAK();
bit I2C_Addresing(uchar addr);

#endif