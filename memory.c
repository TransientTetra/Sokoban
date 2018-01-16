#include "memory.h"
#include "struct.h"

//func reads a file with level, makes a mallocated board, returns ptr to it
struct field ** make_board(unsigned int level)
{
	int n = 0, s = 0;
	FILE *level_file;
	char txt[20];
	sprintf(txt, "./levels/%d.sok", level);
	level_file = fopen(txt, "r");
	fscanf(level_file, "%d %d ", &n, &s);

	struct field ** board;
	board = (struct field **) malloc(n * sizeof(struct field *));

	for (int i = 0; i < n; ++i)
	{
		board[i] = (struct field *) malloc(s * sizeof(struct field));
	}

	zero_board(board, n, s);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			char temp = fgetc(level_file);
			if (temp == 'W')
			{
				board[i][j].wall = 1;
			}
			else if (temp == 'P')
			{
				board[i][j].player = 1;
				board[i][j].floor = 1;
			}
			else if (temp == 'O')
			{
				board[i][j].player = 1;
				board[i][j].goal = 1;
			}
			else if (temp == 'B')
			{
				board[i][j].barrel = 1;
				board[i][j].floor = 1;
			}
			else if (temp == 'K')
			{
				board[i][j].barrel = 1;
				board[i][j].goal = 1;
			}
			else if (temp == 'F')
			{
				board[i][j].floor = 1;
			}
			else if (temp == 'G')
			{
				board[i][j].goal = 1;
			}			
		}
	}


	fclose(level_file);

	return board;
}

//zeroes all fields in a board
void zero_board(struct field ** board, int n, int s)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			board[i][j].wall = 0;
			board[i][j].player = 0;
			board[i][j].floor = 0;
			board[i][j].barrel = 0;
			board[i][j].goal = 0;
		}
	}
}

//frees up mallocated previously board
void del_board(struct field ** board, int n)
{
	for (int i = 0; i < n; ++i)
	{
		free(board[i]);
	}
	free(board);
}

//this func opens level file, reads it's dimensions and alters given variables
void get_level_size(unsigned int level, int &n, int &s)
{
	FILE *level_file;
	char txt[20];
	sprintf(txt, "./levels/%d.sok", level);
	level_file = fopen(txt, "r");
	fscanf(level_file, "%d %d ", &n, &s);
	fclose(level_file);
}

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
	SDL_Texture **scrtex,
	SDL_Window **window,
	SDL_Renderer **renderer)
{
	*charset = SDL_LoadBMP("./cs8x8.bmp");
	if(*charset == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	}
	SDL_SetColorKey(*charset, true, 0x000000);

	*player = SDL_LoadBMP(player_graphic_location);
	if(*player == NULL)
	{
		printf("SDL_LoadBMP(player.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*charset);
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	}

	*floor = SDL_LoadBMP(floor_graphic_location);
	if(*floor == NULL)
	{
		printf("SDL_LoadBMP(floor.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*player);
		SDL_FreeSurface(*charset);
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	}

	*wall = SDL_LoadBMP(wall_graphic_location);
	if(*wall == NULL)
	{
		printf("SDL_LoadBMP(wall.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*floor);
		SDL_FreeSurface(*player);
		SDL_FreeSurface(*charset);
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	}

	*barrel = SDL_LoadBMP(barrel_graphic_location);
	if(*barrel == NULL)
	{
		printf("SDL_LoadBMP(barrel.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*wall);
		SDL_FreeSurface(*floor);
		SDL_FreeSurface(*player);
		SDL_FreeSurface(*charset);
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	}

	*goal = SDL_LoadBMP(goal_graphic_location);
	if(*goal == NULL)
	{
		printf("SDL_LoadBMP(goal.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*barrel);
		SDL_FreeSurface(*wall);
		SDL_FreeSurface(*floor);
		SDL_FreeSurface(*player);
		SDL_FreeSurface(*charset);
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	}

	*goal_barrel = SDL_LoadBMP(goal_barrel_graphic_location);
	if(*goal_barrel == NULL)
	{
		printf("SDL_LoadBMP(goal_barrel.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*goal);
		SDL_FreeSurface(*barrel);
		SDL_FreeSurface(*wall);
		SDL_FreeSurface(*floor);
		SDL_FreeSurface(*player);
		SDL_FreeSurface(*charset);
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	}	
}