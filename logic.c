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
int win_prompt(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int blue, int &quit, int level, int move_counter, int push_counter, double time)
{
	SDL_Event event;
	char text[128];
	while (quit == 0)
	{
		SDL_FillRect(screen, NULL, blue);

		sprintf(text, "Congratulations! You completed level %d in %d moves including %d pushes, in %.1lf seconds!", level, move_counter, push_counter, time);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 2 * TILE, text, charset);
		DrawString(screen, screen->w / 2 - strlen("If you want to save your score in a leaderboard press l") * 8 / 2, 3 * TILE, "If you want to save your score in a leaderboard press l", charset);
		DrawString(screen, screen->w / 2 - strlen("If you want to return to the main menu press m") * 8 / 2, 4 * TILE, "If you want to return to the main menu press m", charset);
		DrawString(screen, screen->w / 2 - strlen("If you want to exit press esc") * 8 / 2, 5 * TILE, "If you want to exit press esc", charset);
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
						case SDLK_l:
							add_to_leaderboard(level, time, move_counter);
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
	int level_leaderboard = 0;
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
									level_leaderboard = level_selector(screen, scrtex, renderer, charset, blue, black, green);
									if (level_leaderboard != 0)
									{
										display_leaderboard(screen, scrtex, renderer, charset, level_leaderboard, blue);
									}
									break;
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

//displays leaderboard from file for a given level
void display_leaderboard(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int level, int blue)
{
	struct score *scores;
	char name[32];
	sprintf(name, "./leaderboards/%d.txt", level);
	FILE *leaderboard = fopen(name, "r");

	SDL_Event event;
	char text[128];
	int amount_scores = 0;
	int quit = 0;
	int sort = 0;
	while (quit == 0)
	{
		SDL_FillRect(screen, NULL, blue);

		if (leaderboard == NULL)
		{
			DrawString(screen, screen->w / 2 - strlen("There are no saved highscores for this level yet") * 8 / 2, 2 * TILE, "There are no saved highscores for this level yet", charset);
			DrawString(screen, screen->w / 2 - strlen("Press any key to go back to main menu...") * 8 / 2, 3 * TILE, "Press any key to go back to main menu...", charset);
		}
		else
		{
			sprintf(text, "LEVEL %d LEADERBOARD", level);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, TILE / 2, text, charset);
			DrawString(screen, screen->w / 2 - strlen("Press esc to return to main menu | Press s to change sorting mode") * 8 / 2, TILE, "Press esc to return to main menu | Press s to change sorting mode", charset);
			if (sort == 0)
			{
				DrawString(screen, screen->w / 2 - strlen("Currently sorting by shortest time") * 8 / 2, TILE + TILE / 2, "Currently sorting by shortest time", charset);
			}
			else if (sort == 1)
			{
				DrawString(screen, screen->w / 2 - strlen("Currently sorting by least moves") * 8 / 2, TILE + TILE / 2, "Currently sorting by least moves", charset);
			}
			DrawString(screen, screen->w / 2 - strlen("No.       Time [s]       Number of moves") * 8 / 2, 2 * TILE, "No.       Time [s]       Number of moves", charset);
			
			if (amount_scores == 0)
			{
				char character = 0;
				rewind(leaderboard);
				while(character != EOF)
				{
					character = fgetc(leaderboard);
					if (character == '@')
					{
						++amount_scores;
					}
				}
				scores = (struct score *) malloc(amount_scores * sizeof(struct score));
			}

			rewind(leaderboard);
			for (int i = 0; i < amount_scores; ++i)
			{
				int temp_time, temp_moves;
				fscanf(leaderboard, "@%d,%d;", &temp_time, &temp_moves);
				scores[i].time = temp_time;
				scores[i].moves = temp_moves;
				scores[i].number = i + 1;
			}
			if(sort == 0)
			{
				int check_sorted = 0;
				while (check_sorted == 0)
				{
					check_sorted = 1;
					for (int i = 0; i < amount_scores - 1; ++i)
					{
						if (scores[i].time > scores[i + 1].time)
						{
							check_sorted = 0;
							int temp_time = scores[i].time;
							scores[i].time = scores[i + 1].time;
							scores[i + 1].time = temp_time;
							int temp_moves = scores[i].moves;
							scores[i].moves = scores[i + 1].moves;
							scores[i + 1].moves = temp_moves;
						}
					}
				}
			}
			if(sort == 1)
			{
				int check_sorted = 0;
				while (check_sorted == 0)
				{
					check_sorted = 1;
					for (int i = 0; i < amount_scores - 1; ++i)
					{
						if (scores[i].moves > scores[i + 1].moves)
						{
							check_sorted = 0;
							int temp_time = scores[i].time;
							scores[i].time = scores[i + 1].time;
							scores[i + 1].time = temp_time;
							int temp_moves = scores[i].moves;
							scores[i].moves = scores[i + 1].moves;
							scores[i + 1].moves = temp_moves;
						}
					}
				}
			}
			for (int i = 0; i < amount_scores; ++i)
			{
				sprintf(text, "%d.", scores[i].number);
				DrawString(screen, 445, 2 * TILE + (i + 1) * TILE / 2, text, charset);
				sprintf(text, "%d s", scores[i].time);
				DrawString(screen, 555 - strlen(text) * 8 / 2, 2 * TILE + (i + 1) * TILE / 2, text, charset);
				sprintf(text, "%d", scores[i].moves);
				DrawString(screen, 700 - strlen(text) * 8 / 2, 2 * TILE + (i + 1) * TILE / 2, text, charset);
			}
		}
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					if (leaderboard == NULL)
					{
						quit = 1;
					}
					else
					{
						switch (event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								quit = 1;
								break;
							case SDLK_s:
								if (sort == 0)
								{
									sort = 1;
								}
								else if (sort == 1)
								{
									sort = 0;
								}
								break;
						}
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
	if (leaderboard != NULL)
	{
		fclose(leaderboard);
		free(scores);
	}
}

//adds to leaderboard file of given level
void add_to_leaderboard(int level, double time, int moves)
{
	char filename[32];
	sprintf(filename, "./leaderboards/%d.txt", level);
	FILE *leaderboard = fopen(filename, "a");
	fprintf(leaderboard, "@%d,%d;", (int)time, moves);
	fclose(leaderboard);
}