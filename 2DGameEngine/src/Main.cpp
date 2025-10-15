
#include "./Game/Game.h"
#include "./Logger/Logger.h"


int main()
{
	Game game;

	game.initialize();
	game.run();
	game.destroy();

	Logger::Log("Hello, 2D Game Engine!");
	return 0;
}
