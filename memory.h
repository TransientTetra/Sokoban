#include <stdio.h>
#include <stdlib.h>

//func reads a file with level, makes a mallocated board, returns ptr to it
struct field ** make_board(unsigned int level);

//frees up mallocated previously board
void del_board(struct field ** board, int n);

//this func opens level file, reads it's dimensions and alters given variables
void get_level_size(unsigned int level, int &n, int &s);