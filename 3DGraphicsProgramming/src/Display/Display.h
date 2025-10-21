#pragma once

#include <SDL3/SDL.h>
#include <vector>


const int FPS = 30;
const float MILLISECS_PER_FRAME = (1000 / FPS);

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern int window_width;
extern int window_height;

extern std::vector<uint32_t>* color_buffer;
extern SDL_Texture* color_buffer_texture;

bool initialize_window();
void destroy_window();
void draw_grid(int spacing, bool dotted_or_line);
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int w, int h, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1);
void render_color_buffer();
void clear_color_buffer(uint32_t color);