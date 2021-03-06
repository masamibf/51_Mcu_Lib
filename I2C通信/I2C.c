#include"I2C.h"

/***********************************************I2C启动函数*******************************************************/
/*                                            产生总线起始信号                                                   */
/*****************************************************************************************************************/
void I2C_Start()
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2CDelay();
	I2C_SDA = 0;
	I2CDelay();
	I2C_SCL = 0;
}

/************************************************I2C停止函数******************************************************/
/*                                             产生总线停止信号                                                  */
/*****************************************************************************************************************/
void I2C_Stop()
{
	I2C_SCL = 0;
	I2C_SDA = 0;
	I2CDelay();
	I2C_SCL = 1;
	I2CDelay();
	I2C_SDA = 1;
	I2CDelay();
}

/************************************************I2C总线写操作函数************************************************/
/*                                      dat：待写入字节  返回从机的应答值                                        */
/*****************************************************************************************************************/
bit I2C_Write(uchar dat)
{
	bit ack = 0;
	uchar mask;
	for(mask=0x80; mask!=0; mask>>=1)               //将mask按位与dat 从高位到低位依次判断dat每一位的值
	{
		if((mask&dat) == 0)                           //若值为0 则拉低SDA 若为1则拉高SDA
			I2C_SDA = 0;
		else
			I2C_SDA = 1;
		I2CDelay();
		I2C_SCL = 1;
		I2CDelay();
		I2C_SCL = 0;
	}
	I2C_SDA = 1;
	I2CDelay();
	I2C_SCL = 1;
	ack = I2C_SDA;
	I2CDelay();
	I2C_SCL = 0;

	return (~ack);
}

/************************************************I2C总线读操作函数************************************************/
/*                                           发送应答信号 并返回 读到的字节                                      */
/*****************************************************************************************************************/
uchar I2CReadACK()
{
	uchar mask;
	uchar dat;
	I2C_SDA=1;                                  //确保主机释放SDA
	for(mask=0x80;mask!=0;mask>>=1)
	{
		I2CDelay();
		I2C_SCL=1;                                //拉高SCL
		if(I2C_SDA==0)
			dat&=~mask;                             //SDA为0时 dat对应位清零
		else
			dat|=mask;
		I2CDelay();
		I2C_SCL=0;                                //拉低SCL 使从机发送下一位
	}
	I2C_SDA=0;                                  //8位数据发送完后 拉低SDA 发送应答信号
	I2CDelay();
	I2C_SCL=1;                                  //拉高SCL
	I2CDelay();
	I2C_SCL=0;                                  //再拉低SCL 完成应答位 保持住总线
	return dat;
}

/************************************************I2C总线读操作函数************************************************/
/*                                           发送非应答信号 并返回 读到的字节                                    */
/*****************************************************************************************************************/
uchar I2CReadNAK()
{
	uchar mask;
	uchar dat;
	I2C_SDA=1;
	for(mask=0x80;mask!=0;mask>>=1)
	{
		I2CDelay();
		I2C_SCL=1;
		if(I2C_SDA==0)
			dat&=~mask;
		else
			dat|=mask;
		I2CDelay();
		I2C_SCL=0;
	}
	I2C_SDA=1;
	I2CDelay();
	I2C_SCL=1;
	I2CDelay();
	I2C_SCL=0;
	return dat;
}

/************************************************I2C寻址函数******************************************************/
/*                                 检查地址为addr的器件是否存在   返回从器件的应答值                             */
/*****************************************************************************************************************/
bit I2C_Addresing(uchar addr)
{
	bit ack = 0;
	I2C_Start();                                     //产生起始位  启动一次总线操作
	ack = I2C_Write(addr << 1);                      //器件地址需要左移一位 因为地址是7位 最低位为读写位 
                                                   //用于表示之后的操作是读还是写
  I2C_Stop();                                      //不需要进行后续的读写 停止本次总线操作
	return ack;
}
