#include "ds1302.h"
#include "spi.h"
#include "delay.h"

// 秒 分 时 日 月 周 年 写保护  充电
unsigned char code write_cmd[] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C, 0x8E, 0x90};
//秒 分 时 日 月 周 年
unsigned char code read_cmd[] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8B, 0x8D};

//写入ram第一字节中的数据，用来判断系统是否掉过电
unsigned char code protect_code = 0x9D;

//  秒 分 时 日 月 周 年 写保护
//BCD码表示 2020-09-14 8:58:12 7
unsigned char time_buf[8] = {0x12, 0x58, 0x08, 0x14, 0x09, 0x07, 0x20, 0x80};
unsigned char time_buf1[8] = {0x00, 0x58, 0x08, 0x14, 0x09, 0x07, 0x20, 0x80}; //回写ds1302时用，不用上面那个是防止回写时被定时器改写

#define BURST_WRITE 0xBE
#define BURST_READ 0xBF

extern unsigned char displayBuf[4];

void ds1302_init()
{
	unsigned char i = 0;
	unsigned char read_protect_code;
	read_protect_code = ds1302_read_byte(0xC1);//0xC1 读取ram第一字节中的数据的命令
	if(protect_code != read_protect_code)
	{
		ds1302_write_byte(write_cmd[7], 0x00);//关闭写保护
		ds1302_write_byte(0xC0, protect_code);	//向ram第一字节中写入保护字
		ds1302_write_byte(write_cmd[8], 0xA5);//充电，一个二极管，2K电阻
		for (i = 0; i < 8; i++)
		{
			ds1302_write_byte(write_cmd[i], time_buf[i]); //最后一次循环打开写保护
		}		
	}

}

void ds1302_burst_init()
{
	unsigned char read_protect_code;
	read_protect_code = ds1302_read_byte(0xC1);//0xC1 读取ram第一字节中的数据的命令
	if(protect_code != read_protect_code)
	{		
		ds1302_write_byte(write_cmd[7], 0x00);//关闭写保护
		ds1302_write_byte(0xC0, protect_code);	//向ram第一字节中写入保护字
		ds1302_write_byte(write_cmd[8], 0xA5);//充电，0xAA两个二极管，4K电阻	0xA5 一个二极管，2K电阻
		ds1302_burst_write(time_buf); //初始化时间
	}	
}




void ds1302_read(unsigned char* buf)
{
	unsigned char i = 0;
	for (; i < 7; i++)
	{
		buf[i] = ds1302_read_byte(read_cmd[i]);
	}
}

void ds1302_write_byte(unsigned char cmd, unsigned char dat)
{
	CE = 0;
	SCLK = 0;
	CE = 1;
	spi_write_byte(cmd);
	spi_write_byte(dat);
	CE = 0;
}

unsigned char ds1302_read_byte(unsigned char cmd)
{
	unsigned char dat;
	IO = 0;//要加这句，不然读出的数据一次正常，一次不正常，读出0x7f,网上说他们读出oxff。
	//https://bbs.csdn.net/topics/390207271
	CE = 0;
	SCLK = 0;
	CE = 1;
	spi_write_byte(cmd);
	dat = spi_read_byte();
	CE = 0;

	return dat;
}

//burst模式，一次性写入8字节，命令是0xBE. buf[7]必须是0x80，以打开写保护
//此函数不会关闭写保护，但会打开写保护，在调用此函数前需要手动关闭写保护
void ds1302_burst_write(unsigned char* buf)
{
	unsigned char i = 0;
	CE = 0;
	SCLK = 0;
	CE = 1;
	spi_write_byte(BURST_WRITE);//burst写命令
	for(; i < 8; i++)
	{
		spi_write_byte(buf[i]); //最后一次循环打开写保护
	}
	CE = 0;
}



void ds1302_burst_read(unsigned char* buf)
{
	unsigned char i = 0;
	CE = 0;
	SCLK = 0;
	CE = 1;
	spi_write_byte(BURST_READ);//burst读命令
	for(; i < 8; i++)
	{
		buf[i] = spi_read_byte();
	}
	CE = 0;
	IO = 0;//要加这句，不然读出的数据一次正常，一次不正常，读出0x7f,网上说他们读出oxff。
}


unsigned char read1302(unsigned char add)
{
	unsigned char i, dat, dat1;
	SCLK = 0;
	CE = 0;
	CE = 1;
	for(i = 0; i < 8; i++)
	{
		IO = add&0x01;
		add>>=1;
		SCLK = 1;
		SCLK = 0;
	}
	for(i = 0; i < 8; i++)
	{
		dat1 = IO;
		dat = (dat>>1)|(dat1<<7);
		SCLK = 1;
		SCLK = 0;
	}
	CE = 0;
	IO = 0;
	return dat;
}