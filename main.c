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
unsigned char key_need_scan = 0;// 是否到达（定时器设定的）扫描按键 的时间
unsigned char time_need_read = 0;//是否到达（定时器设定的）读取ds1302数据 的时间
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
//	ds1302_burst_read(time_buf);//先读一次

//	Timer0Init();
	while(1)
	{
		key_process();
		if(time_need_read)
		{
//			ds1302_read(time_buf);//普通方式读整个buf,不包括写保护位
//			ds1302_burst_read(time_buf);//burst方式读取整个buf ,包括写保护位
			time_buf[1] = ds1302_read_byte(0x83);//普通方式读分
			time_buf[2] = ds1302_read_byte(0x85);//普通方式读时
			
			
			time_format(time_buf, displayBuf);
			time_need_read = 0;
		}
	}
	
}
void time_format(unsigned char* src, unsigned char* dest) //把BCD码的时间转换成显示的时间,放入dest中
{
	dest[0] = src[2] >> 4;
	dest[1] = (dest[1] &0x10) | (src[2] & 0x0F);
	dest[2] = src[1] >> 4;
	dest[3] = src[1] & 0x0f;
}

void time_format_reverse(unsigned char* src, unsigned char* dest)//把显示的时间转换成BCD码的时间, 放入dest中
{
	dest[2] = (src[0]<<4) | (src[1] & 0x0F);
	dest[1] = (src[2]<<4) | (src[3] & 0x0F);
}


void TimerInit(void)		//1毫秒@12.000MHz
{
//	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	
	ET1 = 1;  //定时计数器1溢出中断允许控制位
	EA = 1;
	TR1 = 1;		//定时器1开始计时
}

//void Timer0Init(void)		//3毫秒@12.000MHz
//{
////	AUXR &= 0x7F;		//定时器时钟12T模式
//	TMOD &= 0xF0;		//设置定时器模式
//	TMOD |= 0x01;		//设置定时器模式
//	TL0 = 0x48;		//设置定时初值
//	TH0 = 0xF4;		//设置定时初值
//	TF0 = 0;		//清除TF0标志
//	
//	ET0 = 1;  //定时计数器1溢出中断允许控制位
//	EA = 1;
//	TR0 = 1;		//定时器0开始计时
//}



void timer1_ISR(void) interrupt 3 //interrupt 3为T1中断
{
	static unsigned int a = 1;
	TL1 = 0x18;		//设置定时初值 1毫秒@12.000MHz
	TH1 = 0xFC;		//设置定时初值

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
	if (a++ == 500)   //长定时的方法
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


//void timer0_ISR(void) interrupt 1 //interrupt 1为T0中断
//{
//	static unsigned char b = 0;
//	TR0 = 0;
//	TL0 = 0x48;		//设置定时器初值 3毫秒@12.000MHz
//	TH0 = 0xF4;    //设置定时器初值 3毫秒@12.000MHz
//	key_need_scan = 1; //3毫秒扫描一次按键
//	if(b++ == 20) //100毫秒读取一次ds1302时间
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
					//将设置的时间数据回写ds1302
					time_format_reverse(displayBuf, time_buf1);
					ds1302_write_byte(0x8E, 0x00);  //关闭写保护
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

