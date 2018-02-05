//**********************Disigned By F H X***************************//
//*********************4位独立按键扫描程序**************************//
//*****1 按键驱动函数 ：检测按键动作 执行 mian.c 中按键动作函数*****//
//*****2 按键扫描函数 ：扫描按键状态 在main.c 中的中断函数被调用****//


#include "key.h"

uchar code KeyCodeMap[4] = {0x1B,0x26,0x0D,0x28,};         // ASCⅡ键值 : ESC键 向上键 回车键 向下键 
uchar KeySta[4] = {1,1,1,1};                              // 按键当前状态 默认为弹起
ulong pdata KeyDownTime[4] = {0,0,0,0};                   // 按键按下时间 默认为0

extern void KeyDown(uchar keycode);

/**********按键驱动函数**********/
void KeyDrive()
{
	uchar i;
	static uchar backup[4] = {1,1,1,1};                     //保存上次按键状态 默认都为弹起
	static ulong pdata TimeTh[4] = {1000,1000,1000,1000};   //按键按下时间阈值 超过阈值则为长按模式
	for(i=0;i<4;i++)
	{
		if(backup[i]!=KeySta[i])                              //检测按键动作
		{
			if(KeySta[i]==0)                                    //按键被按下	
			{
				KeyDown(KeyCodeMap[i]);                           //执行按键动作函数
			}
			backup[i]=KeySta[i];                                //保存当前按键状态
		}
    if(KeyDownTime[i]>0)                                  //检测按键按下时间
		{
			if(KeyDownTime[i]>=TimeTh[i])                       //按键按下时间大于阈值 执行按键动作函数
			{
				KeyDown(KeyCodeMap[i]);
				TimeTh[i]+=200;                                   //阈值自增
			}
		}
		else 
		{
			TimeTh[i]=1000;                                     //按键弹起时恢复阈值时间
		}
	}
}

/**********按键扫描函数**********/
void KeyScan()
{
	uchar i;
	static uchar Keybuff[4]={0xFF,0xFF,0xFF,0xFF};          //按键扫描缓冲区
	
	Keybuff[0]=(Keybuff[0]<<1)|KEY_1;                       //逐个扫描4个独立按键 起到延时消抖作用
	Keybuff[1]=(Keybuff[1]<<1)|KEY_2;
	Keybuff[2]=(Keybuff[2]<<1)|KEY_3;
	Keybuff[3]=(Keybuff[3]<<1)|KEY_4;
	for(i=0;i<4;i++)
	{
		if((Keybuff[i]&0x0F)==0x00)                           //检测到某个按键被按下
		{
			KeySta[i]=0;                                        //改变该按键状态
			KeyDownTime[i]+=4;                                  //该按键按下时间累加
		}
		else if((Keybuff[i]&0x0F)==0x0F)                      //检测到某个按键弹起
		{
			KeySta[i] = 1;                                      //改变该按键状态
      KeyDownTime[i] = 0;                                 //该按键按下时间清零
		}
  }
}