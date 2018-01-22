#include "draw.h"

//takes board and it's size and two ints, searches for player position and changes
//the two ints into player's position coordinates
void get_player_position(struct field **board, int &x, int &y, int n, int s);

//checks if all barrels are on on goal tiles, returns 0 if yes, 1 otherwise
int check_win(struct field **board, int n, int s);

//displays a prompt upon winning
int win_prompt(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int color, int &quit, int level, int move_counter, int push_counter, double time);

//main menu
int menu(SDL_Surface *wallpaper, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int main_color,int secondary_color, int &level, short int &graphics_version, short int &change_graphics);

//menu for level selection
int level_selector(SDL_Surface *wallpaper, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int main_color, int secondary_color);

//draws a selector box, for menu
void select_box(const char *text, int highlight, int n, int vertical_shift, SDL_Surface *screen, SDL_Surface *charset, int blue, int green);

//general purpose menu for text input, returns input text
const char * input_text(const char *title, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int color);

//displays leaderboard from file for a given level
void display_leaderboard(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Renderer *renderer, SDL_Surface *charset, int level, int color);

//adds to leaderboard
void add_to_leaderboard(int level, double time, int moves);