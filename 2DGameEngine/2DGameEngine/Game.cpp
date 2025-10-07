#include "Game.h"

#include <SDL3/SDL.h>
#include <print>

Game::Game()
{
	std::println("Game constructor called");
}

Game::~Game() 
{
	std::println("Game destructor called");
}

void Game::initialize()
{
	// Initialize game resources and settings
	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
		std::println("SDL_Init Error: {}", SDL_GetError());
		return;
	} 
	std::println("SDL_Init succeeded");


	window = SDL_CreateWindow(
		NULL, 
		800,
		600,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		std::println("SDL_CreateWindow Error: {}", SDL_GetError());
		return;
	}
	std::println("SDL_Window created");

	renderer = SDL_CreateRenderer(
		window,
		NULL);

	if (!renderer) {
		std::println("SDL_CreateRenderer Error: {}", SDL_GetError());
		return;
	}
	std::println("SDL_Renderer created");


}

void Game::run()
{
	// Main game loop
	//while (true) // Replace with actual game loop condition
	//{
	//	processInput();
	//	update();
	//	render();
	//}
}

void Game::processInput()
{
	// Handle user input
}

void Game::update()
{
	// Update game state
}

void Game::render()
{
	// Render game objects
}

void Game::destroy()
{
	// Clean up resources
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		std::println("SDL_Renderer destroyed");
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
		std::println("SDL_Window destroyed");
	}
	SDL_Quit();
	std::println("SDL_Quit called");
}