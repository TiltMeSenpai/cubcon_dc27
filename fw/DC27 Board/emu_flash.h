/*
 * emu_flash.h
 *
 * Created: 7/7/2019 10:49:01
 *  Author: tiltmesenpai
 */ 


#ifndef EMU_FLASH_H_
#define EMU_FLASH_H_

#define SPI_RESET_EN   0x66
#define SPI_RESET_MEM  0x99
#define SPI_READ_ID    0x9E
#define SPI_SFDP       0x5A
#define SPI_READ       0x03
#define SPI_WRITE_EN   0x06
#define SPI_WRITE_DIS  0x04
#define SPI_READ_STAT  0x05
#define SPI_WRITE_STAT 0x01
#define SPI_READ_LOCK  0xE8
#define SPI_WRITE_LOCK 0xE5



#endif /* EMU_FLASH_H_ */