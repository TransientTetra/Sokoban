#include "draw.h"

void move_up(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter);

void move_down(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter);

void move_left(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter);

void move_right(int level, int blue, double &global_time,SDL_Surface *charset, SDL_Renderer *renderer, SDL_Texture *scrtex, SDL_Surface *screen, SDL_Surface *player, SDL_Surface *barrel, SDL_Surface *floor, SDL_Surface *goal, struct field **board, int n, int s, unsigned int &move_counter, unsigned int &push_counter);