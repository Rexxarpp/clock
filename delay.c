#include "delay.h"

//毫秒级延时，参数unsigned char (1-127)

void delay_xms(void)		//@12.000MHz  xms<=127!!
{
	unsigned char i, j;

	i = 9;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}