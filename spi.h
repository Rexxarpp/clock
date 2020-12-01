#ifndef __SPI_H__
#define __SPI_H__
#include "STC89C5xRC.H"

sbit SCLK = P1^5;
sbit IO = P1^6;
sbit CE = P1^7;

void spi_write_byte(unsigned char dat);
unsigned char spi_read_byte();
#endif