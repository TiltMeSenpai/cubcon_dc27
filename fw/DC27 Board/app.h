/*
 * app.h
 *
 * Created: 7/10/2019 19:52:48
 *  Author: tiltmesenpai
 */ 


#ifndef APP_H_
#define APP_H_
#include <display.h>

typedef void (* app_cb)(u8g2_t *);

struct app {
	app_cb init;
	app_cb frametick;
	app_cb btn_up;
	app_cb btn_click;
	app_cb btn_down;
	char *app_name;
	};


struct app *current_app;
u8g2_t u8g2;

void timer_do_reset(void);
void timer_do_tick(void);
void timer_do_sleep(void);
void timer_do_wakeup(void);
void tilt_up(void);
void btn_click(void);
void tilt_down(void);

void launch_app(struct app *app);

#endif /* APP_H_ */