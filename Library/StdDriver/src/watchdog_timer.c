#include "watchdog_timer.h"
#include "Function_define.h"

void Check_WDT_Reset_Config(void)
{
	set_IAPEN;
	IAPAL = 0x04;
	IAPAH = 0x00;	
	IAPFD = 0xFF;
	IAPCN = 0xC0;						//Read config command
	set_IAPGO;  
	if ((IAPFD&0xF0)==0xF0)
	{
		IAPFD = 0x0F;
		IAPCN = 0xE1;
		set_IAPGO;                         						//trigger IAP
		while((CHPCON&SET_BIT6)==SET_BIT6);          //check IAPFF (CHPCON.6)
		clr_CFUEN;
		clr_IAPEN;
		EA = 0;
		TA = 0xAA;
		TA = 0x55;
		CHPCON &= 0xFD;
		TA = 0xAA;
		TA = 0x55;
		CHPCON |= 0x80;
	}
	clr_IAPEN;
}
char WatchDog_Timer_Init(void)
{
	signed char stt = 0;
	Check_WDT_Reset_Config();
	TA=0xAA;TA=0x55; stt = WDCON&0x08;
	
	if(stt==0x08){
		TA=0xAA;TA=0x55;WDCON&=0xF7;
	}
	
	TA=0xAA;TA=0x55;WDCON|=0x07;				//Setting WDT prescale 
	set_WDCLR;									//Clear WDT timer
	while((WDCON|~SET_BIT6)==0xFF);				//confirm WDT clear is ok before into power down mode
	set_WDTR;
	return stt;
}
