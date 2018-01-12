#include "./SDL-2.0.7/include/SDL.h"
#include "./SDL-2.0.7/include/SDL_main.h"
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH	1200
#define SCREEN_HEIGHT	600
#define BOARD_X 64
#define BOARD_Y 64
#define TILE 32
#define PLAYERSPEED 300

struct field
{
	unsigned int player;
	unsigned int wall;
	unsigned int barrel;
	unsigned int goal;
	unsigned int floor;
};

struct score
{
	int number;
	int time;
	int moves;
};