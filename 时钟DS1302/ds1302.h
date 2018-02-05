#ifndef __DS1302_H
#define __DS1302_H

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
	#include"intrins.h"
sbit DS1302_SCK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

 /****定义结构体****/
struct STime{
	uint year;                      //年
	uchar mon;                      //月
	uchar day;                      //日
	uchar hour;                     //小时
	uchar min;                      //分
	uchar sec;                      //秒
	uchar week;                     //星期
};

void InitDS1302();
uchar DS1302_ByteRead();
uchar DS1302_SingleRead(uchar reg);
void DS1302_SingleWrite(uchar reg,uchar dat);
void DS1302_ByteWrite(uchar dat);
void DS1302_BurstWrite(uchar *dat);
void DS1302_BurstRead(uchar *dat);
void GetRealTime(struct STime *time);
void SetRealTime(struct STime *time);

#endif