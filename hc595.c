#include "hc595.h"



void hc_595_init()
{
	HC595_SH_CLK = 0;
	HC595_ST_CLK = 0;
	
	HC595_SH_CLK_L = 0;
	HC595_ST_CLK_L = 0;
	
	HC595_SH_CLK_R = 0;
	HC595_ST_CLK_R = 0;
}

//将移位寄存器中的数据存入存储寄存器以显示
void hc_595_stor_data()
{
	HC595_ST_CLK = 1;
	HC595_ST_CLK = 0;
}

void hc_595_stor_data_L()
{	
	HC595_ST_CLK_L = 1;
	HC595_ST_CLK_L = 0;
}

void hc_595_stor_data_R()
{	
	HC595_ST_CLK_R = 1;
	HC595_ST_CLK_R = 0;
}

//向移位寄存器中写入1字节，不显示

void hc_595_write_byte(unsigned char dat)
{
	HC595_DS = dat & 0x80;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
	
	HC595_DS = dat & 0x40;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
	
	HC595_DS = dat & 0x20;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
	
	HC595_DS = dat & 0x10;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
	
	HC595_DS = dat & 0x08;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
	
	HC595_DS = dat & 0x04;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
	
	HC595_DS = dat & 0x02;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
	
	HC595_DS = dat & 0x01;
	HC595_SH_CLK = 0;
	HC595_SH_CLK = 1;
}

void hc_595_write_byte_L(unsigned char dat)
{
	HC595_DS_L = dat & 0x80;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
	
	HC595_DS_L = dat & 0x40;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
	
	HC595_DS_L = dat & 0x20;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
	
	HC595_DS_L = dat & 0x10;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
	
	HC595_DS_L = dat & 0x08;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
	
	HC595_DS_L = dat & 0x04;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
	
	HC595_DS_L = dat & 0x02;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
	
	HC595_DS_L = dat & 0x01;
	HC595_SH_CLK_L = 0;
	HC595_SH_CLK_L = 1;
}

void hc_595_write_byte_R(unsigned char dat)
{
	HC595_DS_R = dat & 0x80;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
	
	HC595_DS_R = dat & 0x40;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
	
	HC595_DS_R = dat & 0x20;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
	
	HC595_DS_R = dat & 0x10;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
	
	HC595_DS_R = dat & 0x08;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
	
	HC595_DS_R = dat & 0x04;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
	
	HC595_DS_R = dat & 0x02;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
	
	HC595_DS_R = dat & 0x01;
	HC595_SH_CLK_R = 0;
	HC595_SH_CLK_R = 1;
}


//void hc_595_write_byte(unsigned char dat)
//{
//	char i; //此处不能用unsigned char 否则循环不能停止。巨坑！！！！
//	for(i = 7; i >= 0; i--)
//	{
//		HC595_DS = (dat >> i) & 0x01;
//		HC595_SH_CLK = 0;
//		HC595_SH_CLK = 1;		
//	}
//	
////	视频中其他人的方法
////	for(i = 0; i < 8; i++)
////	{
////		if(dat < 0x80)
////		{
////			HC595_DS = 0;
////		}
////		else
////		{
////			HC595_DS = 1;
////		}
////		HC595_SH_CLK = 1;
////		HC595_SH_CLK = 0;
////		
////		dat <<= 1;
////		
////	}

//}

//向移位寄存器中写入2字节，并显示
void hc_595_write_two_byte(unsigned char dat_h, unsigned char dat_l)
{
	hc_595_write_byte(dat_h);
	hc_595_write_byte(dat_l);
	hc_595_stor_data();
}

void hc_595_write_two_byte_L(unsigned char dat_h, unsigned char dat_l)
{
	hc_595_write_byte_L(dat_h);
	hc_595_write_byte_L(dat_l);
	hc_595_stor_data_L();
}

void hc_595_write_two_byte_R(unsigned char dat_h, unsigned char dat_l)
{
	hc_595_write_byte_R(dat_h);
	hc_595_write_byte_R(dat_l);
	hc_595_stor_data_R();
}