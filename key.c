#include "key.h"
#include "delay.h"

unsigned char key_scan()
{
	unsigned char return_value = KEY_NORMAL;
	if (0 == set_key)
	{
//		delay_xms();
		if(0 == set_key)
		{
			return_value = KEY_SET_PRESSED;
			while(!set_key);
		}

	}
	else if(0 == adj_key)
	{
//		delay_xms();
		if(0 == adj_key)
		{
			return_value = KEY_ADJ_PRESSED;
			while(!adj_key);
		}
		
	}
	
	else if(0 == l_key)
	{
//		delay_xms();
		if(0 == l_key)
		{
			return_value = KEY_TIMER_L_PRESSED;
			while(!l_key);
		}
		
	}
	
	else if(0 == r_key)
	{
//		delay_xms();
		if(0 == r_key)
		{
			return_value = KEY_TIMER_R_PRESSED;
			while(!r_key);
		}
		
	}
	
	
	return return_value;
}