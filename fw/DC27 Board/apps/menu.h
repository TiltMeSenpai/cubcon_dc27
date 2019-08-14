/*
 * menu.h
 *
 * Created: 7/11/2019 17:38:54
 *  Author: tiltmesenpai
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <app.h>

// Menu app callbacks
void menu_init(u8g2_t *);
void menu_up(u8g2_t *);
void menu_down(u8g2_t *);
void menu_sel(u8g2_t *);

static struct app menu_app = {
	.app_name = "Menu",
	.init = menu_init,
	.btn_up = menu_up,
	.btn_click = menu_sel,
	.btn_down = menu_down,
	.frametick = NULL,
};



#endif /* MENU_H_ */