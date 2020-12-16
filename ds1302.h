#ifndef __DS1302_H__
#define __DS1302_H__

void ds1302_init();
void ds1302_read(unsigned char* buf);
void ds1302_write_byte(unsigned char cmd, unsigned char dat);
unsigned char ds1302_read_byte(unsigned char cmd);
unsigned char read1302(unsigned char add);

void ds1302_burst_write(unsigned char* buf);
//”√burst∑Ω Ωinit
void ds1302_burst_init();
void ds1302_burst_read(unsigned char* buf);
void ds1302_burst_write_ram(unsigned char* buf, unsigned char write_len);
void ds1302_burst_read_ram(unsigned char* buf, unsigned char read_len);
unsigned char check_protect_code(unsigned char* buf1, unsigned char* buf2, unsigned char len);
#endif