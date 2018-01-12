#include "struct.h"
#include "movement.h"
#include "logic.h"

void move_up(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter)
{
	int t1, t2;
	double delta, distance = 0;
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x - 1][y].wall != 1)
	{
		if (board[x - 1][y].barrel == 1)
		{
			if (board[x - 2][y].barrel != 1 && board[x - 2][y].wall != 1)
			{
				char text[128];
				t1 = SDL_GetTicks();
				while (distance <= TILE)
				{
					t2 = SDL_GetTicks();
					delta = (t2 - t1) * 0.001;
					t1 = t2;
					global_time += delta;
					distance += PLAYERSPEED * delta;

					DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
					sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
					DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

					if (board[x][y].goal == 1)
					{
						DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
					}
					else
					{
						DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
					}
					if (board[x - 1][y].goal == 1)
					{
						DrawSurface(screen, goal, (x - 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
					}
					else
					{
						DrawSurface(screen, floor, (x - 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
					}
					DrawSurface(screen, player, x * TILE - distance + BOARD_X, y * TILE + BOARD_Y);
					DrawSurface(screen, barrel, (x - 1) * TILE - distance + BOARD_X, y * TILE + BOARD_Y);
					SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
					SDL_RenderCopy(renderer, scrtex, NULL, NULL);
					SDL_RenderPresent(renderer);
				}
				board[x][y].player = 0;
				board[x - 1][y].player = 1;
				board[x - 1][y].barrel = 0;
				board[x - 2][y].barrel = 1;
				++push_counter;
				++move_counter;
			}
		}
		else
		{
			char text[128];
			t1 = SDL_GetTicks();
			while (distance <= TILE)
			{
				t2 = SDL_GetTicks();
				delta = (t2 - t1) * 0.001;
				t1 = t2;
				global_time += delta;
				distance += PLAYERSPEED * delta;

				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
				sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

				if (board[x][y].goal == 1)
				{
					DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
				}
				else
				{
					DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
				}
				if (board[x - 1][y].goal == 1)
				{
					DrawSurface(screen, goal, (x - 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
				}
				else
				{
					DrawSurface(screen, floor, (x - 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
				}
				DrawSurface(screen, player, x * TILE - distance + BOARD_X, y * TILE + BOARD_Y);
				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}

			board[x][y].player = 0;
			board[x - 1][y].player = 1;
			++move_counter;	
		}		
	}
}

void move_down(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter)
{
	int t1, t2;
	double delta, distance = 0;
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x + 1][y].wall != 1)
	{
		if (board[x + 1][y].barrel == 1)
		{
			if (board[x + 2][y].barrel != 1 && board[x + 2][y].wall != 1)
			{
				char text[128];
				t1 = SDL_GetTicks();
				while (distance <= TILE)
				{
					t2 = SDL_GetTicks();
					delta = (t2 - t1) * 0.001;
					t1 = t2;
					global_time += delta;
					distance += PLAYERSPEED * delta;

					DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
					sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
					DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

					if (board[x][y].goal == 1)
					{
						DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
					}
					else
					{
						DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
					}
					if (board[x + 1][y].goal == 1)
					{
						DrawSurface(screen, goal, (x + 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
					}
					else
					{
						DrawSurface(screen, floor, (x + 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
					}
					DrawSurface(screen, player, x * TILE + distance + BOARD_X, y * TILE + BOARD_Y);
					DrawSurface(screen, barrel, (x + 1) * TILE + distance + BOARD_X, y * TILE + BOARD_Y);
					SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
					SDL_RenderCopy(renderer, scrtex, NULL, NULL);
					SDL_RenderPresent(renderer);
				}
				board[x][y].player = 0;
				board[x + 1][y].player = 1;
				board[x + 1][y].barrel = 0;
				board[x + 2][y].barrel = 1;
				++push_counter;
				++move_counter;
			}
		}
		else
		{
			char text[128];
			t1 = SDL_GetTicks();
			while (distance <= TILE)
			{
				t2 = SDL_GetTicks();
				delta = (t2 - t1) * 0.001;
				t1 = t2;
				global_time += delta;
				distance += PLAYERSPEED * delta;

				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
				sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

				if (board[x][y].goal == 1)
				{
					DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
				}
				else
				{
					DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
				}
				if (board[x + 1][y].goal == 1)
				{
					DrawSurface(screen, goal, (x + 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
				}
				else
				{
					DrawSurface(screen, floor, (x + 1) * TILE + BOARD_X, y * TILE + BOARD_Y);				
				}
				DrawSurface(screen, player, x * TILE + distance + BOARD_X, y * TILE + BOARD_Y);
				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}

			board[x][y].player = 0;
			board[x + 1][y].player = 1;
			++move_counter;	
		}		
	}
}

void move_left(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter)
{
	int t1, t2;
	double delta, distance = 0;
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x][y - 1].wall != 1)
	{
		if (board[x][y - 1].barrel == 1)
		{
			if (board[x][y - 2].barrel != 1 && board[x][y - 2].wall != 1)
			{
				char text[128];
				t1 = SDL_GetTicks();
				while (distance <= TILE)
				{
					t2 = SDL_GetTicks();
					delta = (t2 - t1) * 0.001;
					t1 = t2;
					global_time += delta;
					distance += PLAYERSPEED * delta;

					DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
					sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
					DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

					if (board[x][y].goal == 1)
					{
						DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
					}
					else
					{
						DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
					}
					if (board[x][y - 1].goal == 1)
					{
						DrawSurface(screen, goal, x * TILE + BOARD_X, (y - 1) * TILE + BOARD_Y);				
					}
					else
					{
						DrawSurface(screen, floor, x * TILE + BOARD_X, (y - 1) * TILE + BOARD_Y);				
					}
					DrawSurface(screen, player, x * TILE + BOARD_X, y * TILE - distance + BOARD_Y);
					DrawSurface(screen, barrel, x * TILE + BOARD_X, (y - 1) * TILE - distance + BOARD_Y);
					SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
					SDL_RenderCopy(renderer, scrtex, NULL, NULL);
					SDL_RenderPresent(renderer);
				}
				board[x][y].player = 0;
				board[x][y - 1].player = 1;
				board[x][y - 1].barrel = 0;
				board[x][y - 2].barrel = 1;
				++push_counter;
				++move_counter;
			}
		}
		else
		{
			char text[128];
			t1 = SDL_GetTicks();
			while (distance <= TILE)
			{
				t2 = SDL_GetTicks();
				delta = (t2 - t1) * 0.001;
				t1 = t2;
				global_time += delta;
				distance += PLAYERSPEED * delta;

				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
				sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

				if (board[x][y].goal == 1)
				{
					DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
				}
				else
				{
					DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
				}
				if (board[x][y - 1].goal == 1)
				{
					DrawSurface(screen, goal, x * TILE + BOARD_X, (y - 1) * TILE + BOARD_Y);				
				}
				else
				{
					DrawSurface(screen, floor, x * TILE + BOARD_X, (y - 1) * TILE + BOARD_Y);				
				}
				DrawSurface(screen, player, x * TILE + BOARD_X, y * TILE - distance + BOARD_Y);
				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}

			board[x][y].player = 0;
			board[x][y - 1].player = 1;
			++move_counter;	
		}		
	}
}

void move_right(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter)
{
	int t1, t2;
	double delta, distance = 0;
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x][y + 1].wall != 1)
	{
		if (board[x][y + 1].barrel == 1)
		{
			if (board[x][y + 2].barrel != 1 && board[x][y + 2].wall != 1)
			{
				char text[128];
				t1 = SDL_GetTicks();
				while (distance <= TILE)
				{
					t2 = SDL_GetTicks();
					delta = (t2 - t1) * 0.001;
					t1 = t2;
					global_time += delta;
					distance += PLAYERSPEED * delta;

					DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
					sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
					DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

					if (board[x][y].goal == 1)
					{
						DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
					}
					else
					{
						DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
					}
					if (board[x][y + 1].goal == 1)
					{
						DrawSurface(screen, goal, x * TILE + BOARD_X, (y + 1) * TILE + BOARD_Y);				
					}
					else
					{
						DrawSurface(screen, floor, x * TILE + BOARD_X, (y + 1) * TILE + BOARD_Y);				
					}
					DrawSurface(screen, player, x * TILE + BOARD_X, y * TILE + distance + BOARD_Y);
					DrawSurface(screen, barrel, x * TILE + BOARD_X, (y + 1) * TILE + distance + BOARD_Y);
					SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
					SDL_RenderCopy(renderer, scrtex, NULL, NULL);
					SDL_RenderPresent(renderer);
				}
				board[x][y].player = 0;
				board[x][y + 1].player = 1;
				board[x][y + 1].barrel = 0;
				board[x][y + 2].barrel = 1;
				++push_counter;
				++move_counter;
			}
		}
		else
		{
			char text[128];
			t1 = SDL_GetTicks();
			while (distance <= TILE)
			{
				t2 = SDL_GetTicks();
				delta = (t2 - t1) * 0.001;
				t1 = t2;
				global_time += delta;
				distance += PLAYERSPEED * delta;

				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, TILE, blue, blue);
				sprintf(text, "Level %d | Elapsed time: %.1lf s | Moves: %d | Pushes: %d", level, global_time, move_counter, push_counter);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

				if (board[x][y].goal == 1)
				{
					DrawSurface(screen, goal, x * TILE + BOARD_X, y * TILE + BOARD_Y);
				}
				else
				{
					DrawSurface(screen, floor, x * TILE + BOARD_X, y * TILE + BOARD_Y);					
				}
				if (board[x][y + 1].goal == 1)
				{
					DrawSurface(screen, goal, x * TILE + BOARD_X, (y + 1) * TILE + BOARD_Y);				
				}
				else
				{
					DrawSurface(screen, floor, x * TILE + BOARD_X, (y + 1) * TILE + BOARD_Y);				
				}
				DrawSurface(screen, player, x * TILE + BOARD_X, y * TILE + distance + BOARD_Y);
				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}

			board[x][y].player = 0;
			board[x][y + 1].player = 1;
			++move_counter;	
		}		
	}
}