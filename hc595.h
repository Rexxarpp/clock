#ifndef __HC595_H__
#define __HC595_H__
#include "STC89C5xRC.H"

sbit HC595_SH_CLK = P2^7; //"��λʱ��"
sbit HC595_ST_CLK = P2^6; //���洢ʱ�ӡ�
sbit HC595_DS = P2^5; //�������ߡ�

sbit HC595_SH_CLK_L = P1^3; //"��λʱ��"  ���
sbit HC595_ST_CLK_L = P1^1; //���洢ʱ�ӡ�
sbit HC595_DS_L = P1^4; //�������ߡ�

sbit HC595_SH_CLK_R = P2^2; //"��λʱ��"  �ұ�
sbit HC595_ST_CLK_R = P2^1; //���洢ʱ�ӡ�
sbit HC595_DS_R = P2^0; //�������ߡ�

	
	
//��ʼ��
void hc_595_init();

//����λ�Ĵ����е����ݴ���洢�Ĵ�������ʾ
void hc_595_stor_data();
void hc_595_stor_data_L();
void hc_595_stor_data_R();

//����λ�Ĵ�����д��1�ֽڣ�����ʾ
void hc_595_write_byte(unsigned char dat);
void hc_595_write_byte_L(unsigned char dat);
void hc_595_write_byte_R(unsigned char dat);

//����λ�Ĵ�����д��2�ֽڣ�����ʾ
void hc_595_write_two_byte(unsigned char dat_h, unsigned char dat_l);
void hc_595_write_two_byte_L(unsigned char dat_h, unsigned char dat_l);
void hc_595_write_two_byte_R(unsigned char dat_h, unsigned char dat_l);

#endif