#ifndef __HC595_H__
#define __HC595_H__
#include "STC89C5xRC.H"

sbit HC595_SH_CLK = P2^7; //"移位时钟"
sbit HC595_ST_CLK = P2^6; //“存储时钟”
sbit HC595_DS = P2^5; //“数据线”

sbit HC595_SH_CLK_L = P1^3; //"移位时钟"  左边
sbit HC595_ST_CLK_L = P1^1; //“存储时钟”
sbit HC595_DS_L = P1^4; //“数据线”

sbit HC595_SH_CLK_R = P2^2; //"移位时钟"  右边
sbit HC595_ST_CLK_R = P2^1; //“存储时钟”
sbit HC595_DS_R = P2^0; //“数据线”

	
	
//初始化
void hc_595_init();

//将移位寄存器中的数据存入存储寄存器以显示
void hc_595_stor_data();
void hc_595_stor_data_L();
void hc_595_stor_data_R();

//向移位寄存器中写入1字节，不显示
void hc_595_write_byte(unsigned char dat);
void hc_595_write_byte_L(unsigned char dat);
void hc_595_write_byte_R(unsigned char dat);

//向移位寄存器中写入2字节，并显示
void hc_595_write_two_byte(unsigned char dat_h, unsigned char dat_l);
void hc_595_write_two_byte_L(unsigned char dat_h, unsigned char dat_l);
void hc_595_write_two_byte_R(unsigned char dat_h, unsigned char dat_l);

#endif