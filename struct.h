#define SCREEN_WIDTH	1200
#define SCREEN_HEIGHT	480
#define BOARD_X 64
#define BOARD_Y 64
#define TILE 32

struct field
{
	unsigned int player;
	unsigned int wall;
	unsigned int barrel;
	unsigned int goal;
	unsigned int floor;
};