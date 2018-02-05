#include "lcd12864.h"
#include "ziku.h"
uchar k; //界面
//-----------------------------------------------
uchar xdata lcdPosX, lcdPosY;							//X,Y坐标
uchar xdata halfScr, halfLineCnt, basicBlock;			//半屏,半屏行数,N*8块
//-----------------------------------------------

/*******************************延时函数*************************************/

/****************************************************************************/
//约0.1ms延时函数	(11.0592MHZ)
void Delay100us(uchar x)   
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<10; i++);
	}
}
//延时(毫秒)子程序
//输入参数:毫秒数
void DelayMs (uint ms) 
{
	uchar i;
	while (--ms)
	{
		for (i = 0; i < 125; i++);
	}
}

/********************************清屏函数************************************/
//清除LCD文本屏幕子程序
/****************************************************************************/
void LcdClear (void) 
{
	LcdWriteCmd(0x01);
}
/****************************************************************************/
//写入控制命令到LCD子程序
//输入参数:LCD控制指令
/****************************************************************************/
void LcdWriteCmd(uchar cmd) 
{
	LcdCheckBusy(); 
	MPU_RS_CH = 0;
	MPU_RW_CH = 0;
	LCD_DATA = cmd;
	MPU_ENABLE = 1;
	DelayMs(1);
	MPU_ENABLE = 0;
}

/****************************************************************************/
//写入显示数据到LCD子程序
//输入参数:显示数据
/****************************************************************************/
void LcdWriteDat (uchar dat) 
{
	LcdCheckBusy(); 
	MPU_RS_CH = 1;
	MPU_RW_CH = 0;
	LCD_DATA = dat;
	MPU_ENABLE = 1;
	DelayMs(1);
	MPU_ENABLE = 0;
}
/****************************************************************************/
//检测LCD忙碌子程序
/****************************************************************************/
void LcdCheckBusy(void) 
{
	LCD_DATA = 0xFF;
	MPU_RS_CH = 0;
	MPU_RW_CH = 1;
	MPU_ENABLE = 1;
	while ((LCD_DATA&0x80)==0x80);
	MPU_ENABLE = 0;
}
/**************************************************************************/
//-------------------------------------------
//函数功能:显示128x64图形,适用于st7920型液晶
//-------------------------------------------
//************************************************************************//        

void LcdShowPhoto1(uchar *img)
{
 uchar i,j;
   for(j=0;j<32;j++)			//绘制上半屏
   {
     for(i=0;i<8;i++)
     {
       LcdWriteCmd(0x34);		//0011 0100 扩充功能设定——8位数据 扩充指令操作 绘图开
       LcdWriteCmd(0x80+j);		//1xxx xxxx 设定绘图RAM——先设定垂直(列)地址AC6 AC5…AC0
       LcdWriteCmd(0x80+i);		//1000 0xxx 设定绘图RAM——再设定水平(行)地址AC3AC2AC1AC0
       LcdWriteCmd(0x30);		//0011 0000 扩充功能设定——8位数据 基本指令操作
       LcdWriteDat(img[j*16+i*2]);
       LcdWriteDat(img[j*16+i*2+1]);
     }
   }
   for(j=32;j<64;j++)			//绘制下半屏
   {
     for(i=0;i<8;i++)
     {
       LcdWriteCmd(0x34);		//0011 0100 扩充功能设定——8位数据 扩充指令操作 绘图开
       LcdWriteCmd(0x80+j-32);		//1xxx xxxx 设定绘图RAM——先设定垂直(列)地址AC6 AC5…AC0
       LcdWriteCmd(0x88+i);		//1000 1xxx 设定绘图RAM——再设定水平(行)地址AC3AC2AC1AC0
       LcdWriteCmd(0x30);		//0011 0000 扩充功能设定——8位数据 基本指令操作
       LcdWriteDat(img[j*16+i*2]);
       LcdWriteDat(img[j*16+i*2+1]);
     }
   }
   LcdWriteCmd(0x36);
}

/*************************************************************************/
//-------------------------------------------
//函数功能:显示128x32图形,适用于st7920型液晶
//功能描述    ：下半屏显示图形
//-------------------------------------------
//***********************************************************************//
void LcdShowPhoto2(uchar *img)
{
 uchar i,j;
   for(j=0;j<32;j++)
   {
     for(i=0;i<8;i++)
     {
       LcdWriteCmd(0x34);
       LcdWriteCmd(0x80+j);
       LcdWriteCmd(0x88+i);
       LcdWriteCmd(0x30);
       LcdWriteDat(img[j*16+i*2]);
       LcdWriteDat(img[j*16+i*2+1]);
     }
   }
   LcdWriteCmd(0x36);
}

/**************************************************************************************
//函数功能:显示16X16图形,适用于st7920型液晶
//形式参数:uchar x,uchar y,uchar *bmp
//行参说明:横坐标X列，纵坐标Y行，sign=1反白、=0不反，tt是要显示的图形bmp1616中的第几个
//************************************************************************************/ 
void LcdShowPhoto3(uchar x,uchar y,uchar sign,uchar tt) 
{				//x-列，y-行，sign-反白选择(1不反白,0反白),tt-图画的选择
	uchar (*pp)[32];	 //定义指针
	pp=bmp1616;	  //二维数组首地址给指针，故指针指向下一个数组地址应为加64
	write1616GDRAM(x,y,sign,pp[tt]); //写入小时的十位	  
}


/*使用绘图的方法让一个16*16的汉字符反白------*/
//形式参数:uchar x,uchar y,uchar wide,uchar bkcor
//行参说明:坐标水平位置,坐标垂直位置,反白行数,要反白还是清除(1:反白,0:清除)   
void write1616GDRAM(uchar x,uchar y,uchar sign,uchar *bmp)	
{                  //x-列，y-行，sign-反白选择(1不反白,0反白),bmp-图画的选择
	uchar i,j,basex;
	LcdWriteCmd(0x36);      //扩展指令，绘图模式命令，开显示也可以绘.(关图片显示0x34)
	if(y==1||y==2)	  //第一第二行
	{
		basex=0x80;	   //上半屏
		y=(y-1)*16;	  //垂直位址从0X80开始.
	}
	if(y==3||y==4)	//第三第四行
	{
		basex=0x88;	 //下半屏
		y=(y-3)*16;	 //垂直位址都是从0X80开始的，不管上下半屏。
	}
	for(i=0;i<16;i++)	//
	{															
		LcdWriteCmd(0x80+y+i);  //写入垂直位址。
		LcdWriteCmd(basex+x-1); //再写入水平位址(上半屏第一字为0X80，……第七字为0X87)
							   //下半屏第一字为0X88，……第七字为0X8F；
		for(j=0;j<2;j++)   //再写入两个8位元的数据,AC会自动增一，接着写数据
		{
			if(sign==1)  
				LcdWriteDat(~(*bmp++));
			else  
				LcdWriteDat(*bmp++);
		}
	}	
	LcdWriteCmd(0x36);  //写完数据，开图片显示     
}
/****************************************************************************/
//字符反白显示
//输入参数:CX=要反白字符的行(0-3)
//CY=要反白字符的列(0-7)
//width=要反白字符的长度(1-16)
//****************************************************************************//
void ConvertChar(uchar CX,uchar CY,uchar width) 
{
	//DisplayPhoto(OFF,ON);
	lcdPosY = 0x80;

	if (CX == 0)
	{
		CX = 0x80;
		halfLineCnt = 16;
	}
	else if (CX == 1)
	{
		CX = 0x80;
		halfLineCnt = 32;
	}
	else if (CX == 2)
	{
		CX = 0x88;
		halfLineCnt = 16;
	}
	else if (CX == 3)
	{
		CX = 0x88;
		halfLineCnt = 32;
	}
	lcdPosX = CX + CY;
	
    for (; halfLineCnt != 0; halfLineCnt--)
	{
		basicBlock = width;
		LcdSetCursor();
	
		for (;basicBlock != 0; basicBlock--)
		{
			if (halfLineCnt > 16)
			{
				LcdWriteDat(0x00);
			}
			else
			{
				LcdWriteDat(0xff);
			}
		}
		lcdPosY++;
	}

	LcdWriteCmd(0x36);   //设置绘图功能
	LcdWriteCmd(0x30);	//功能设定(基本指令)
}
/*****************************************/
//坐标写入子程序
/*****************************************/
void LcdSetCursor (void) 
{
	LcdWriteCmd(0x34);      //功能设定(扩充指令)
	LcdWriteCmd(lcdPosY);
	LcdWriteCmd(lcdPosX);
	LcdWriteCmd(0x30);      //功能设定(基本指令)
}
/****************************************************************************/
//显示字符串子程序
//输入参数:X=行(0-3), Y=列(0-7), speed=显示速度(毫秒), msg=字符数据
/****************************************************************************/
void LcdShowStr (uchar X,uchar Y,uchar speed,uchar *msg) 
{
	if (X == 0)
	{
		X = 0x80;
	}
	else if (X == 1)
	{
		X = 0x90;
	}
	else if (X == 2)
	{
		X = 0x88;
	}
	else if (X == 3)
	{
		X = 0x98;
	}
	Y = X + Y;
	LcdWriteCmd(Y);
	while (*msg)
	{
		LcdWriteDat(*msg++);
		DelayMs(speed);
	}
}
/****************************************************************************/
//清理图片缓冲区
/****************************************************************************/
void Clear_img()
{
	uchar i,j;
	for(i=0;i<32;i++)	
	{
		LcdWriteCmd(0x80+i);
		LcdWriteCmd(0x80);									      
		for(j=0;j<16;j++)
		{
			LcdWriteDat(0x00);
		}		
	}
	for(i=0;i<32;i++)
	{
		LcdWriteCmd(0x80+i);
		LcdWriteCmd(0x88);
		for(j=0;j<16;j++)
		{
			LcdWriteDat(0x00);
		}		
	}
}
/****************************************************************************/
//初始化LCD子程序
/****************************************************************************/
void LcdInit (void)
{
	LcdWriteCmd(0x34);
	LcdWriteCmd(0x30);
	LcdClear();
	LcdWriteCmd(0x06);    //设置输入模式
	LcdWriteCmd(0x0C);   	//设置开显控制
	//k=Read24c02(3);
	//if(k==2){Clear_img();LcdClear();
	//}
	//if(k==0){LcdClear(); Clear_img();init_dz();
	//}
	//if(k==1){LcdClear(); Clear_img();init_dz();
	//}
}
