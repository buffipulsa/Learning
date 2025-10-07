#pragma once

#include <SDL3/SDL.h>

class Game 
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

public:
	Game();
	~Game();
	
	void initialize();
	void run();
	void processInput();
	void update();
	void render();
	void destroy();
};