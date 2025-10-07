
#include "2DGameEngine.h"


int main()
{
	Game game;

	game.initialize();
	game.run();
	game.destroy();

	std::println("Hello, 2D Game Engine!");
	return 0;
}
