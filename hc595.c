#include "hc595.h"


void hc_595_init()
{
	HC595_SH_CLK = 0;
	HC595_ST_CLK = 0;
}

//����λ�Ĵ����е����ݴ���洢�Ĵ�������ʾ
void hc_595_stor_data()
{
	HC595_ST_CLK = 1;
	HC595_ST_CLK = 0;
}

//����λ�Ĵ�����д��1�ֽڣ�����ʾ

void hc_595_write_byte(unsigned char dat)
{
	char i; //�˴�������unsigned char ����ѭ������ֹͣ���޿ӣ�������
	for(i = 7; i >= 0; i--)
	{
		HC595_DS = (dat >> i) & 0x01;
		HC595_SH_CLK = 0;
		HC595_SH_CLK = 1;		
	}
	/*
	//��Ƶ�������˵ķ���
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

//����λ�Ĵ�����д��2�ֽڣ�����ʾ
void hc_595_write_two_byte(unsigned char dat_h, unsigned char dat_l)
{
	hc_595_write_byte(dat_h);
	hc_595_write_byte(dat_l);
	hc_595_stor_data();
}