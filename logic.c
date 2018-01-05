#include "struct.h"
#include "logic.h"

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