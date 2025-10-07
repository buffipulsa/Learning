#pragma once

#include <SDL3/SDL.h>

class Game 
{
private:
	bool is_running;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

public:
	Game();
	~Game();
	
	void initialize();
	void run();
	void processInput();
	void setup();
	void update();
	void render();
	void destroy();

	int window_width = 0;
	int window_height = 0;

};