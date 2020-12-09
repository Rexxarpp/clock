#ifndef __HC595_H__
#define __HC595_H__
#include "STC89C5xRC.H"

sbit HC595_SH_CLK = P2^7; //"��λʱ��"
sbit HC595_ST_CLK = P2^6; //���洢ʱ�ӡ�
sbit HC595_DS = P2^5; //�������ߡ�

void hc_595_setPin(sbit sh_clk, sbit st_clk, ds);
//��ʼ��
void hc_595_init();

//����λ�Ĵ����е����ݴ���洢�Ĵ�������ʾ
void hc_595_stor_data();

//����λ�Ĵ�����д��1�ֽڣ�����ʾ
void hc_595_write_byte(unsigned char dat);

//����λ�Ĵ�����д��2�ֽڣ�����ʾ
void hc_595_write_two_byte(unsigned char dat_h, unsigned char dat_l);

#endif