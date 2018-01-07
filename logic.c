#include "struct.h"
#include "logic.h"

//takes board and it's size and two ints, searches for player position and changes
//the two ints into player's position coordinates
void get_player_position(struct field **board, int &x, int &y, int n, int s)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			if (board[i][j].player == 1)
			{
				x = i;
				y = j;
				return;
			}
		}
	}
}

//checks if all barrels are on on goal tiles, returns 1 if yes, 0 otherwise
int check_win(struct field **board, int n, int s)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			if (board[i][j].barrel == 1 && board[i][j].goal != 1)
			{
				return 0;
			}
		}
	}
	return 1;
}

//displays a prompt upon winning
int win_prompt(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int blue, int &quit, int level, int move_counter, int push_counter)
{
	SDL_Event event;
	char text[128];
	while (quit == 0)
	{
		SDL_FillRect(screen, NULL, blue);

		sprintf(text, "Congratulations! You completed level %d in %d moves and %d pushes.", level, move_counter, push_counter);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 2 * TILE, text, charset);
		DrawString(screen, screen->w / 2 - strlen("Press esc to exit or m to go back to menu...") * 8 / 2, 3 * TILE, "Press esc to exit or m to go back to menu...", charset);
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
							quit = 1;
							return 1;
							break;
						case SDLK_m:
							return 0;
							break;
					}
					break;
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					quit = 1;
					return 1;
					break;
			}
		}

	}
}

//draws a selector box, for menu
void select_box(const char *text, int highlight, int n, SDL_Surface *screen, SDL_Surface *charset, int blue, int green)
{
	if (highlight == n)
	{
		DrawRectangle(screen, 4, 4 + n * TILE + n * 2, SCREEN_WIDTH - 8, TILE, green, green);
	}
	else
	{			
		DrawRectangle(screen, 4, 4 + n * TILE + n * 2, SCREEN_WIDTH - 8, TILE, blue, blue);
	}
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 13 + n * TILE + n * 2, text, charset);
}

//menu for level selection
int level_selector(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int blue, int black, int green)
{
	FILE *level_list = fopen("./levels/levels.ini", "r");
	int amount_levels;
	fscanf(level_list, "%d;", &amount_levels);

	int *levels;
	levels = (int *) malloc(amount_levels * sizeof(int));

	for (int i = 0; i < amount_levels; ++i)
	{	
		fscanf(level_list, "%d,", &levels[i]);
	}
	fclose(level_list);

	SDL_Event event;
	int choice = 0;
	int highlight = 1;
	while(choice == 0)
	{
		SDL_FillRect(screen, NULL, black);

		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
		DrawString(screen, screen->w / 2 - strlen("CHOOSE LEVEL") * 8 / 2, 11, "CHOOSE LEVEL", charset);

		for (int i = 0; i < amount_levels; ++i)
		{
			char text[16];
			sprintf(text, "%d", levels[i]);
			select_box(text, highlight, i + 1, screen, charset, blue, green);
		}

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
						case SDLK_DOWN:
							if (highlight < amount_levels)
							{
								++highlight;
							}
							break;
						case SDLK_UP:
							if (highlight > 1)
							{
								--highlight;
							}
							break;
						case SDLK_RETURN:
							for (int i = 0; i < amount_levels; ++i)
							{
								if (highlight == i + 1)
								{
									return levels[i];									
									free(levels);
								}
							}
							break;
						case SDLK_ESCAPE:
							return 0;
							break;
					}
					break;
			}
		}
	}

	return 0;
}

//main menu
void menu(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int blue, int black, int green, int &level, int &quit)
{
	SDL_Event event;
	int choice = 0;
	int highlight = 1;
	while(choice == 0)
	{
		SDL_FillRect(screen, NULL, black);

		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
		DrawString(screen, screen->w / 2 - strlen("MENU") * 8 / 2, 11, "MENU", charset);

		select_box("CHOOSE LEVEL", highlight, 1, screen, charset, blue, green);
		select_box("LEADERBOARD", highlight, 2, screen, charset, blue, green);
		select_box("QUIT", highlight, 3, screen, charset, blue, green);

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
							choice = 1;
							quit = 1;
							break;
						case SDLK_DOWN:
							if (highlight < 3)
							{
								++highlight;
							}
							break;
						case SDLK_UP:
							if (highlight > 1)
							{
								--highlight;
							}
							break;
						case SDLK_RETURN:
							switch (highlight)
							{
								case 1:
									level = level_selector(screen, scrtex, renderer, charset, blue, black, green);
									if (level != 0)
									{										
										choice = 1;
									}
									else
									{										
										choice = 0;
									}
									break;
								case 2:
								case 3:
									quit = 1;
									choice = 1;
									break;
							}
							break;
					}
					break;
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					quit = 1;
					break;
			}
		}
	}
}