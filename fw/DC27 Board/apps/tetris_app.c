/*
 * tetris_app.c
 *
 * Created: 7/16/2019 11:54:58 AM
 *  Author: a.kirilov
 */ 

#include "tetris_app.h"
#include <hal_rand_sync.h>
#include <hal_gpio.h>
#include <stdio.h>
#include <string.h>

extern struct rand_sync_desc RAND_0; // Don't ask why this doesn't exist already

// ####################
// # Game static vars #
// ####################

static uint32_t game_frame_in_cur_lvl;
static uint32_t game_score;
static struct tetromino game_active_piece;
static uint8_t game_logical_board[36][10];
static uint8_t game_spawn_tracker;
static uint16_t game_level;
static uint8_t game_start_level;
static uint32_t game_lines_cleared;
static uint8_t game_frames_per_drop;
static uint16_t game_btn_held_frames;
static enum button_pressed game_last_btn_press;
static enum state game_state;

// #######################
// # Drawing conversions #
// #######################

int16_t ltopx(int16_t logicx){
	return 3 * logicx + GAME_X_POS;
}

int16_t ltopy(int16_t logicy){
	return 3 * logicy + GAME_Y_POS;
}

// ###################
// # Drawing Helpers #
// ###################

bool get_lpixel_in_bitmap(uint16_t bitmap, uint8_t x, uint8_t y){
	return (bitmap << (4* y + x)) & 0x8000;
}

void draw_lpixel(u8g2_t *disp, int16_t x, int16_t y){
	u8g2_DrawBox(disp, ltopx(x), ltopy(y), 3, 3);
}

void draw_score(u8g2_t *disp, uint32_t score){
	// Update Score
	static char score_buf[7] = "000000";
	sprintf(score_buf, "%06u", score);
	u8g2_DrawStr(disp, 4, TETRIS_HDR_HEIGHT - 2, score_buf);
}

void draw_tetromino_color(u8g2_t *disp, struct tetromino *piece, uint8_t color){
	// Verify we have a real tetromino
	if (piece->type == TETROMINO_TYPE_NONE)
	{
		// WTF?
		return;
	}
	
	// Get bitmap
	uint16_t bitmap = tetromino_rotations[piece->type][piece->rotation];
	
	// Iterate bitmap and draw
	u8g2_SetDrawColor(disp, color);
	for (uint8_t by = 0; by < 4; by++){
		for (uint8_t bx = 0; bx < 4; bx++){
			if (get_lpixel_in_bitmap(bitmap,bx,by)){
				int16_t boardx = piece->x + bx;
				int16_t boardy = piece->y + by;
				draw_lpixel(disp, boardx, boardy);
			}
		}
	}
	
	// Revert draw to default color
	u8g2_SetDrawColor(disp, 1);
}

// XOR draw tetromino
void xor_draw_tetromino(u8g2_t *disp, struct tetromino *piece){
	draw_tetromino_color(disp, piece, 2);
}

void draw_header(u8g2_t *disp){
	// Draw Tetris Header
	static unsigned char tetris_hdr_bits[] = {
		0b11111111, 0b11111111, 0b11111111, 0b11111111,
		0b00000001, 0b00000000, 0b00000000, 0b10000000,
		0b01110001, 0b01110111, 0b01110011, 0b10000111, // |
		0b00100001, 0b00100001, 0b00100101, 0b10000001, // |
		0b00100001, 0b00100111, 0b00100011, 0b10000111, // | "TETRIS"
		0b00100001, 0b00100001, 0b00100101, 0b10000100, // |
		0b00100001, 0b00100111, 0b01110101, 0b10000111, // |
		0b00000001, 0b00000000, 0b00000000, 0b10000000,
		0b11110001, 0b11111111, 0b11111111, 0b10000111, // LINE
		0b00000001, 0b00000000, 0b00000000, 0b10000000,
		0b00000001, 0b00000000, 0b00000000, 0b10000000, // |
		0b00000001, 0b00000000, 0b00000000, 0b10000000, // |
		0b00000001, 0b00000000, 0b00000000, 0b10000000, // | Score space
		0b00000001, 0b00000000, 0b00000000, 0b10000000, // |
		0b00000001, 0b00000000, 0b00000000, 0b10000000, // |
		0b00000001, 0b00000000, 0b00000000, 0b10000000,
		0b11111111, 0b11111111, 0b11111111, 0b11111111
	};
	
	// Draw header
	u8g2_DrawXBM(disp, 0, 0, TETRIS_HDR_WIDTH, TETRIS_HDR_HEIGHT, tetris_hdr_bits);
}

void draw_game_frame(u8g2_t *disp){
	u8g2_DrawFrame(disp, 0, TETRIS_HDR_HEIGHT + 1, SCN_WIDTH, (SCN_HEIGHT - (TETRIS_HDR_HEIGHT + 1)));
}

void draw_game_board(u8g2_t *disp){
	for (uint16_t ly = 0; ly < GAME_LOGICAL_HEIGHT; ly++){
		for (uint16_t lx = 0; lx < GAME_LOGICAL_WIDTH; lx++){
			if (game_logical_board[ly][lx]){
				draw_lpixel(disp, lx, ly);
			}
		}
	}
}

// Redraw everything except
void full_redraw(u8g2_t *disp){
	u8g2_ClearBuffer(disp);
	draw_header(disp);
	draw_game_frame(disp);
	draw_score(disp, game_score);
	draw_game_board(disp);
	u8g2_SendBuffer(disp);
}

// ######################
// # Game Logic Helpers #
// ######################

bool move_collides(struct tetromino *piece, int16_t dx, int16_t dy, uint8_t drot){
	// Get the new things
	int16_t newx = piece->x + dx;
	int16_t newy = piece->y + dy;
	uint8_t newrot = (piece->rotation + drot) % 4;
	uint16_t bitmap = tetromino_rotations[piece->type][newrot];
	
	// Check collisions
	for (uint8_t by = 0; by < 4; by++){
		for (uint8_t bx = 0; bx < 4; bx++){
			int16_t nbx = newx + bx;
			int16_t nby = newy + by;
			if (get_lpixel_in_bitmap(bitmap,bx,by)){
				if (nby < 0 || nby >= GAME_LOGICAL_HEIGHT || nbx < 0 || nbx >= GAME_LOGICAL_WIDTH || game_logical_board[nby][nbx]) {
					return true;
				}
			}
		}
	}
	
	return false;
}

void spawn_tetromino(struct tetromino *piece){
	// Choose type
	int type;
	do {
		type = rand_sync_read8(&RAND_0) % 7;
	} while ((1 << type) & game_spawn_tracker);
	
	// Update spawn tracker
	game_spawn_tracker = game_spawn_tracker | (1 << type);
	
	// Reset spawn tracker if we've spawned all 7 pieces
	if (game_spawn_tracker == 0x7f) {
		game_spawn_tracker = 0;
	}
	
	// Set parameters
	piece->type = type;
	piece->x = 3;
	piece->y = 0;
	piece->rotation = 0;
}

// Move a tetromino
void move_tetromino(u8g2_t *disp, struct tetromino *piece, int8_t direction) {
	if (!move_collides(piece, direction, 0, 0)) {
		xor_draw_tetromino(disp, piece);
		piece->x += direction;
		xor_draw_tetromino(disp, piece);
		u8g2_SendBuffer(disp);
	}
}

// Freeze a tetromino
void freeze_tetromino(struct tetromino *piece){
	uint16_t bitmap = tetromino_rotations[piece->type][piece->rotation];
	for (uint8_t by = 0; by < 4; by++){
		for (uint8_t bx = 0; bx < 4; bx++){
			if (get_lpixel_in_bitmap(bitmap,bx,by)){
				int16_t boardx = piece->x + bx;
				int16_t boardy = piece->y + by;
				game_logical_board[boardy][boardx] = 1;
			}
		}
	}
}

uint8_t clear_lines(u8g2_t *disp, struct tetromino *piece)
{
	uint8_t lines_cleared = 0;
	int16_t ply = piece->y;
	for (uint16_t ly = ply; (ly < ply + 4) && (ly < GAME_LOGICAL_HEIGHT); ly++){
		uint8_t *row = game_logical_board[ly];
		if (row[0] && row[1] && row[2] && row[3] && row[4] &&
			row[5] && row[6] && row[7] && row[8] && row[9]){
			// Clear a row
			lines_cleared++;
			// Shift above lines down
			for (uint16_t clry = ly; clry > 0; clry--){
				for (uint16_t clrx = 0; clrx < GAME_LOGICAL_WIDTH; clrx++){
					game_logical_board[clry][clrx] = game_logical_board[clry - 1][clrx];
				}
			}
		}
	}
	// Full redraw if we changed the board
	if (lines_cleared){
		full_redraw(disp);
	}
	return lines_cleared;
}

uint32_t score_lines(uint8_t lines){
	switch (lines){
	case 1:
		return 40 * (game_level + 1);
	case 2:
		return 100 * (game_level + 1);
	case 3:
		return 300 * (game_level + 1);
	case 4:
		return 1200 * (game_level + 1);
	}
}

void game_setup(u8g2_t *disp) {
	// Clear values
	game_frame_in_cur_lvl = 0;
	game_score = 0;
	game_spawn_tracker = 0;
	game_frames_per_drop = frames_per_level[game_level];
	game_active_piece.type = TETROMINO_TYPE_NONE;
	game_start_level = game_level = 0;
	memset(&game_logical_board, 0, GAME_LOGICAL_HEIGHT * GAME_LOGICAL_WIDTH);

	// Draw Everything
	full_redraw(disp);
	u8g2_SendBuffer(disp);
	
	// Set game state running
	game_state = GAME_STATE_SETUP;
}

// Clear score, clear board, clear frame counter, clear spawner, set level
void game_start(u8g2_t *disp)
{
	// Clear values
	game_last_btn_press = BUTTON_PRESSED_NONE;
	game_level = game_start_level;
	
	// Redraw score
	draw_score(disp, game_score);
	
	// Spawn first tetromino
	spawn_tetromino(&game_active_piece);
	xor_draw_tetromino(disp, &game_active_piece);
	
	// Update game state
	game_state = GAME_STATE_RUNNING;
	
	// Flush buffer
	u8g2_SendBuffer(disp);
}

void game_over(u8g2_t *disp, char *line1, char *line2)
{
	// Set game state
	game_state = GAME_STATE_OVERED;
	
	// Draw the last piece
	draw_tetromino_color(disp, &game_active_piece, 1);
	
	// Turn off active piece
	game_active_piece.type = TETROMINO_TYPE_NONE;
	
	// Clear a bit box
	u8g2_SetDrawColor(disp, 0);
	u8g2_DrawBox(disp, ltopx(3) - 5, ltopy(15) - 9, 23, 19);
	u8g2_SetDrawColor(disp, 1);
	
	// Draw bounding frame
	u8g2_DrawFrame(disp, ltopx(3) - 4, ltopy(15) - 8, 21, 17);
	
	// Write "Game Over"
	u8g2_DrawStr(disp, ltopx(3) - 1, ltopy(15), line1);
	u8g2_DrawStr(disp, ltopx(3) - 1 , ltopy(17), line2);
	u8g2_SendBuffer(disp);
}

void lose_game(u8g2_t *disp){
	game_over(disp, "YOUR", "LOSE");
}

void win_game(u8g2_t *disp){
	game_over(disp, "YOUR", "WIN!");
}

// #################
// # App Functions #
// #################

// Tetris one-time setup
void tetris_init(u8g2_t *disp){
	// Set rotation
	u8g2_SetDisplayRotation(disp, U8G2_R3);
	
	// Init font, rand
	u8g2_SetFont(disp, u8g2_font_micro_mr);
	rand_sync_enable(&RAND_0);
	
	game_setup(disp);
}

void tetris_frametick(u8g2_t *disp){
	if (game_state == GAME_STATE_RUNNING){
		// Increase frame counter
		game_frame_in_cur_lvl++;
		
		// Handle button actions
		// Center button held
		if ((game_last_btn_press == BUTTON_PRESSED_CENTER) && !gpio_get_pin_level(PIN_PA03)) {
			if (game_btn_held_frames < 255) {
				game_btn_held_frames++;
			}
			if (game_btn_held_frames >= BTN_HELD_DELAY_FRAMES) {
				game_frames_per_drop = 1;
				game_score++;
				draw_score(disp, game_score);
				//u8g2_SendBuffer(disp);
			}
		// Right held
		} else if ((game_last_btn_press == BUTTON_PRESSED_RIGHT) && !gpio_get_pin_level(PIN_PA04)) {
			if (game_btn_held_frames < 255){
				game_btn_held_frames++;
			}
			if (game_btn_held_frames >= BTN_HELD_DELAY_FRAMES) {
				move_tetromino(disp, &game_active_piece, 1);
			}
		// Left held
		} else if ((game_last_btn_press == BUTTON_PRESSED_LEFT) && !gpio_get_pin_level(PIN_PA02)) {	
			if (game_btn_held_frames < 255){
				game_btn_held_frames++;
			}
			if (game_btn_held_frames >= BTN_HELD_DELAY_FRAMES) {
				move_tetromino(disp, &game_active_piece, -1);
			}
		// Button released or mismatched press
		} else {
			// Last press center Short hold - rotate
			if ((game_last_btn_press == BUTTON_PRESSED_CENTER) && game_btn_held_frames < BTN_HELD_DELAY_FRAMES) {
				// Short hold = rotate on release
				if (!move_collides(&game_active_piece, 0, 0, 1)) {
					xor_draw_tetromino(disp, &game_active_piece);
					game_active_piece.rotation++;
					game_active_piece.rotation %= 4;
					xor_draw_tetromino(disp, &game_active_piece);
					u8g2_SendBuffer(disp);
				}
				// Try rotation with kick x-1
				else if (!move_collides(&game_active_piece, -1, 0, 1)) {
					xor_draw_tetromino(disp, &game_active_piece);
					game_active_piece.x--;
					game_active_piece.rotation++;
					game_active_piece.rotation %= 4;
					xor_draw_tetromino(disp, &game_active_piece);
					u8g2_SendBuffer(disp);
				}
				// Try rotation with kick x+1
				else if (!move_collides(&game_active_piece, 1, 0, 1)) {
					xor_draw_tetromino(disp, &game_active_piece);
					game_active_piece.x++;
					game_active_piece.rotation++;
					game_active_piece.rotation %= 4;
					xor_draw_tetromino(disp, &game_active_piece);
					u8g2_SendBuffer(disp);
				}
				// Try rotation with kick x-2
				else if (!move_collides(&game_active_piece, -2, 0, 1)) {
					xor_draw_tetromino(disp, &game_active_piece);
					game_active_piece.x-=2;
					game_active_piece.rotation++;
					game_active_piece.rotation %= 4;
					xor_draw_tetromino(disp, &game_active_piece);
					u8g2_SendBuffer(disp);
				}
				// Try rotation with kick x+2
				else if (!move_collides(&game_active_piece, 2, 0, 1)) {
					xor_draw_tetromino(disp, &game_active_piece);
					game_active_piece.x+=2;
					game_active_piece.rotation++;
					game_active_piece.rotation %= 4;
					xor_draw_tetromino(disp, &game_active_piece);
					u8g2_SendBuffer(disp);
				}
			// Long hold - stop soft dropping
			} else {
				// We stop sliding
				game_frames_per_drop = frames_per_level[game_level];
			}
			game_btn_held_frames = 0;
			game_last_btn_press = BUTTON_PRESSED_NONE;
		}

		// Move piece down
		if (game_frame_in_cur_lvl % game_frames_per_drop == 0){
			// If we can't move down, freeze piece, line clear, and check for game over
			if(move_collides(&game_active_piece, 0, 1, 0)){
				// If we are soft dropping when we hit the bottom
				if (game_btn_held_frames >= BTN_HELD_DELAY_FRAMES) {
					// Stop the soft drop
					game_btn_held_frames = 0;
					// Reset the frames to move and give one full turn
					game_frames_per_drop = frames_per_level[game_level];
					game_frame_in_cur_lvl = 0;
					// Reset the button down bool
					game_last_btn_press = BUTTON_PRESSED_NONE;
					// Return to buy ourselves and extra frame
					//return;
				}
				// Freeze piece
				freeze_tetromino(&game_active_piece);
				// Check line clear
				uint8_t lines_cleared = clear_lines(disp, &game_active_piece);
				game_lines_cleared += lines_cleared;
				// Update score
				game_score += score_lines(lines_cleared);
				// Check level for update
				if (((game_lines_cleared / 10) > (game_level)) && (game_level < MAX_LEVEL)){
					game_level++;
					game_frame_in_cur_lvl = 0;
					game_frames_per_drop = frames_per_level[game_level];
				}
				// Check score overflow
				if (game_score > 999999)
				{
					game_score = 999999;
					draw_score(disp, game_score);
					win_game(disp);
					return;
				}
				// Draw score
				draw_score(disp, game_score);
				// Spawn new piece
				spawn_tetromino(&game_active_piece);
				// Check game over
				if (move_collides(&game_active_piece, 0, 0, 0)){
					lose_game(disp);
					return;
				}
			// Else just move down normally
			} else {
				xor_draw_tetromino(disp, &game_active_piece);
				game_active_piece.y++;
			}
			// Regardless, draw the piece in its new location
			xor_draw_tetromino(disp, &game_active_piece);
			u8g2_SendBuffer(disp);
		}
	}
}

// Move piece right
void tetris_btn_up(u8g2_t *disp){
	if (game_state == GAME_STATE_SETUP){
		if (game_start_level < 9) {
			game_start_level++;
			draw_score(disp, game_start_level);
			u8g2_SendBuffer(disp);
		}
	} else if (game_state == GAME_STATE_RUNNING){
		move_tetromino(disp, &game_active_piece, 1);
		game_last_btn_press = BUTTON_PRESSED_RIGHT;
	}
}

// Move piece left and set held button
void tetris_btn_down(u8g2_t *disp){
	if (game_state == GAME_STATE_SETUP){
		if (game_start_level > 0) {
			game_start_level--;
			draw_score(disp, game_start_level);
			u8g2_SendBuffer(disp);
		}
	} else if (game_state == GAME_STATE_RUNNING){
		move_tetromino(disp, &game_active_piece, -1);
		game_last_btn_press = BUTTON_PRESSED_LEFT;
	}
}

// Rotate
void tetris_btn_click(u8g2_t *disp){
	if (game_state == GAME_STATE_SETUP){
		game_start(disp);
	} else if (game_state == GAME_STATE_RUNNING)
	{
		game_last_btn_press = BUTTON_PRESSED_CENTER;
	} else if (game_state == GAME_STATE_OVERED) {
		// TODO something with score instead?
		game_setup(disp);
	}
}
