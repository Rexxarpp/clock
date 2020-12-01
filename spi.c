#include "spi.h"

//void spi_write_byte(unsigned char dat)
//{
//	unsigned char i;
//	for(i = 0; i < 8; i++)
//	{
//		IO = dat & 0x01;
//		dat >>= 1;
//		SCLK = 1;
//		SCLK = 0;		
//	}
//}

void spi_write_byte(unsigned char dat)
{
//	unsigned char i = 5;
	IO = dat & 0x01;
//	while(i--);
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
	
	IO = dat & 0x01;
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
	
	IO = dat & 0x01;
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
	
	IO = dat & 0x01;
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
	
	IO = dat & 0x01;
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
	
	IO = dat & 0x01;
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
	
	IO = dat & 0x01;
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
	
	IO = dat & 0x01;
	dat >>= 1;
	SCLK = 1;
	SCLK = 0;
}

//unsigned char spi_read_byte()
//{
//	unsigned char ret = 0;
//	unsigned char i;
//	for (i = 0x01; i != 0; i <<= 1)
//	{
//		if(0 != IO)
//		{
//			ret |= i;
//		}
//		SCLK = 1;
//		SCLK = 0;
//	}
//	return ret;
//}

unsigned char spi_read_byte()
{
	unsigned char ret = 0;

	ret |= (unsigned char)IO;
	SCLK = 1;
	SCLK = 0;
	
	ret |= ((unsigned char)IO << 1);
	SCLK = 1;
	SCLK = 0;
	
	ret |= ((unsigned char)IO << 2);
	SCLK = 1;
	SCLK = 0;
	
	ret |= ((unsigned char)IO << 3);
	SCLK = 1;
	SCLK = 0;
	
	ret |= ((unsigned char)IO << 4);
	SCLK = 1;
	SCLK = 0;
	
	ret |= ((unsigned char)IO << 5);
	SCLK = 1;
	SCLK = 0;
	
	ret |= ((unsigned char)IO << 6);
	SCLK = 1;
	SCLK = 0;
	
	ret |= ((unsigned char)IO << 7);
	SCLK = 1;
	SCLK = 0;
	
	return ret;
}