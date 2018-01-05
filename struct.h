#define SCREEN_WIDTH	1200
#define SCREEN_HEIGHT	480
#define BOARD_X 64
#define BOARD_Y 64
#define TILE 32

struct field
{
	unsigned int player = 0;
	unsigned int wall = 0;
	unsigned int barrel = 0;
	unsigned int goal = 0;
	unsigned int floor = 0;
};