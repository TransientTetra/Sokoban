//takes board and it's size and two ints, searches for player position and changes
//the two ints into player's position coordinates
void get_player_position(struct field **board, int &x, int &y, int n, int s);

//checks if all barrels are on on goal tiles, returns 0 if yes, 1 otherwise
int check_win(struct field **board, int n, int s);