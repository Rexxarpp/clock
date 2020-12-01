#include "hc595.h"


void hc_595_init()
{
	HC595_SH_CLK = 0;
	HC595_ST_CLK = 0;
}

//将移位寄存器中的数据存入存储寄存器以显示
void hc_595_stor_data()
{
	HC595_ST_CLK = 1;
	HC595_ST_CLK = 0;
}

//向移位寄存器中写入1字节，不显示

void hc_595_write_byte(unsigned char dat)
{
	char i; //此处不能用unsigned char 否则循环不能停止。巨坑！！！！
	for(i = 7; i >= 0; i--)
	{
		HC595_DS = (dat >> i) & 0x01;
		HC595_SH_CLK = 0;
		HC595_SH_CLK = 1;		
	}
	/*
	//视频中其他人的方法
	for(i = 0; i < 8; i++)
	{
		if(dat < 0x80)
		{
			HC595_DS = 0;
		}
		else
		{
			HC595_DS = 1;
		}
		HC595_SH_CLK = 1;
		HC595_SH_CLK = 0;
		
		dat <<= 1;
		
	}
*/
}

//向移位寄存器中写入2字节，并显示
void hc_595_write_two_byte(unsigned char dat_h, unsigned char dat_l)
{
	hc_595_write_byte(dat_h);
	hc_595_write_byte(dat_l);
	hc_595_stor_data();
}