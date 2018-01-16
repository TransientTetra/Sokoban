#include"./SDL-2.0.7/include/SDL.h"
#include"./SDL-2.0.7/include/SDL_main.h"


void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );

Uint32 get_pixel32( SDL_Surface *surface, int x, int y );

void flip_horizontal( SDL_Surface*& image );

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);

// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);

// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

//this func draws the board
void draw_board(int n, int s, struct field **board, unsigned int level, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *floor, SDL_Surface *barrel, SDL_Surface *wall, SDL_Surface *goal, SDL_Surface *goal_barrel);