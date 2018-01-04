#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define TILE 32

struct field
{
	unsigned int player;
	unsigned int wall;
	unsigned int barrel;
	unsigned int goal;
	unsigned int floor;
};