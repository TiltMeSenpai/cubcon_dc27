/*
 * tetris_app.h
 *
 * Created: 7/17/2019 12:06:33 PM
 *  Author: a.kirilov
 */ 

#ifndef TETRIS_ROTATIONS_H_
#define TETRIS_ROTATIONS_H_

#include <app_list.h>

// Tetromino macro
#define PACK_TETROMINO(row0, row1, row2, row3) (row0 << 12 | row1 << 8 | row2 << 4 | row3)

// Soft Drop Delay
#define BTN_HELD_DELAY_FRAMES 10

// Header Defines
#define TETRIS_HDR_WIDTH SCN_WIDTH
#define TETRIS_HDR_HEIGHT 17

// Score Defines
#define TETRIS_SCO_X 4
#define TETRIS_SCO_Y (TETRIS_HDR_HEIGHT - 2)
#define MAX_LEVEL 20

// Game boundary defines
#define GAME_X_POS 1 // 1 for the bounding frame
#define GAME_Y_POS (TETRIS_HDR_HEIGHT + 2) // 1 for the empty space, 1 for the bounding frame
#define GAME_LOGICAL_WIDTH 10 // 10 thiccels = 30 pixels
#define GAME_LOGICAL_HEIGHT 36 // 36 thiccels = 108 pixels

// Game state
enum state {
	GAME_STATE_SETUP = 0,
	GAME_STATE_RUNNING,
	GAME_STATE_OVERED
	};

// Tetromino type enum
enum tetromino_type {
	TETROMINO_TYPE_NONE = -1,
	TETROMINO_TYPE_I = 0,
	TETROMINO_TYPE_J,
	TETROMINO_TYPE_L,
	TETROMINO_TYPE_O,
	TETROMINO_TYPE_S,
	TETROMINO_TYPE_T,
	TETROMINO_TYPE_Z,
};

enum button_pressed {
	BUTTON_PRESSED_NONE = 0,
	BUTTON_PRESSED_LEFT,
	BUTTON_PRESSED_CENTER,
	BUTTON_PRESSED_RIGHT
	};

// Tetris piece
struct tetromino {
	enum tetromino_type type;
	uint8_t rotation;
	int8_t x;
	int8_t y;
};

// Frames per drop for each level
// Divided by 2 from og tetris because we run at 1/2 the framerate
uint8_t frames_per_level[21] = {27, 25, 23, 21, 19, 17, 14, 11, 9, 6, 5, 5, 4, 4, 3, 3,	3, 3, 2, 2,	2};

// Rotations for each tetromino
uint16_t tetromino_rotations[7][4] = {
	// I rotations
	{
		PACK_TETROMINO(
		0b0000,
		0b1111,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0010,
		0b0010,
		0b0010,
		0b0010),
		
		PACK_TETROMINO(
		0b0000,
		0b0000,
		0b1111,
		0b0000),
		
		PACK_TETROMINO(
		0b0100,
		0b0100,
		0b0100,
		0b0100)
					   
	},
	// J rotations
	{
		PACK_TETROMINO(
		0b1000,
		0b1110,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0110,
		0b0100,
		0b0100,
		0b0000),
		
		PACK_TETROMINO(
		0b0000,
		0b1110,
		0b0010,
		0b0000),
		
		PACK_TETROMINO(
		0b0100,
		0b0100,
		0b1100,
		0b0000)
	},
	// L rotations
	{
		PACK_TETROMINO(
		0b0010,
		0b1110,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0100,
		0b0100,
		0b0110,
		0b0000),
		
		PACK_TETROMINO(
		0b0000,
		0b1110,
		0b1000,
		0b0000),
		
		PACK_TETROMINO(
		0b1100,
		0b0100,
		0b0100,
		0b0000)
	},
	// O rotations
	{
		PACK_TETROMINO(
		0b0110,
		0b0110,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0110,
		0b0110,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0110,
		0b0110,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0110,
		0b0110,
		0b0000,
		0b0000),
	},
	// S rotations
	{
		PACK_TETROMINO(
		0b0110,
		0b1100,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0100,
		0b0110,
		0b0010,
		0b0000),
		
		PACK_TETROMINO(
		0b0000,
		0b0110,
		0b1100,
		0b0000),
		
		PACK_TETROMINO(
		0b1000,
		0b1100,
		0b0100,
		0b0000),
	},
	// T rotations
	{
		PACK_TETROMINO(
		0b0100,
		0b1110,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0100,
		0b0110,
		0b0100,
		0b0000),
		
		PACK_TETROMINO(
		0b0000,
		0b1110,
		0b0100,
		0b0000),
		
		PACK_TETROMINO(
		0b0100,
		0b1100,
		0b0100,
		0b0000),
	},
	// Z rotations
	{
		PACK_TETROMINO(
		0b1100,
		0b0110,
		0b0000,
		0b0000),
		
		PACK_TETROMINO(
		0b0010,
		0b0110,
		0b0100,
		0b0000),
		
		PACK_TETROMINO(
		0b0000,
		0b1100,
		0b0110,
		0b0000),
		
		PACK_TETROMINO(
		0b0100,
		0b1100,
		0b1000,
		0b0000),
	}
};

#endif /* TETRIS_ROTATIONS_H_ */