#include "smg.h"

uchar code SmgDuan[] = {                  //数码管断选
     0x3F,0x06,0x5B,0x4F,0x66,
     0x6D,0x7D,0x07,0x7F,0x6F
}; 

uchar SmgWei[8] = {                       //数码管位选
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 
};

uchar T0RH = 0;
uchar T0RL = 0;

/***********************************************************************/
/*                           数码管扫描函数                            */
/***********************************************************************/
void LedScan()
{
	static uchar i=0;                         //位选索引值
	SMGDUAN = 0x00;                           //消隐
  SMGWEI  =(SMGWEI&0xF8)|i;                 //位选索引值赋值给P1低三位（改变38译码器）
	SMGDUAN = SmgWei[i];                      //位选数据输送到P0
	if(i<8)i++;                               //索引值自增
	else i=0;
}

/***********************************************************************/
/*                           数码管显示函数                            */
/*                   形参num  当num=0 数码管显示数字0                  */
/***********************************************************************/
void LedShowNum(ulong num)
{
	signed int i=0;                         
	uchar buff[8];                          
	for(i=0;i<=7;i++)                        //将长整型num转化为8位十进制数组
	{
		buff[i]=num%10;
		num=num/10;
	}
	for(i=7;i>=1;i--)                        //从最高位开始 遇到0则不显示 非0则退出
	{
		if(buff[i]==0)
		  SmgWei[7-i]=0x00;
		else
			break;
	}
	for(;i>=0;i--)                           //剩余低位转化为数码管显示字符
	{
		SmgWei[7-i]=SmgDuan[buff[i]];
	}
}

/**********定时器0初始化函数**********/
/*******形参ms 当ms=1 定时1毫秒*******/
void Timer0Init(uint ms)
{
	ulong tmp;                              //16位长整型变量tmp
	tmp=12000000/12;                        //用晶振频率除以12得到定时器计数频率
	tmp=(tmp*ms)/1000;                      //计算出需要多少个机器周期
	tmp=65536-tmp;                          //定时器的初始值
	tmp=tmp+18;                             //补偿中断延时响应造成的误差
	T0RH=(uchar)(tmp>>8);                   //将tmp高8位右移8位 赋值给T0RH
	T0RL=(uchar)tmp;                        //将tmp低8位赋值给T0RL
	TMOD&=0xF0;                             //TMOD高4位不变 低四位清零
	TMOD|=0x01;                             //TMOD低四位变成0001
	TH0=T0RH;                               //装载初值
	TL0=T0RL;
	ET0=1;                                  //开启定时器0中断          
	TR0=1;                                  //开启定时器0
}

/**********定时器0中断函数**********/
/*********1毫秒进入一次中断*********/
void InterruptTimer0() interrupt 1
{
	TH0=T0RH;                               //重载初值
	TL0=T0RL;
	LedScan();                              //数码管扫描
}
