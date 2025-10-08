#pragma once

#include <SDL3/SDL.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game 
{
private:
	bool is_running;
	int millisecs_prev_frame = 0;

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