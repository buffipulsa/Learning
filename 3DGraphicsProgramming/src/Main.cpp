#include "./Logger/Logger.h"

#include <SDL3/SDL.h>

#include <vector>


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool is_running = false;

int window_width = NULL;
int window_height = NULL;

std::vector<uint32_t>* color_buffer = new std::vector<uint32_t>;
SDL_Texture* color_buffer_texture = nullptr;

static bool initialize_window()
{
	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) 
	{
		Logger::Err("SDL_Init Error");
		return false;
	}
	Logger::Log("SDL_Init Succeeded");

	const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(1);
	if (!display_mode)
	{
		Logger::Err("SDL_DisplayMode Error");
		return false;
	}
	Logger::Log("SDL_DisplayMode Succeeded");

	window_width = display_mode->w;
	window_height = display_mode->h;

	// Create a SDL window
	window = SDL_CreateWindow(nullptr, window_width, window_height, SDL_WINDOW_BORDERLESS);
	if (!window) 
	{
		Logger::Err("SDL_CreateWindow Error");
		return false;
	}
	Logger::Log("SDL_CreateWindow Succeeded");

	// Create a SDL renderer
	renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer)
	{
		Logger::Err("SDL_CreateRenderer Error");
		return false;
	}
	Logger::Log("SDL_CreateRenderer Succeeded");

	SDL_SetWindowFullscreen(window, true);

	return true;
}

static void setup()
{
	// Allocate the required memory in bytes to hold the color buffer
	const size_t color_buffer_size = static_cast<size_t>(window_width * window_height);
	color_buffer->assign(color_buffer_size, NULL);

	if (!color_buffer)
	{
		Logger::Err("Color Buffer Assign Error");
		return;
	}

	// Creating a SDL texture that is used to display the color buffer
	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
}

static void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type)
	{
		case SDL_EVENT_QUIT:
			is_running = false;
			break;

		case SDL_EVENT_KEY_DOWN:
			if (event.key.key == SDLK_ESCAPE) 
			{
				is_running = false;
				break;
			}
	}
}

static void update()
{

}

static void draw_grid(int spacing = 50, bool dotted_or_line = true)
{
	int increment_value = 1;
	if (!dotted_or_line) {
		increment_value = spacing;
	}
	for (int y = 0; y < window_height; y += increment_value) {
		for (int x = 0; x < window_width; x += increment_value) {
			if (dotted_or_line) {
				if (y % spacing == 0 || x % spacing == 0) {
					(*color_buffer)[(window_width * y) + x] = 0xFF333333;
				}
			}
			else {
				(*color_buffer)[(window_width * y) + x] = 0xFF333333;
			}
		}
	}
}

static void draw_rect(int x, int y, int w, int h, uint32_t color) 
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			int current_x = x + i;
			int current_y = y + j;
			(*color_buffer)[(window_width * current_y) + current_x] = 0xFFFF00FF;
		}
	}
}

static void render_color_buffer()
{
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer->data(), (int)(window_width * sizeof(uint32_t)));

	SDL_RenderTexture(renderer, color_buffer_texture, NULL, NULL);
}

static void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			(*color_buffer)[(window_width * y) + x] = color;
		}
	}
}

static void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);

	draw_grid(50, false);
	draw_rect(500, 500, 250, 650, 0xFFFF0000);

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

static void destroy_window()
{
	delete(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main()
{
	is_running = initialize_window();

	setup();

	while (is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}
