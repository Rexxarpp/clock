#ifndef __KEY_H__
#define __KEY_H__

#include "STC89C5xRC.H"

#define KEY_NORMAL 0
#define KEY_SET_PRESSED 1
#define KEY_ADJ_PRESSED 2

sbit set_key = P1^0;
sbit adj_key = P3^6;

sbit l_key = P1^2;//��߶�ʱ���İ���
sbit r_key = P3^5;//�ұ߶�ʱ���İ���

unsigned char key_scan();
#endif