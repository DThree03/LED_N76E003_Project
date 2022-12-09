#ifndef	_FLASH_EEPROM_H__
#define	_FLASH_EEPROM_H__

typedef bit                   BIT;
typedef unsigned char         UINT8;
typedef unsigned int          UINT16;
typedef unsigned long         UINT32;

typedef unsigned char         uint8_t;
typedef unsigned int          uint16_t;
typedef unsigned long         uint32_t;

unsigned char  read_APROM_BYTE(unsigned int code *u16_addr);

void write_DATAFLASH_BYTE(unsigned int u16EPAddr,unsigned char u8EPData);

extern bit BIT_TMP;

#endif
