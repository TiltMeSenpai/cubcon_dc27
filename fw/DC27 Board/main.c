#include <atmel_start.h>

#include <app_list.h>
#include "apps/menu.h"
#include <display.h>

void show_framecount(void);

static struct timer_task frametick = {0};

void initTick(void);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	// Wait for display controller to safely power on
	delay_ms(100);
	initDisplay(&u8g2);
	initTick();
	launch_app(&menu_app);
	while(1){
		__WFI();
	}
}

void initTick(){
	// Clear the irq flags?? I guess?
	volatile uint32_t flags = hri_eic_read_INTFLAG_reg(EIC_SEC);
	hri_eic_clear_INTFLAG_reg(EIC_SEC, flags);
	
	// Rest of init as normal
	ext_irq_register(PIN_PA04, tilt_up);
	ext_irq_register(PIN_PA03, btn_click);
	ext_irq_register(PIN_PA02, tilt_down);
	frametick.cb = timer_do_tick;
	frametick.interval = 1; // Tick 60 hz
	frametick.mode = TIMER_TASK_REPEAT;
	timer_add_task(&TIMER_0, &frametick);
	timer_start(&TIMER_0);
}