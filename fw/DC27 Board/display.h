/*
 * display.h
 *
 * Created: 7/10/2019 19:14:20
 *  Author: tiltmesenpai
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <hal_delay.h>
#include <hal_ext_irq.h>
#include <hal_i2c_m_sync.h>
#include <external/u8g2.h>

// Screen defines
#define SCN_WIDTH 32
#define SCN_HEIGHT 128

extern struct i2c_m_sync_desc I2C_0;
void initDisplay(u8g2_t*);
void iota(char*, uint32_t);


#endif /* DISPLAY_H_ */