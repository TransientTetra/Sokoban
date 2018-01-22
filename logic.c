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
int win_prompt(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int color, int &quit, int level, int move_counter, int push_counter, double time)
{
	SDL_Event event;
	char text[128];
	while (quit == 0)
	{
		SDL_FillRect(screen, NULL, color);

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
							add_to_leaderboard(level, input_text("PLEASE ENTER YOUR NAME", screen, scrtex, renderer, charset, color), time, move_counter);
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
void select_box(const char *text, int highlight, int n, int vertical_shift, SDL_Surface *screen, SDL_Surface *charset, int blue, int green)
{
	if (highlight == n)
	{
		DrawRectangle(screen, screen->w / 3, 4 + n * TILE + n * 2 + vertical_shift, screen->w / 3, TILE, green, green);
	}
	else
	{			
		DrawRectangle(screen, screen->w / 3, 4 + n * TILE + n * 2 + vertical_shift, screen->w / 3, TILE, blue, blue);
	}
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 13 + n * TILE + n * 2 + vertical_shift, text, charset);
}

//menu for level selection
int level_selector(SDL_Surface *wallpaper, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int main_color, int secondary_color)
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
		DrawSurface(screen, wallpaper, 300, 400);

		select_box("CHOOSE LEVEL", highlight, 0, VERTICAL_MENU_ORIENT / 2, screen, charset, main_color, secondary_color);
		select_box("Return to main menu", highlight, 1, VERTICAL_MENU_ORIENT / 2, screen, charset, main_color, secondary_color);

		for (int i = 0; i < amount_levels; ++i)
		{
			char text[16];
			sprintf(text, "%d", levels[i]);
			select_box(text, highlight, i + 2, VERTICAL_MENU_ORIENT / 2, screen, charset, main_color, secondary_color);
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
							if (highlight < amount_levels + 1)
							{
								++highlight;
							}
							else highlight = 1;
							break;
						case SDLK_UP:
							if (highlight > 1)
							{
								--highlight;
							}
							else highlight = amount_levels + 1;
							break;
						case SDLK_RETURN:
							for (int i = 0; i < amount_levels; ++i)
							{
								if (highlight == i + 2)
								{
									return levels[i];									
									free(levels);
								}
								if (highlight == 1)
								{
									return 0;
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
int menu(SDL_Surface *wallpaper, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int main_color, int secondary_color, int &level, short int &graphics_version, short int &change_graphics)
{
	SDL_Event event;
	int level_leaderboard = 0;
	int choice = 0;
	int highlight = 1;
	while(choice == 0)
	{
		DrawSurface(screen, wallpaper, 300, 400);

		DrawRectangle(screen, screen->w / 3, 4 + VERTICAL_MENU_ORIENT, screen->w / 3, TILE, main_color, main_color);
		DrawString(screen, screen->w / 2 - strlen("MENU") * 8 / 2, 11 + VERTICAL_MENU_ORIENT, "MENU", charset);

		select_box("CHOOSE LEVEL", highlight, 1, VERTICAL_MENU_ORIENT, screen, charset, main_color, secondary_color);
		select_box("LEADERBOARD", highlight, 2, VERTICAL_MENU_ORIENT, screen, charset, main_color, secondary_color);
		select_box("INPUT CODE", highlight, 3, VERTICAL_MENU_ORIENT, screen, charset, main_color, secondary_color);
		select_box("QUIT", highlight, 4, VERTICAL_MENU_ORIENT, screen, charset, main_color, secondary_color);

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
							if (highlight < 4)
							{
								++highlight;
							}
							else highlight = 1;
							break;
						case SDLK_UP:
							if (highlight > 1)
							{
								--highlight;
							}
							else highlight = 4;
							break;
						case SDLK_RETURN:
							switch (highlight)
							{
								case 1:
									level = level_selector(wallpaper, screen, scrtex, renderer, charset, main_color, secondary_color);
									if (level != 0)
									{										
										return 0;
									}
									else
									{										
										choice = 0;
									}
									break;
								case 2:
									level_leaderboard = level_selector(wallpaper, screen, scrtex, renderer, charset, main_color, secondary_color);
									if (level_leaderboard != 0)
									{
										display_leaderboard(screen, scrtex, renderer, charset, level_leaderboard, main_color);
									}
									break;
								case 3:
									if (strcmp(input_text("ENTER A SECRET CODE", screen, scrtex, renderer, charset, main_color), HAWAII_CODE) == 0)
									{
										change_graphics = 1;
										graphics_version = 1;
										wallpaper = SDL_LoadBMP("./art/wallpaper_hawaii.bmp");
									}
									break;
								case 4:
									return 1;
									break;
							}
							break;
					}
					break;
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					return 1;
					break;
			}
		}
	}
}

//general purpose menu for text input, returns input text
const char * input_text(const char *title, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int color)
{
	char *return_text;
	return_text = (char *) malloc(32 * sizeof(char));
	return_text[0] = '\0';
	SDL_Event event;
	while (1)
	{
		SDL_FillRect(screen, NULL, color);

		DrawString(screen, screen->w / 2 - strlen(title) * 8 / 2, 4 * TILE, title, charset);
		DrawString(screen, screen->w / 2 - strlen(return_text) * 8 / 2, 5 * TILE, return_text, charset);

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
							return "0";
							break;
						case SDLK_RETURN:
							return return_text;
							break;
						case SDLK_BACKSPACE:
							return_text[strlen(return_text) - 1] = '\0';
							break;
						case SDLK_s:
							strcat(return_text, "s");
							break;
						case SDLK_q:
							strcat(return_text, "q");
							break;
						case SDLK_w:
							strcat(return_text, "w");
							break;
						case SDLK_e:
							strcat(return_text, "e");
							break;
						case SDLK_r:
							strcat(return_text, "r");
							break;
						case SDLK_t:
							strcat(return_text, "t");
							break;
						case SDLK_y:
							strcat(return_text, "y");
							break;
						case SDLK_u:
							strcat(return_text, "u");
							break;
						case SDLK_i:
							strcat(return_text, "i");
							break;
						case SDLK_o:
							strcat(return_text, "o");
							break;
						case SDLK_p:
							strcat(return_text, "p");
							break;
						case SDLK_a:
							strcat(return_text, "a");
							break;
						case SDLK_d:
							strcat(return_text, "d");
							break;
						case SDLK_f:
							strcat(return_text, "f");
							break;
						case SDLK_g:
							strcat(return_text, "g");
							break;
						case SDLK_h:
							strcat(return_text, "h");
							break;
						case SDLK_j:
							strcat(return_text, "j");
							break;
						case SDLK_k:
							strcat(return_text, "k");
							break;
						case SDLK_l:
							strcat(return_text, "l");
							break;
						case SDLK_z:
							strcat(return_text, "z");
							break;
						case SDLK_x:
							strcat(return_text, "x");
							break;
						case SDLK_c:
							strcat(return_text, "c");
							break;
						case SDLK_v:
							strcat(return_text, "v");
							break;
						case SDLK_b:
							strcat(return_text, "b");
							break;
						case SDLK_n:
							strcat(return_text, "n");
							break;
						case SDLK_m:
							strcat(return_text, "m");
							break;
					}
					break;
				case SDL_QUIT:
					return "0";
					break;
			}
		}
	}	
}

//displays leaderboard from file for a given level
void display_leaderboard(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int level, int color)
{
	struct score *scores;
	char name[32];
	sprintf(name, "./leaderboards/%d.ldr", level);
	FILE *leaderboard = fopen(name, "r");

	SDL_Event event;
	char text[128];
	int amount_scores = 0;
	int quit = 0;
	int sort = 0;
	while (quit == 0)
	{
		SDL_FillRect(screen, NULL, color);

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
			DrawString(screen, screen->w / 3 - strlen("No.") * 8 / 2, 2 * TILE, "No.", charset);
			DrawString(screen, screen->w / 2 - strlen("Time [s]") * 8 / 2, 2 * TILE, "Time [s]", charset);
			DrawString(screen, screen->w * 2 / 3 - strlen("Moves") * 8 / 2, 2 * TILE, "Moves", charset);
			
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
				char temp_name[32];
				int temp_time, temp_moves;
				fscanf(leaderboard, "@%s,%d,%d;", temp_name, &temp_time, &temp_moves);
				strcpy(scores[i].name, temp_name);
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
				DrawString(screen, screen->w / 3 - strlen(text), 2 * TILE + (i + 1) * TILE / 2, text, charset);
				sprintf(text, "%d s", scores[i].time);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 2 * TILE + (i + 1) * TILE / 2, text, charset);
				sprintf(text, "%d", scores[i].moves);
				DrawString(screen, screen->w * 2 / 3 - strlen(text) * 8 / 2, 2 * TILE + (i + 1) * TILE / 2, text, charset);
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
void add_to_leaderboard(int level, const char *name, double time, int moves)
{
	char filename[32];
	sprintf(filename, "./leaderboards/%d.ldr", level);
	FILE *leaderboard = fopen(filename, "a");
	fprintf(leaderboard, "@%s,%d,%d;", name, (int)time, moves);
	fclose(leaderboard);
}