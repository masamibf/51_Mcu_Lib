#ifndef __DS18B20_H
#define __DS18B20_H

#include"reg52.h"
#include<intrins.h>
#define	uchar unsigned char
#define	uint unsigned int
	

//sbit DS18B20_DQ = P1^5;
sbit DS18B20_DQ = P3^7;

bit	RESET_DS18B20(void);
void Write_DS18B20_DATA(uchar Value);
uchar Read_DS18B20_DATA(void);
uint Read_DS18B20_TEMP(void);
void Delay_Us(uchar i);

#endif