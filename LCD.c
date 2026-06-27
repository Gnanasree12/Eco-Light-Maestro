//lcd.c
#include <LPC21xx.h>
#include  "defines.h"
#include "delay.h"
#include "types.h"
#include "lcd_defines.h"

void writeLCD(u8 Dat)
{
	WBYTE(IOPIN0,LCD_DATA,Dat);
	SSETBIT(IOSET0,LCD_EN);
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN);
	delay_ms(2);
}

void cmdLCD(u8 cmd)
{
	SCLRBIT(IOCLR0,LCD_RS);
	writeLCD(cmd);
}

void charLCD(u8 asciiVal)
{
  SSETBIT(IOSET0,LCD_RS);
  writeLCD(asciiVal);	
}

void InitLCD(void)
{
	IODIR0|=0xFF<<LCD_DATA|1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
	delay_ms(15);
	cmdLCD(0x30);
	delay_ms(5);
	cmdLCD(0x30);
	delay_us(100);
	cmdLCD(0x30);
	cmdLCD(MODE_8BIT_2LINE);
	cmdLCD(DSP_ON_CUR_OFF);
	cmdLCD(CLEAR_LCD);
	cmdLCD(SHIFT_CUR_RIGHT);
}

void strLCD(s8 *p)
{
	while(*p)
		charLCD(*p++);
}

void U32LCD(u32 n)
{
	s32 i=0;
	u8 a[10];
	if(n==0)
	{
		charLCD('0');
	}
  else
  {
		while(n!=0)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		{
			charLCD(a[i]);
		}
  }		
}

void S32LCD(s32 n)
{
	if(n<0)
	{
		charLCD('-');
		n=-n;
	}
	U32LCD(n);
}

void F32LCD(f32 f,u32 nDP)
{
	u32 n,i;
	if(f<0.0)
	{
		charLCD('-');
		f=-f;
	}
	n=f;
	U32LCD(n);
	charLCD('.');
	for(i=0;i<nDP;i++)
	{
		f=(f-n)*10;
		n=f;
		charLCD(n+48);
	}	
}	

void HexLCD(u32 n)
{
	s32 i=0;
	u8 a[8],t;
	if(n==0)
	{
		charLCD('0');
	}
  else
  {
		while(n!=0)
		{
			t=(n%16);
			t=((t>9)?((t-10)+'A'):(t+48));
			a[i++]=t;
			n/=16;
		}
		for(--i;i>=0;i--)
		{
			charLCD(a[i]);
		}
  }
}

void BinLCD(u32 n,u32 nBD)
{
	s32 i;
	for(i=(nBD-1);i>=0;i--)
	   charLCD(RBIT(n,i)+48);
}

void BuildCGRAM(u8 *p,u32 nBytes)
{
	s32 i;
	//point cursor/address pointer to
	//cgram start
	cmdLCD(GOTO_CGRAM_START);
	for(i=0;i<nBytes;i++)
	{
		//write to cgram via data reg
		charLCD(p[i]);		
	}
	//reposition cursor/address pointer to
	//ddram start
	cmdLCD(GOTO_LINE1_POS0);
}
