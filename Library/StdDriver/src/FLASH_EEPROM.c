/****************************************************************************************************/		
#include "FLASH_EEPROM.h"

#include "Function_define.h"

volatile unsigned char xdata page_buffer[128];

//-------------------------------------------------------------------------
unsigned char  read_APROM_BYTE(unsigned int code *u16_addr)
{
	unsigned char rdata;
	rdata = *u16_addr>>8;
	return rdata;
}
void write_DATAFLASH_BYTE(unsigned int u16EPAddr,unsigned char u8EPData)
{
unsigned char looptmp=0;
  unsigned int u16_addrl_r;
  unsigned int RAMtmp;
  
//Check page start address
  u16_addrl_r = (u16EPAddr/128)*128;
//Save APROM data to XRAM0
  for(looptmp=0;looptmp<0x80;looptmp++)
  {
    RAMtmp = (unsigned char)read_APROM_BYTE((unsigned int code *)(u16_addrl_r+looptmp));
    page_buffer[looptmp]=RAMtmp;
  }
// Modify customer data in XRAM
  page_buffer[u16EPAddr&0x7f] = u8EPData;
  
//Erase APROM DATAFLASH page
    IAPAL = u16_addrl_r&0xff;
    IAPAH = (u16_addrl_r>>8)&0xff;
    IAPFD = 0xFF;
    set_IAPEN; 
    set_APUEN;
    IAPCN = 0x22;     
     set_IAPGO; 
    
//Save changed RAM data to APROM DATAFLASH
    set_IAPEN; 
    set_APUEN;
    IAPCN = 0x21;
    for(looptmp=0;looptmp<0x80;looptmp++)
    {
      IAPAL = (u16_addrl_r&0xff)+looptmp;
      IAPAH = (u16_addrl_r>>8)&0xff;
      IAPFD = page_buffer[looptmp];
      set_IAPGO;      
    }
    clr_APUEN;
    clr_IAPEN;
}	
