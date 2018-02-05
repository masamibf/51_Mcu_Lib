#include"1602.h"
	

/**********检测Lcd是否忙**********/
void LcdWriteReady()
{
	uchar sta;                                
	LCD1602_DB=0xFF;                          
	LCD1602_RS=0;                             
	LCD1602_RW=1;
	do                                         
  {
		LCD1602_E=1;
		sta=LCD1602_DB;
		LCD1602_E=0;
	}while(sta&0x80);                       
}

/**********Lcd写命令函数**********/
void LcdWriteCmd(uchar cmd)
{
	LcdWriteReady();                           
	LCD1602_RS=0;                             
	LCD1602_RW=0;
	LCD1602_DB=cmd;
	LCD1602_E=1;
	LCD1602_E=0;
}

/**********Lcd初始化函数**********/
void InitLcd1602()
{
	LcdWriteCmd(0x38);                         
	LcdWriteCmd(0x0c);                        
	LcdWriteCmd(0x06);                      
	LcdWriteCmd(0x01);  
}

/**********Lcd设置初始光标**********/
void LcdSetCursor(uchar x,uchar y)          
{
	uchar addr;
	if(y==0)
	{
		addr=0x00+x;                         
	}
	else
	{
		addr=0x40+x;                             
	}
	LcdWriteCmd(addr|0x80);                   
}

/**********Lcd写数据函数**********/
void LcdWriteDat(uchar dat)
{
	LcdWriteReady();                           
	LCD1602_RS=1;                             
	LCD1602_RW=0;
	LCD1602_DB=dat;
	LCD1602_E=1;
	LCD1602_E=0;
}

/**********Lcd显示字符串函数**********/
void LcdShowStr(uchar x,uchar y,uchar *str)
{
	LcdSetCursor(x,y);                         //设置起始坐标
	while(*str!='\0')                          //当字符串没有结束时连续写入
	{
		LcdWriteDat(*str++);                     //先取str指向的数据 再将str+1
	}
}

/**********Lcd显示数据函数**********/
void LcdShowDat(uchar x,uchar y,uchar num)
{
	LcdSetCursor(x,y);
	LcdWriteDat(num);
}

/**********打开光标显示**************/
void LcdOpenCursor()
{
	LcdWriteCmd(0x0F);
}

/**********关闭光标显示**************/
void LcdCloseCursor()
{
	LcdWriteCmd(0x0C);
}

