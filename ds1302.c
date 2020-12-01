#include "ds1302.h"
#include "spi.h"
#include "delay.h"

// �� �� ʱ �� �� �� �� д����  ���
unsigned char code write_cmd[] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C, 0x8E, 0x90};
//�� �� ʱ �� �� �� ��
unsigned char code read_cmd[] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8B, 0x8D};

//д��ram��һ�ֽ��е����ݣ������ж�ϵͳ�Ƿ������
unsigned char code protect_code = 0x9D;

//  �� �� ʱ �� �� �� �� д����
//BCD���ʾ 2020-09-14 8:58:12 7
unsigned char time_buf[8] = {0x12, 0x58, 0x08, 0x14, 0x09, 0x07, 0x20, 0x80};
unsigned char time_buf1[8] = {0x00, 0x58, 0x08, 0x14, 0x09, 0x07, 0x20, 0x80}; //��дds1302ʱ�ã����������Ǹ��Ƿ�ֹ��дʱ����ʱ����д

#define BURST_WRITE 0xBE
#define BURST_READ 0xBF

extern unsigned char displayBuf[4];

void ds1302_init()
{
	unsigned char i = 0;
	unsigned char read_protect_code;
	read_protect_code = ds1302_read_byte(0xC1);//0xC1 ��ȡram��һ�ֽ��е����ݵ�����
	if(protect_code != read_protect_code)
	{
		ds1302_write_byte(write_cmd[7], 0x00);//�ر�д����
		ds1302_write_byte(0xC0, protect_code);	//��ram��һ�ֽ���д�뱣����
		ds1302_write_byte(write_cmd[8], 0xA5);//��磬һ�������ܣ�2K����
		for (i = 0; i < 8; i++)
		{
			ds1302_write_byte(write_cmd[i], time_buf[i]); //���һ��ѭ����д����
		}		
	}

}

void ds1302_burst_init()
{
	unsigned char read_protect_code;
	read_protect_code = ds1302_read_byte(0xC1);//0xC1 ��ȡram��һ�ֽ��е����ݵ�����
	if(protect_code != read_protect_code)
	{		
		ds1302_write_byte(write_cmd[7], 0x00);//�ر�д����
		ds1302_write_byte(0xC0, protect_code);	//��ram��һ�ֽ���д�뱣����
		ds1302_write_byte(write_cmd[8], 0xA5);//��磬0xAA���������ܣ�4K����	0xA5 һ�������ܣ�2K����
		ds1302_burst_write(time_buf); //��ʼ��ʱ��
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
	IO = 0;//Ҫ����䣬��Ȼ����������һ��������һ�β�����������0x7f,����˵���Ƕ���oxff��
	//https://bbs.csdn.net/topics/390207271
	CE = 0;
	SCLK = 0;
	CE = 1;
	spi_write_byte(cmd);
	dat = spi_read_byte();
	CE = 0;

	return dat;
}

//burstģʽ��һ����д��8�ֽڣ�������0xBE. buf[7]������0x80���Դ�д����
//�˺�������ر�д�����������д�������ڵ��ô˺���ǰ��Ҫ�ֶ��ر�д����
void ds1302_burst_write(unsigned char* buf)
{
	unsigned char i = 0;
	CE = 0;
	SCLK = 0;
	CE = 1;
	spi_write_byte(BURST_WRITE);//burstд����
	for(; i < 8; i++)
	{
		spi_write_byte(buf[i]); //���һ��ѭ����д����
	}
	CE = 0;
}



void ds1302_burst_read(unsigned char* buf)
{
	unsigned char i = 0;
	CE = 0;
	SCLK = 0;
	CE = 1;
	spi_write_byte(BURST_READ);//burst������
	for(; i < 8; i++)
	{
		buf[i] = spi_read_byte();
	}
	CE = 0;
	IO = 0;//Ҫ����䣬��Ȼ����������һ��������һ�β�����������0x7f,����˵���Ƕ���oxff��
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