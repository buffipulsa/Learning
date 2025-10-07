#include "Game.h"

#include <print>
#include <filesystem>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


Game::Game()
{
	is_running = false;
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

	const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(1);
	if (!display_mode)
	{
		std::println("SDL_DisplayMode Error: {}", SDL_GetError());
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
		std::println("SDL_CreateWindow Error: {}", SDL_GetError());
		return;
	}
	std::println("SDL_Window created");

	renderer = SDL_CreateRenderer(
		window,
		nullptr
	);

	if (!renderer) {
		std::println("SDL_CreateRenderer Error: {}", SDL_GetError());
		return;
	}
	std::println("SDL_Renderer created");

	if (!SDL_SetRenderVSync(renderer, 1))
	{
		std::println("SDL_SetRenderVSync Error: {}", SDL_GetError());
		return;
	}
	std::println("SDL_SetRenderVSync on!");

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

void Game::setup()
{
	// Initialize game objects

}

void Game::update()
{
	// Update game state
}

void Game::render()
{
	// Render game objects
	SDL_SetRenderDrawColor(renderer,21,21,21,255);

	SDL_RenderClear(renderer);

	// Draw a PNG texture
	std::filesystem::path assets = std::filesystem::path(PROJECT_SOURCE_DIR) / "assets";
	std::filesystem::path image_path = assets / "images" / "tank-tiger-right.png";
	std::string utf8 = image_path.string();
	if (std::filesystem::exists(image_path)) {
		std::println("Missing file: %s", utf8.c_str());
	}
	//std::println("{}", image_path.string());
	SDL_Surface* surface = IMG_Load(utf8.c_str());
	if (!surface)
	{
		std::println("IMG_Load Error: {}", SDL_GetError());
		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	const SDL_FRect dstRect = { 10,10,32,32 };
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