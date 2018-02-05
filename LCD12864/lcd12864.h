#ifndef __LCD12864_H__
#define __LCD12864_H__

#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

/****************************************************************************/
//TS12864并口相关设定//
sbit MPU_RS_CH=P1^5;						//寄存器选择输入
sbit MPU_RW_CH=P1^6; 					//读写控制
sbit MPU_ENABLE=P1^7;						//使能控制
#define	LCD_DATA	P0							//液晶数据口
//-----------------------------------------------
#define	OFF			0							//逻辑关
#define	ON			1							//逻辑开
//-----------------------------------------------

	//0x01					//清显示指令
	//0x06					//设置输入模式
	//0x0c					//设置开显控制
	//0x30					//功能设定(基本指令)
	//0x34					//功能设定(扩充指令)
	//0x36					//设置绘图功能

//子程序声明
//void procKey (void);

void LcdInit (void);

void LcdClear (void);

void LcdWriteCmd (uchar cmd); 

void LcdWriteDat (uchar dat); 

void LcdCheckBusy(void); 

void LcdShowPhoto1(uchar *img);

void LcdShowPhoto2(uchar *img);

void LcdShowPhoto3(uchar x,uchar y,uchar sign,uchar tt);

void write1616GDRAM(uchar x,uchar y,uchar sign,uchar *bmp);

void ConvertChar (uchar CX,uchar CY,uchar width); 

void LcdSetCursor (void);

void LcdShowStr (uchar X,uchar Y,uchar speed,uchar *msg);

//void init_dz();

void Clear_img();
#endif