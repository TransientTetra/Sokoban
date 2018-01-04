#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define TILE 32

struct field
{
	unsigned int player = 0;
	unsigned int wall = 0;
	unsigned int barrel = 0;
	unsigned int goal = 0;
	unsigned int floor = 0;
};