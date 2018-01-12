
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			printf("%d", board[i][j].wall);
		}
		printf("\n");
	}

	//demo
		{
			for (int i = 0; i < 21; ++i)
				{
					for (int j = 0; j < 16; ++j)
					{
						DrawSurface(screen, floor, i * TILE, j * TILE);
						if ((i % 3 == 0 && j % 3 == 0) || (i == 1 || i == 0 || i == 20 || j == 1 || j == 0 || j == 15))
						{
							DrawSurface(screen, wall, i * TILE, j * TILE);
						}
					}
				}
				
				DrawSurface(screen, barrel, 8 * TILE, 8 * TILE);
				DrawSurface(screen, goal, 7 * TILE, 7 * TILE);
				DrawSurface(screen, player, 2 * TILE + x * TILE, 2 * TILE + y * TILE);
		}