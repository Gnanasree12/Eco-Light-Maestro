//rtc.c
#include <LPC21xx.H>
#include "rtc_defines.h"
#include   "types.h"
#include "lcd.h"

char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// RTC Initialization: Configures and enables the RTC
void RTC_Init(void) 
{
  // Reset the RTC
	CCR = RTC_CTC_RESET;	
  // Set prescaler integer part
	PREINT = PREINT_VAL;
  // Set prescaler fractional part
	PREFRAC = PREFRAC_VAL;
	/*
  // Enable the RTC for LPC2129
	CCR = RTC_CCR_EN;
	*/
	// Enable the RTC for LPC2148 with external clock source
	CCR = RTC_CCR_EN | RTC_CLKSRC;
}

void RTCGetTime(u32 *hr,u32 *mi,u32 *se)
{
	*hr = HOUR;
	*mi = MIN;
	*se = SEC;	
}

void DisplayRTCTime(u32 hr,u32 mi,u32 se)
{
	//SetCursor(1,0);
	cmdLCD(0x80);
	charLCD((hr/10)+48);
	charLCD((hr%10)+48);
	charLCD(':');
	charLCD((mi/10)+48);
	charLCD((mi%10)+48);
	charLCD(':');
	charLCD((se/10)+48);
	charLCD((se%10)+48);	
}

void RTCGetDate(u32 *dt,u32 *mo,u32 *yr)
{
	*dt = DOM;
	*mo = MONTH;
	*yr = YEAR;	
}

void DisplayRTCDate(u32 dt,u32 mo,u32 yr)
{
	cmdLCD(0xC0);
	//SetCursor(2,0);
	charLCD((dt/10)+48);
	charLCD((dt%10)+48);
	charLCD('/');
	charLCD((mo/10)+48);
	charLCD((mo%10)+48);
	charLCD('/');
	U32LCD(yr);	
}

void RTCGetDay(u32 *day)
{
	*day = DOW;
}
void DisplayRTCDay(u32 day)
{
	cmdLCD(0x8A);
	//SetCursor(1,10);
	strLCD(week[day]);	
}

void RTCSetTime(u32 hr,u32 mi,u32 se)
{
	HOUR = hr;
	MIN = mi;
	SEC = se;
}
void RTCSetDate(u32 dt,u32 mo,u32 yr)
{
	DOM = dt;
	MONTH = mo;
	YEAR = yr;
}
void RTCSetDay(u32 day)
{
	DOW = day;
}

