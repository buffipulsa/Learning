#include "Game.h"
#include "Logger.h"

#include <iostream>
#include <print>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>


Game::Game()
{
	is_running = false;
	Logger::Log("Game constructor called");
}

Game::~Game() 
{
	Logger::Log("Game destructor called");
}

void Game::initialize()
{
	// Initialize game resources and settings
	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
		Logger::Err("SDL_Init Error");
		return;
	} 
	Logger::Log("SDL_Init succeeded");

	const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(1);
	if (!display_mode)
	{
		Logger::Err("SDL_DisplayMode Error");
		return;
	}

	window_width = 800; // display_mode->w;
	window_height = 600; // display_mode->h;
	window = SDL_CreateWindow(
		nullptr, 
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		Logger::Err("SDL_CreateWindow Error");
		return;
	}
	Logger::Log("SDL_Window created");

	renderer = SDL_CreateRenderer(
		window,
		nullptr
	);

	if (!renderer) {
		Logger::Err("SDL_CreateRenderer Error");
		return;
	}
	Logger::Log("SDL_Renderer created");

	if (!SDL_SetRenderVSync(renderer, 1))
	{
		Logger::Err("SDL_SetRenderVSync Error");
		return;
	}
	Logger::Log("SDL_SetRenderVSync on!");

	SDL_SetWindowFullscreen(window, true);

	is_running = true;
}

void Game::run()
{
	// Main game loop
	setup();
	while (is_running) // Replace with actual game loop condition
	{
		processInput();
		update();
		render();
	}
	
}

void Game::processInput()
{
	// Handle user input
	SDL_Event sdl_event;
	while (SDL_PollEvent(&sdl_event))
	{
		switch (sdl_event.type)
		{
			case SDL_EVENT_QUIT:
				is_running = false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if(sdl_event.key.key == SDLK_ESCAPE)
				{
					is_running = false;
				}
				break;
		}
	}
}

glm::vec2 player_position;
glm::vec2 player_velocity;

void Game::setup()
{
	// Initialize game objects
	player_position = glm::vec2(10.0, 20.0);
	player_velocity = glm::vec2(10.0, 5.0);
}

void Game::update()
{
	// Update game state
	int time_to_wait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecs_prev_frame);
	if (time_to_wait > 0 && time_to_wait <= MILLISECS_PER_FRAME) 
	{
		SDL_Delay(time_to_wait);
	}

	double delta_time = (SDL_GetTicks() - millisecs_prev_frame) / 1000.0;

	millisecs_prev_frame = SDL_GetTicks();

	player_position.x += player_velocity.x * delta_time;
	player_position.y += player_velocity.y * delta_time;
}	

void Game::render()
{
	// Render game objects
	SDL_SetRenderDrawColor(renderer,21,21,21,255);

	SDL_RenderClear(renderer);

	// Draw a PNG texture
	SDL_Surface* surface = IMG_Load("E:/Learning/2DGameEngine/2DGameEngine/assets/images/tank-tiger-right.png");
	if (!surface)
	{
		Logger::Err("IMG_Load Error");
		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		Logger::Err("SDL_CreateTextureFromSurface Error");
		return;
	}
	SDL_DestroySurface(surface);

	const SDL_FRect dstRect = { player_position.x,player_position.y,32,32 };
	SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);

}

void Game::destroy()
{
	// Clean up resources
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		Logger::Log("SDL_Renderer destroyed");
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
		Logger::Log("SDL_Window destroyed");
	}
	SDL_Quit();
	Logger::Log("SDL_Quit called");
}