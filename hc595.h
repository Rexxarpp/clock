#ifndef __HC595_H__
#define __HC595_H__
#include "STC89C5xRC.H"

sbit HC595_SH_CLK = P2^7; //"移位时钟"
sbit HC595_ST_CLK = P2^6; //“存储时钟”
sbit HC595_DS = P2^5; //“数据线”

void hc_595_setPin(sbit sh_clk, sbit st_clk, ds);
//初始化
void hc_595_init();

//将移位寄存器中的数据存入存储寄存器以显示
void hc_595_stor_data();

//向移位寄存器中写入1字节，不显示
void hc_595_write_byte(unsigned char dat);

//向移位寄存器中写入2字节，并显示
void hc_595_write_two_byte(unsigned char dat_h, unsigned char dat_l);

#endif