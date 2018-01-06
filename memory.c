#include "memory.h"
#include "struct.h"

//func reads a file with level, makes a mallocated board, returns ptr to it
struct field ** make_board(unsigned int level)
{
	int n = 0, s = 0;
	FILE *level_file;
	char txt[20];
	sprintf(txt, "./levels/%d.txt", level);
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
	sprintf(txt, "./levels/%d.txt", level);
	level_file = fopen(txt, "r");
	fscanf(level_file, "%d %d ", &n, &s);
	fclose(level_file);
}