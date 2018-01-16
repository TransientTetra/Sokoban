#include "struct.h"
#include "draw.h"
#include "logic.h"
#include "movement.h"
#include "memory.h"

//todo:
//code enter to change appearance
//goal barrel graphic
//auto screen resize
//change charset
//make menu better looking
//change how menu functions (make it return a value like level selector)
//divise display from menu functions
//organise header linking
//change level so that level.ini is unnecessary
//menu wrapping around when selecting
//center player body

//bugs:
//(fixed)time bug!!!
//(fixed)seg fault (choose level->enter game->m to menu->choose level->esc to menu->quit)
//(fixed)corrupted size vs prev_size (seen once, unseen since; fixed along with munmap?)
//(fixed)munmap_chunk: invalid pointer (in display_leaderboard while sorting)

int main(int argc, char const *argv[])
{
	struct field **board;
	int level = 0;
	unsigned int push_counter = 0, move_counter = 0;
	int t1, t2, quit, rc;
	double delta, global_time;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *player, *floor, *barrel, *wall, *goal, *goal_barrel;
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

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, TILE, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	load_graphics(
	&screen,
	&charset,
	&player, "./art/player.bmp",
	&floor, "./art/floor.bmp",
	&barrel, "./art/barrel.bmp",
	&wall, "./art/wall.bmp",
	&goal, "./art/goal.bmp",
	&goal_barrel, "./art/goal_barrel.bmp",
	&scrtex,
	&window,
	&renderer);

	char text[128];
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	quit = 0;

	menu(screen, scrtex, renderer, charset, blue, black, green, level, quit);

	if (quit == 0)
	{
		board = make_board(level);


		short int win = 0;
		short int flip = 0;
		int n = 0, s = 0;
		get_level_size(level, n, s);

		t1 = SDL_GetTicks();
		global_time = 0;

		while (quit == 0)
		{
			t2 = SDL_GetTicks();
			delta = (t2 - t1) * 0.001;
			t1 = t2;
			global_time += delta;


			SDL_FillRect(screen, NULL, black);
			draw_board(n, s, board, level, screen, player, floor, barrel, wall, goal, goal_barrel);

			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
			sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								global_time = 0;
								del_board(board, n);
								move_counter = 0;
								push_counter = 0;
								menu(screen, scrtex, renderer, charset, blue, black, green, level, quit);
								t1 = SDL_GetTicks();
								if (level != 0)
								{
									get_level_size(level, n, s);
									board = make_board(level);
								}
								break;
							case SDLK_n:
								del_board(board, n);
								board = make_board(level);
								global_time = 0;
								move_counter = 0;
								push_counter = 0;
								break;
							case SDLK_h:
								load_graphics(
								&screen,
								&charset,
								&player, "./art/player_hawaii.bmp",
								&floor, "./art/floor_hawaii.bmp",
								&barrel, "./art/barrel_hawaii.bmp",
								&wall, "./art/wall_hawaii.bmp",
								&goal, "./art/goal_hawaii.bmp",
								&goal_barrel, "./art/goal_barrel_hawaii.bmp",
								&scrtex,
								&window,
								&renderer);
								break;
							case SDLK_DOWN:
								move_down(board, n, s, move_counter, push_counter);
								win = check_win(board, n, s);
								break;
							case SDLK_UP:
								move_up(board, n, s, move_counter, push_counter);
								win = check_win(board, n, s);
								break;
							case SDLK_RIGHT:
								if (flip == 0)
								{
									move_right(board, n, s, move_counter, push_counter);
								}
								win = check_win(board, n, s);
								if (flip == 1)
								{
									flip_horizontal(player);
									flip = 0;
								}
								break;
							case SDLK_LEFT:
								if (flip == 1)
								{
									move_left(board, n, s, move_counter, push_counter);
								}
								win = check_win(board, n, s);
								if (flip == 0)
								{
									flip_horizontal(player);
									flip = 1;
								}
								break;
						}
						break;
					case SDL_QUIT:
						quit = 1;
						break;
				}
			}

			if (win == 1)
			{
				int win_menu_check = win_prompt(screen, scrtex, renderer, charset, blue, quit, level, move_counter, push_counter, global_time);
				if (win_menu_check == 1)
				{
					quit = 1;
					del_board(board, n);
				}
				if (win_menu_check == 0)
				{
					win = 0;
					del_board(board, n);
					global_time = 0;
					move_counter = 0;
					push_counter = 0;
					menu(screen, scrtex, renderer, charset, blue, black, green, level, quit);
					t1 = SDL_GetTicks();
					get_level_size(level, n, s);
					board = make_board(level);
				}
			}
		}
	}
	

	SDL_FreeSurface(goal);
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

	return 0;
}