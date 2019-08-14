/*
 * flappy_bird.c
 *
 * Created: 7/19/2019 15:36:16
 *  Author: tiltmesenpai
 */ 

#include <app_list.h>
#include <hal_rand_sync.h>

#define GAMEBOARD_LEN 4

extern struct rand_sync_desc RAND_0;

struct bird_pipe {
	uint8_t low;
	uint8_t high;
	uint16_t x;
	};

static const uint8_t bird[] = {
 0xec,0xfc,0xef,0xe7,0xe2};

static int16_t dy, y;
static uint8_t game_over;
static unsigned int score;

struct bird_pipe gameboard[GAMEBOARD_LEN];

void spawn_pipe(struct bird_pipe *pipe, int x){
	pipe->x = x;
	pipe->low = rand_sync_read8(&RAND_0) % 32;
	uint8_t pipe_delta = rand_sync_read8(&RAND_0) % 5;
	pipe->high = (pipe->low + pipe_delta + 10) % 32;
	if(pipe->high < pipe->low){
		int swap = pipe->high;
		pipe->high = pipe->low;
		pipe->low = swap;
	}
}


void draw_game_over(u8g2_t *disp){
	static char score_screen[16]; // This should be enough right?
	sprintf(score_screen, "%d", score);
	int px = u8g2_GetStrWidth(disp, score_screen);
	u8g2_SetDrawColor(disp, 0);
	u8g2_DrawBox(disp, 40, 6, 51, 20);
	u8g2_SetDrawColor(disp, 1);
	u8g2_DrawStr(disp, 44, 14, "Game Over");
	u8g2_DrawStr(disp, 64 - (px/2), 24, score_screen);
}

void draw_pipe(u8g2_t *disp, struct bird_pipe *pipe){
	if(pipe->high > pipe->low){
		u8g2_DrawBox(disp, pipe->x, 0, 5, pipe->low);
		u8g2_DrawBox(disp, pipe->x, pipe->high, 5, 32 - pipe->high);
	}
	else u8g2_DrawBox(disp, pipe->x, pipe->low, 5, pipe->low - pipe->high);
}

void draw_gameboard(u8g2_t *disp){
	for(int i = 0; i < GAMEBOARD_LEN; i++){
		struct bird_pipe *p = &gameboard[i];
		if(p->x < 8 && !(p->low< (y / 20) && ((p->high - 5) > (y / 20))))
			game_over = 1;
		if(p->x > 0){
			p->x--;
			draw_pipe(disp, p);
		}
		else {
			spawn_pipe(p, 128);
			score++;
		}
	}
	if(game_over) draw_game_over(disp);
}

void flappy_init(u8g2_t *disp){
	y = 320;
	dy = 0;
	game_over = 0;
	score = 0;
	gameboard[0].high = 32;
	gameboard[0].low = 0;
	gameboard[0].x = 0;
	u8g2_SetDrawColor(disp, 1);
	u8g2_ClearBuffer(disp);
	u8g2_SendBuffer(disp);
	rand_sync_enable(&RAND_0);
	for(int i = 1; i < GAMEBOARD_LEN; i++) // Everything but the first pipe
		spawn_pipe(&gameboard[i], i * (128 / GAMEBOARD_LEN));
}

void flappy_frametick(u8g2_t *disp){
	if(game_over) return;
	y = (y + dy + 640) % 640; 
	if(dy < 120) dy+=2;
	u8g2_ClearBuffer(disp);
	draw_gameboard(disp);
	u8g2_DrawXBM(disp, 3, y/20, 5, 5, &bird);
	u8g2_SendBuffer(disp);
}

void flappy_btn_click(u8g2_t *disp){
	if(game_over) flappy_init(disp);
	else{
		if(dy > -120) dy -= 30;
		if(dy > 0) dy = 0;
	}
}