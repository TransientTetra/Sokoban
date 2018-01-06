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