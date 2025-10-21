
#include "Display.h"
#include "../Logger/Logger.h"


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int window_width = NULL;
int window_height = NULL;

std::vector<uint32_t>* color_buffer = new std::vector<uint32_t>;
SDL_Texture* color_buffer_texture = nullptr;

bool initialize_window()
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

void destroy_window()
{
	delete(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void draw_grid(int spacing, bool dotted_or_line)
{
	int increment_value = 1;
	if (!dotted_or_line) {
		increment_value = spacing;
	}
	for (int y = 0; y < window_height; y += increment_value) {
		for (int x = 0; x < window_width; x += increment_value) {
			if (dotted_or_line) {
				if (y % spacing == 0 || x % spacing == 0) {
					draw_pixel(x, y, 0xFF333333);
					//(*color_buffer)[(window_width * y) + x] = 0xFF333333;
				}
			}
			else {
				draw_pixel(x, y, 0xFF333333);
				//(*color_buffer)[(window_width * y) + x] = 0xFF333333;
			}
		}
	}
}

void draw_pixel(int x, int y, uint32_t color)
{
	if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
		(*color_buffer)[(window_width * y) + x] = color;
	}
}

void draw_rect(int x, int y, int w, int h, uint32_t color)
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			int current_x = x + i;
			int current_y = y + j;
			draw_pixel(current_x, current_y, color);
			//(*color_buffer)[(window_width * current_y) + current_x] = 0xFFFF00FF;
		}
	}
}

void draw_line(int x0, int y0, int x1, int y1)
{
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)side_length;
	float y_inc = delta_y / (float)side_length;

	float current_x = x0;
	float current_y = y0;

	for (int i = 0; i <= side_length; i++) {
		draw_pixel(round(current_x), round(current_y), 0xFFFFFFFF);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void render_color_buffer()
{
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer->data(), (int)(window_width * sizeof(uint32_t)));

	SDL_RenderTexture(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			draw_pixel(x, y, color);
		}
	}
}