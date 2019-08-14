/*
 * app.c
 *
 * Created: 7/13/2019 10:47:05
 *  Author: tiltmesenpai
 */ 
#include <app.h>
#include <apps/menu.h>
#include <hal_timer.h>

extern struct timer_descriptor TIMER_0;

#define IDLE_TIME 30 * 60
static uint32_t timer_countdown = IDLE_TIME, ge_reset_ctr;

void timer_do_reset(){
	if(timer_countdown < 1) timer_do_wakeup();
	timer_countdown = IDLE_TIME;
}

void timer_do_tick(void){
	if(--timer_countdown < 1) timer_do_sleep();
	if(current_app->frametick) current_app->frametick(&u8g2);
}

void timer_do_sleep(void){
	timer_stop(&TIMER_0);
	u8g2_SetPowerSave(&u8g2, 1);
}

void timer_do_wakeup(void){
	timer_start(&TIMER_0);
	u8g2_SetPowerSave(&u8g2, 0);
}

void do_hibernate(void){
	launch_app(&menu_app);
	timer_countdown = 1;
	timer_do_sleep();
}

void tilt_up(){
	timer_do_reset();
	if(current_app->btn_up) current_app->btn_up(&u8g2);
}

void btn_click(){
	timer_do_reset();
	if(current_app->btn_click) current_app->btn_click(&u8g2);
}

void tilt_down(){
	timer_do_reset();
	if(current_app->btn_down) current_app->btn_down(&u8g2);
}

void launch_app(struct app *app){
	current_app = app;
	app->init(&u8g2);
}