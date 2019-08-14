/*
 * knock_knock.c
 *
 * Created: 7/17/2019 19:44:09
 *  Author: tiltmesenpai
 */ 

#include <app.h>
#include <hal_gpio.h>

#define GATHER_PINS_BOT(gpio) (((gpio >> 5) & 0b1111111) | (gpio_get_pin_level(PIN_PA16) ? (1 << 7) : 0 ))

static const uint32_t pin_top[] = {
	PIN_PA27,
	PIN_PA25,
	PIN_PA24,
	PIN_PA23,
	PIN_PA22,
	PIN_PA19,
	PIN_PA18,
	PIN_PA17,
};

static const uint32_t pin_bot[] = {
	PIN_PA05,
	PIN_PA06,
	PIN_PA07,
	PIN_PA08,
	PIN_PA09,
	PIN_PA10,
	PIN_PA11,
	PIN_PA16,
};



static uint8_t on_state, curr_level;
static uint16_t frametick_ctr, ge_reset_ctr;

void frametick_knock(u8g2_t *disp){
	
}
void click_knock(u8g2_t *disp){
}

void init_knock(u8g2_t* disp){
	curr_level = 0;
	u8g2_SetFont(disp, u8g2_font_5x7_tf);
	u8g2_ClearBuffer(disp);
	u8g2_DrawStr(disp, 0, 16, "Super Secret ;)");
	u8g2_SendBuffer(disp);
}