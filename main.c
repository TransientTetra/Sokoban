#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C"
{
#include"./SDL-2.0.7/include/SDL.h"
#include"./SDL-2.0.7/include/SDL_main.h"
}

#include "draw.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

int main(int argc, char const *argv[])
{
	int rc;
	SDL_Event event;
	SDL_Surface *screen, *charset, *board;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	if (rc != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_SetWindowTitle(window, "Sokoban");

	SDL_ShowCursor(SDL_DISABLE);

	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}


	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}