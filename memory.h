#include <stdio.h>
#include <stdlib.h>
#include"./SDL-2.0.7/include/SDL.h"
#include"./SDL-2.0.7/include/SDL_main.h"

//func reads a file with level, makes a mallocated board, returns ptr to it
struct field ** make_board(unsigned int level);

//zeroes all fields in a board
void zero_board(struct field ** board, int n, int s);

//frees up mallocated previously board
void del_board(struct field ** board, int n);

//this func opens level file, reads it's dimensions and alters given variables
void get_level_size(unsigned int level, int &n, int &s);

//this func loads graphics, takes pointers to surfaces and art location
int load_graphics(
	SDL_Surface **screen,
	SDL_Surface **charset,
	SDL_Surface **player, const char* player_graphic_location,
	SDL_Surface **floor, const char* floor_graphic_location,
	SDL_Surface **barrel, const char* barrel_graphic_location,
	SDL_Surface **wall, const char* wall_graphic_location,
	SDL_Surface **goal, const char* goal_graphic_location,
	SDL_Surface **goal_barrel, const char* goal_barrel_graphic_location,
	SDL_Surface **wallpaper, const char* wallpaper_location,
	SDL_Texture **scrtex,
	SDL_Window **window,
	SDL_Renderer **renderer);