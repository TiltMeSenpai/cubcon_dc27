/*
 * display.c
 *
 * Created: 7/10/2019 19:14:42
 *  Author: tiltmesenpai
 */ 
#include <display.h>
uint8_t u8x8_byte_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	static uint8_t buffer[32];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
	static uint8_t buf_idx;
	uint8_t *data;
	
	switch(msg)
	{
		case U8X8_MSG_BYTE_SEND:
		data = (uint8_t *)arg_ptr;
		while( arg_int > 0 )
		{
			buffer[buf_idx++] = *data;
			data++;
			arg_int--;
		}
		break;
		case U8X8_MSG_BYTE_INIT:
			i2c_m_sync_enable(&I2C_0);
		/* add your custom code to init i2c subsystem */
		break;
		case U8X8_MSG_BYTE_SET_DC:
		/* ignored for i2c */
		break;
		case U8X8_MSG_BYTE_START_TRANSFER:
			buf_idx = 0;
			i2c_m_sync_set_slaveaddr(&I2C_0, 0x3c, I2C_M_SEVEN);
		break;
		case U8X8_MSG_BYTE_END_TRANSFER:
			io_write(&I2C_0.io, buffer, buf_idx);
		break;
		default:
		return 0;
	}
	return 1;
}

uint8_t u8x8_gpio_and_delay_stm32l0(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:   
      break;
    case U8X8_MSG_DELAY_NANO:
      /* not required for SW I2C */
      break;
    
    case U8X8_MSG_DELAY_10MICRO:
      /* not used at the moment */
      break;
    
    case U8X8_MSG_DELAY_100NANO:
      /* not used at the moment */
      break;  
    case U8X8_MSG_DELAY_MILLI:
      delay_ms(arg_int);
      break;
    case U8X8_MSG_DELAY_I2C:
      /* arg_int is 1 or 4: 100KHz (5us) or 400KHz (1.25us) */
      //delay_micro_seconds(arg_int<=2?5:1);
      break;
    
    case U8X8_MSG_GPIO_I2C_CLOCK:
    case U8X8_MSG_GPIO_I2C_DATA:
    case U8X8_MSG_GPIO_MENU_SELECT:
      break;
    case U8X8_MSG_GPIO_MENU_NEXT:
      break;
    case U8X8_MSG_GPIO_MENU_PREV:
      break;
    case U8X8_MSG_GPIO_MENU_HOME:
      break;
    default:
      u8x8_SetGPIOResult(u8x8, 1);
      break;
  }
  return 1;
}

static const uint32_t u8toa_tab[10]  = {1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 } ;


/* v = value, d = number of digits */
void iota(char *buf, uint32_t v)
{
	uint8_t pos;
	uint8_t d;
	uint32_t c;
	for( pos = 0; pos < 10; pos++ )
	{
		d = '0';
		c = u8toa_tab[pos];
		while( v >= c )
		{
			v -= c;
			d++;
		}
		buf[pos] = d;
	}
	buf[10] = '\0';
}

/*
  Setup u8g2
  This must be executed only after POR reset.
*/
void initDisplay(u8g2_t *disp)
{
  /* setup display */
  u8g2_Setup_ssd1306_i2c_128x32_univision_f(disp, U8G2_R2, u8x8_byte_i2c, u8x8_gpio_and_delay_stm32l0);
  u8g2_InitDisplay(disp);
  u8g2_SetPowerSave(disp, 0);
  u8g2_SetFont(disp, u8g2_font_5x8_tf);
  u8g2_ClearBuffer(disp);
  u8g2_SendBuffer(disp);
}