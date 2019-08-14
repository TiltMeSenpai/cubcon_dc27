/*
 * menu.c
 *
 * Created: 7/11/2019 17:38:41
 *  Author: tiltmesenpai
 */ 

#include "menu.h"
#include <app_list.h>

#define NUM_ELEM(list) (sizeof(list) / sizeof(*list))

static int app_sel;

void draw_menu_items(u8g2_t *disp){
	u8g2_DrawStr(disp, 0, 16, ">");
	u8g2_DrawStr(disp, 5, 8, app_list[(app_sel - 1 + NUM_ELEM(app_list)) % NUM_ELEM(app_list)]->app_name);
	u8g2_DrawStr(disp, 5, 16, app_list[app_sel]->app_name);
	u8g2_DrawStr(disp, 5, 24, app_list[(app_sel + 1 + NUM_ELEM(app_list)) % NUM_ELEM(app_list)]->app_name);
}

void menu_init(u8g2_t *disp) {
	app_sel = 0;
	u8g2_ClearBuffer(disp);
	draw_menu_items(disp);
	u8g2_SendBuffer(disp);
}

void menu_up(u8g2_t *disp){
	app_sel = (app_sel + 1 + NUM_ELEM(app_list)) % NUM_ELEM(app_list);
	u8g2_ClearBuffer(disp);
	draw_menu_items(disp);
	u8g2_SendBuffer(disp);
}

void menu_down(u8g2_t *disp){
	app_sel = (app_sel - 1 + NUM_ELEM(app_list)) % NUM_ELEM(app_list);
	u8g2_ClearBuffer(disp);
	draw_menu_items(disp);
	u8g2_SendBuffer(disp);
}

void menu_sel(u8g2_t * disp){
	launch_app(app_list[app_sel]);
}


