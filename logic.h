#include "draw.h"

//takes board and it's size and two ints, searches for player position and changes
//the two ints into player's position coordinates
void get_player_position(struct field **board, int &x, int &y, int n, int s);

//checks if all barrels are on on goal tiles, returns 0 if yes, 1 otherwise
int check_win(struct field **board, int n, int s);

//displays a prompt upon winning
int win_prompt(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int blue, int &quit, int level, int move_counter, int push_counter, double time);

//main menu
void menu(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int blue, int black, int green, int &level, int &quit);

//menu for level selection
int level_selector(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int blue, int black, int green);

//draws a selector box, for menu
void select_box(const char *text, int highlight, int n, int vertical_shift, SDL_Surface *screen, SDL_Surface *charset, int blue, int green);

//displays leaderboard from file for a given level
void display_leaderboard(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int level, int blue);

//adds to leaderboard
void add_to_leaderboard(int level, double time, int moves);