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