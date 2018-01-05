#include "struct.h"
#include "movement.h"
#include "logic.h"

void move_up(struct field **board, int n, int s)
{
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x - 1][y].wall != 1)
	{
		if (board[x - 1][y].barrel == 1)
		{
			if (board[x - 2][y].barrel != 1 && board[x - 2][y].wall != 1)
			{
				board[x][y].player = 0;
				board[x - 1][y].player = 1;
				board[x - 1][y].barrel = 0;
				board[x - 2][y].barrel = 1;
			}
		}
		else
		{
			board[x][y].player = 0;
			board[--x][y].player = 1;
		}		
	}
}

void move_down(struct field **board, int n, int s)
{
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x + 1][y].wall != 1)
	{
		if (board[x + 1][y].barrel == 1)
		{
			if (board[x + 2][y].barrel != 1 && board[x + 2][y].wall != 1)
			{
				board[x][y].player = 0;
				board[x + 1][y].player = 1;
				board[x + 1][y].barrel = 0;
				board[x + 2][y].barrel = 1;
			}
		}
		else
		{
			board[x][y].player = 0;
			board[++x][y].player = 1;
		}	
	}
}

void move_left(struct field **board, int n, int s)
{
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x][y - 1].wall != 1)
	{
		if (board[x][y - 1].barrel == 1)
		{
			if (board[x][y - 2].barrel != 1 && board[x][y - 2].wall != 1)
			{
				board[x][y].player = 0;
				board[x][y - 1].player = 1;
				board[x][y - 1].barrel = 0;
				board[x][y - 2].barrel = 1;
			}
		}
		else
		{
			board[x][y].player = 0;
			board[x][--y].player = 1;
		}
	}		
}

void move_right(struct field **board, int n, int s)
{
	int x, y;
	get_player_position(board, x, y, n, s);
	if (board[x][y + 1].wall != 1)
	{
		if (board[x][y + 1].barrel == 1)
		{
			if (board[x][y + 2].barrel != 1 && board[x][y + 2].wall != 1)
			{
				board[x][y].player = 0;
				board[x][y + 1].player = 1;
				board[x][y + 1].barrel = 0;
				board[x][y + 2].barrel = 1;
			}
		}
		else
		{
			board[x][y].player = 0;
			board[x][++y].player = 1;
		}
	}	
}