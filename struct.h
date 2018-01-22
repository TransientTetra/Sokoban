#include "./SDL-2.0.7/include/SDL.h"
#include "./SDL-2.0.7/include/SDL_main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define BOARD_X 64
#define BOARD_Y 64
#define TILE 32
#define VERTICAL_MENU_ORIENT 200
#define HAWAII_CODE "havana"


struct field
{
	unsigned short int player;
	unsigned short int wall;
	unsigned short int barrel;
	unsigned short int goal;
	unsigned short int floor;
};

struct score
{
	char name[32];
	int number;
	int time;
	int moves;
};