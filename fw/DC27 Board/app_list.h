/*
 * app_list.h
 *
 * Created: 7/11/2019 17:42:24
 *  Author: tiltmesenpai
 */ 


#ifndef APP_LIST_H_
#define APP_LIST_H_

#include <app.h>

// Tetris fns
void tetris_init(u8g2_t *disp);
void tetris_frametick(u8g2_t *disp);
void tetris_btn_up(u8g2_t *disp);
void tetris_btn_down(u8g2_t *disp);
void tetris_btn_click(u8g2_t *disp);


// Birb fns
void flappy_init(u8g2_t *disp);
void flappy_frametick(u8g2_t *disp);
void flappy_btn_click(u8g2_t *disp);

// ??? fns
void init_knock(u8g2_t* disp);
void frametick_knock(u8g2_t *disp);
void click_knock(u8g2_t* disp);

// Hibernate callback
void do_hibernate(u8g2_t *);

static struct app hibernate_app = {
	.app_name = "Hibernate",
	.init = do_hibernate
};

static struct app tetris_app = {
	.app_name = "Tetris",
	.init = tetris_init,
	.frametick = tetris_frametick,
	.btn_up = tetris_btn_up,
	.btn_down = tetris_btn_down,
	.btn_click = tetris_btn_click
};

static struct app flappy_app = {
	.app_name = "Flappy Birb",
	.init = flappy_init,
	.frametick = flappy_frametick,
	.btn_click = flappy_btn_click,
	.btn_up = flappy_btn_click,
	.btn_down = flappy_btn_click
	};
	
static struct app knock_app = {
	.app_name = "???",
	.init = init_knock,
	.frametick = frametick_knock,
	.btn_click = click_knock
	};

static struct app *app_list[] = {
	&tetris_app,
	&flappy_app,
	&knock_app,
	&hibernate_app,
	};

#endif /* APP_LIST_H_ */