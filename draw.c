#include "draw.h"
#include "struct.h"


// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text)
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	}
}

// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int y, int x) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};

	// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
	};

	// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};

// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};	

//this func draws the board
void draw_board(int n, int s, struct field **board, unsigned int level, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *floor, SDL_Surface *barrel, SDL_Surface *wall, SDL_Surface *goal, SDL_Surface *goal_barrel)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			if (board[i][j].wall == 1)
			{
				DrawSurface(screen, wall, i * TILE + BOARD_X, j * TILE + BOARD_Y);
			}
			else if (board[i][j].goal == 1)
			{
				DrawSurface(screen, goal, i * TILE + BOARD_X, j * TILE + BOARD_Y);
			}
			else if (board[i][j].floor == 1)
			{
				DrawSurface(screen, floor, i * TILE + BOARD_X, j * TILE + BOARD_Y);
			}
			if (board[i][j].barrel == 1)
			{
				if (board[i][j].goal == 1)
				{
					DrawSurface(screen, goal_barrel, i * TILE + BOARD_X, j * TILE + BOARD_Y);
				}
				else
				{
					DrawSurface(screen, barrel, i * TILE + BOARD_X, j * TILE + BOARD_Y);
				}
			}
			if (board[i][j].player == 1)
			{
				DrawSurface(screen, player, i * TILE + BOARD_X, j * TILE + BOARD_Y);
			}
		}
	}
}