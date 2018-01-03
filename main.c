#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "draw.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define TILE 32

int main(int argc, char const *argv[])
{
	int quit, rc;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *player, *floor, *barrel, *wall, *goal;
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

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Sokoban");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

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
	SDL_SetColorKey(charset, true, 0x000000);

	player = SDL_LoadBMP("./art/player.bmp");
	if(player == NULL)
	{
		printf("SDL_LoadBMP(player.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	floor = SDL_LoadBMP("./art/floor.bmp");
	if(floor == NULL)
	{
		printf("SDL_LoadBMP(floor.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(player);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	wall = SDL_LoadBMP("./art/wall.bmp");
	if(wall == NULL)
	{
		printf("SDL_LoadBMP(wall.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(floor);
		SDL_FreeSurface(player);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	barrel = SDL_LoadBMP("./art/barrel.bmp");
	if(barrel == NULL)
	{
		printf("SDL_LoadBMP(barrel.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(wall);
		SDL_FreeSurface(floor);
		SDL_FreeSurface(player);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	goal = SDL_LoadBMP("./art/goal.bmp");
	if(goal == NULL)
	{
		printf("SDL_LoadBMP(goal.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(barrel);
		SDL_FreeSurface(wall);
		SDL_FreeSurface(floor);
		SDL_FreeSurface(player);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	char text[128];
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	quit = 0;

	while (quit == 0)
	{
		SDL_FillRect(screen, NULL, black);
		DrawSurface(screen, player, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		DrawSurface(screen, floor, SCREEN_WIDTH / 2 + TILE, SCREEN_HEIGHT / 2 + TILE);
		DrawSurface(screen, barrel, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + TILE);
		DrawSurface(screen, wall, SCREEN_WIDTH / 2 + 2 * TILE, SCREEN_HEIGHT / 2 + TILE);
		DrawSurface(screen, goal, SCREEN_WIDTH / 2 - TILE, SCREEN_HEIGHT / 2);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					break;
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					quit = 1;
					break;
			}
		}
	}

	SDL_FreeSurface(barrel);
	SDL_FreeSurface(wall);
	SDL_FreeSurface(floor);
	SDL_FreeSurface(player);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	SDL_Quit();
	return 0;
}