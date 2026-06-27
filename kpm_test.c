//kpm_test_2.c
#include "kpm.h"
#include "defines.h"
#include <LPC21xx.h>
u8 keyV;
int main()
{
	//cfg p1.24 to p1.31 as gpio out pins
  WRITEBYTE(IODIR1,24,0xFF);	
	InitKPM();
	while(1)
	{
		keyV=KeyScan();
		WRITEBYTE(IOPIN1,24,keyV);
		while(ColScan()==0);
	}
}
