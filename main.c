#include "STC89C5xRC.H"
#include "display.h"
#include "hc595.h"
#include "key.h"
#include "delay.h"
#include "ds1302.h"

enum STATE{SYS_NORMAL = 0, SYS_SET_1 = 1, SYS_SET_2 = 2, SYS_SET_3 = 3, SYS_SET_4 = 4};
extern unsigned char displayBuf[4];
extern unsigned char code seg_code[32];
extern unsigned char time_buf[8];
extern unsigned char time_buf1[8];
unsigned char key_state = KEY_NORMAL;
enum STATE sys_state = SYS_NORMAL;
unsigned char key_need_scan = 0;// �Ƿ񵽴��ʱ���趨�ģ�ɨ�谴�� ��ʱ��
unsigned char time_need_read = 0;//�Ƿ񵽴��ʱ���趨�ģ���ȡds1302���� ��ʱ��
unsigned char not_disp_place = 4;

void TimerInit(void);
void Timer0Init(void);	
void time_format(unsigned char* src, unsigned char* dest);

void key_process();

void main()
{
	//TODO set the right pin
	hc_595_setPin(P2^7, P2^6, P2^5);
	hc_595_init();
	//TODO set the right pin
	hc_595_setPin(P2^7, P2^6, P2^5);
	hc_595_init();
	//TODO set the right pin
	hc_595_setPin(P2^7, P2^6, P2^5);
	hc_595_init();
	
	TimerInit();
//	ds1302_init();
	ds1302_burst_init();
//	ds1302_burst_read(time_buf);//�ȶ�һ��

//	Timer0Init();
	while(1)
	{
		key_process();
		if(time_need_read)
		{
//			ds1302_read(time_buf);//��ͨ��ʽ������buf,������д����λ
//			ds1302_burst_read(time_buf);//burst��ʽ��ȡ����buf ,����д����λ
			time_buf[1] = ds1302_read_byte(0x83);//��ͨ��ʽ����
			time_buf[2] = ds1302_read_byte(0x85);//��ͨ��ʽ��ʱ
			
			
			time_format(time_buf, displayBuf);
			time_need_read = 0;
		}
	}
	
}
void time_format(unsigned char* src, unsigned char* dest) //��BCD���ʱ��ת������ʾ��ʱ��,����dest��
{
	dest[0] = src[2] >> 4;
	dest[1] = (dest[1] &0x10) | (src[2] & 0x0F);
	dest[2] = src[1] >> 4;
	dest[3] = src[1] & 0x0f;
}

void time_format_reverse(unsigned char* src, unsigned char* dest)//����ʾ��ʱ��ת����BCD���ʱ��, ����dest��
{
	dest[2] = (src[0]<<4) | (src[1] & 0x0F);
	dest[1] = (src[2]<<4) | (src[3] & 0x0F);
}


void TimerInit(void)		//1����@12.000MHz
{
//	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x18;		//���ö�ʱ��ֵ
	TH1 = 0xFC;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	
	ET1 = 1;  //��ʱ������1����ж��������λ
	EA = 1;
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}

//void Timer0Init(void)		//3����@12.000MHz
//{
////	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
//	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
//	TMOD |= 0x01;		//���ö�ʱ��ģʽ
//	TL0 = 0x48;		//���ö�ʱ��ֵ
//	TH0 = 0xF4;		//���ö�ʱ��ֵ
//	TF0 = 0;		//���TF0��־
//	
//	ET0 = 1;  //��ʱ������1����ж��������λ
//	EA = 1;
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
//}



void timer1_ISR(void) interrupt 3 //interrupt 3ΪT1�ж�
{
	static unsigned int a = 1;
	TL1 = 0x18;		//���ö�ʱ��ֵ 1����@12.000MHz
	TH1 = 0xFC;		//���ö�ʱ��ֵ

	if( a%8 == 0)
	{
		key_need_scan = 1;
	}
	if((sys_state == SYS_NORMAL))
	{
		if(a%20 == 0)
		{
			time_need_read = 1;
		}		
	}
	if (a++ == 500)   //����ʱ�ķ���
	{
		switch(sys_state)
		{
			case SYS_NORMAL:
				not_disp_place = 4;
				displayBuf[1] ^= 0x10;
				break;
			
			case SYS_SET_1:
				if (not_disp_place !=0)
				{
					not_disp_place = 0;
				}
				else
				{
					not_disp_place = 4;
				}
				break;
				
			case SYS_SET_2:
				displayBuf[1] &= 0x0f;
				if (not_disp_place !=1)
				{
					not_disp_place = 1;
				}
				else
				{
					not_disp_place = 4;
				}
				break;
				
			case SYS_SET_3:
				if (not_disp_place !=2)
				{
					not_disp_place = 2;
				}
				else
				{
					not_disp_place = 4;
				}
				break;
				
			case SYS_SET_4:
				if (not_disp_place !=3)
				{
					not_disp_place = 3;
				}
				else
				{
					not_disp_place = 4;
				}
				break;
				
			default:
				break;
		}
		
		a = 1;
	}
	display(not_disp_place);
	display_timer();	
}


//void timer0_ISR(void) interrupt 1 //interrupt 1ΪT0�ж�
//{
//	static unsigned char b = 0;
//	TR0 = 0;
//	TL0 = 0x48;		//���ö�ʱ����ֵ 3����@12.000MHz
//	TH0 = 0xF4;    //���ö�ʱ����ֵ 3����@12.000MHz
//	key_need_scan = 1; //3����ɨ��һ�ΰ���
//	if(b++ == 20) //100�����ȡһ��ds1302ʱ��
//	{
//		time_need_read = 1;
//		b=0;
//	}
//	TR0 = 1;

//}	
	

void key_process()
{
	if(key_need_scan == 1)
	{
		key_state = key_scan();
		switch(key_state)
		{
			case KEY_SET_PRESSED:
				if(sys_state == SYS_SET_4)
				{
					sys_state = SYS_NORMAL;
					//�����õ�ʱ�����ݻ�дds1302
					time_format_reverse(displayBuf, time_buf1);
					ds1302_write_byte(0x8E, 0x00);  //�ر�д����
					ds1302_burst_write(time_buf1);					
				}
				else if(sys_state == SYS_SET_1)
				{
					sys_state++;
					if(displayBuf[0] == 2)
					{
						if((displayBuf[1] | 0x0F) > 3)
						{
							displayBuf[1] = 0;
						}
					}	
				}
				else
				{
					sys_state++;
				}
				break;
			case KEY_ADJ_PRESSED:
				switch(sys_state)
				{
					case SYS_SET_1:
						displayBuf[0]++;
						displayBuf[0] %= 3;
						break;
					case SYS_SET_2:
						displayBuf[1] &= 0x0f;
						displayBuf[1]++;
						if (displayBuf[0] == 2)
						{
							displayBuf[1] %= 4;
						}
						else
						{
							displayBuf[1] %= 10;
						}
						break;
					case SYS_SET_3:
						displayBuf[2]++;
						displayBuf[2] %= 6;
						break;
					case SYS_SET_4:
						displayBuf[3]++;
						displayBuf[3] %= 10;
						break;
					default:
						break;
				}
				break;
				default:
				break;
			}
			key_need_scan = 0;
		}
}

