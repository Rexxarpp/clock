#include "display.h"
#include "hc595.h"
#include "delay.h"


//hc505 控制2803 NPN型达林顿管驱动 共阳极数码管 高电平选中
//数码管段码与595引脚关系如下：
//段码-----------595引脚---字节中的位置
// A----------------QC---------3
// B----------------QD---------4
// C----------------QG---------7
// D----------------QF---------6
// E----------------QE---------5
// F----------------QB---------2
// G----------------QA---------1
//时钟冒号----------QH---------8

//数码管段码位置如下
//    ===A====
//    =      =
//    =F     =B
//    =      =
//    ===G====
//    =      =
//    =E     =C
//    =      =
//    ===D====  DP

unsigned char code seg_code1[] = 
	{0x7E, 0x48, 0x3D, 0x6D, 0x4B, 0x67, 0x77, 0x4C, 0x7F, 0x6F,  0x5F, 0x73, 0x36, 0x79, 0x37, 0x17, //0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F
     0xFE, 0xC8, 0xBD, 0xED, 0xCB, 0xE7, 0xF7, 0xCC, 0xFF, 0xEF,  0xDF, 0xF3, 0xB6, 0xF9, 0xB7, 0x97};//带时钟冒号的0～9


//位选与595引脚对应关系
//位选-----595引脚---字节中的位置
//   S1------QG---------7
//   S2------QF---------6
//   S3------QE---------5
//   S4------QD---------4
//s8550pnp型三极管，低电平为选中
unsigned char code place_code[] = {0xBF, 0xDF, 0xEF, 0xF7};//S1, S2, S3, S4 时钟冒号的位选与S2相同

unsigned char displayBuf[] = {1, 2, 4, 5};

//两个定时时钟的显示缓存
unsigned char displayBuf1[] = {0, 0, 0, 0, 0, 0};
unsigned char displayBuf2[] = {0, 0, 0, 0, 0, 0};

//两个定时时钟数码管段码与595引脚关系如下：
//段码-----------595引脚---字节中的位置
// A----------------QF---------6
// B----------------QG---------7
// C----------------QA---------1
// D----------------QB---------2
// E----------------QC---------3
// F----------------QE---------5
// G----------------QD---------4
//时钟冒号----------QH---------8

//两个定时时钟使用
unsigned char code seg_code1[] = 
	{0xF7, 0xC1, 0xEE, 0xEB, 0xD9, 0xBB, 0xBF, 0xE1, 0xFF, 0xFB, 0xFD, 0x9F, 0xB6, 0xCF, 0xBE, 0xBC};
	//0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F 所有都带时钟冒号
	
//s8550pnp型三极管，低电平为选中
unsigned char code place_code1[] = {0xBF, 0xDF, 0xEF, 0xF7};//S1, S2, S3, S4, S5, S6

//参数not_display_place表示不显示的位，传0、1、2、3分别不显示1、2、3、4位。如果全部显示，传4好了
void display(unsigned char not_display_place)
{
	//1、送位选
	//2、送段码
	//3、延时
	//4、消隐：将所有段位关闭
	static unsigned char i = 0;
	if(i != not_display_place)
	{
		hc_595_write_two_byte(0x00, 0xff);//4、消隐：将所有段位关闭 先做消隐，再显示。这样字符显示的时间长，亮度高
		hc_595_write_two_byte(seg_code[displayBuf[i]], place_code[i]);//高位是段码，低位是位码 单片机直连位选595
	}
	else
	{
		hc_595_write_two_byte(0x00, 0xff);//4、消隐：将所有段位关闭 先做消隐，再显示。这样字符显示的时间长，亮度高
		hc_595_write_two_byte(seg_code[displayBuf[i]], 0xff);
	}

	i++;
	i = i%4;
//	delay_xms(1);//定时器中调用不用延时

}
