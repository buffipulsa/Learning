#include "./Logger/Logger.h"
#include "./Display/Display.h"
#include "./Mesh/Mesh.h"

#include <SDL3/SDL.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include <vector>


std::vector<triangle_t> triangles_to_render;

glm::vec3 camera_position{ 0,0,-5 };
float rotation = 0.0;
	
float fov_factor = 640;

bool is_running = false;

uint64_t prev_frame_time = 0;


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

	load_cube_mesh_data();
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

static glm::vec2 project(glm::vec3 point)
{
	return glm::vec2{ (fov_factor * point.x) / point.z, (fov_factor * point.y) / point.z};
}

static void update()
{
	// Timestamp setup
	int time_to_wait = MILLISECS_PER_FRAME - (SDL_GetTicks() - prev_frame_time);
	if (time_to_wait > 0 && time_to_wait <= MILLISECS_PER_FRAME)
	{
		SDL_Delay(time_to_wait);
	}

	double delta_time = (SDL_GetTicks() - prev_frame_time) / 1000.0;

	prev_frame_time = SDL_GetTicks();

	glm::vec3 mesh_center = { 0.0f, 0.0f, 0.0f };
	for (const auto& v : cube_verticies) {
		mesh_center += v;
	}

	mesh.rotation += 0.05;

	glm::vec3 rotation_axis = glm::normalize(glm::vec3{ 1,0,1 });

	// Loop all triangle faces of our mesh
	for (int i = 0; i < mesh.faces.size(); i++) {
		face_t mesh_face = mesh.faces[i];
		glm::vec3 face_vertices[3];
		face_vertices[0] = mesh.verticies[mesh_face.a - 1];
		face_vertices[1] = mesh.verticies[mesh_face.b - 1];
		face_vertices[2] = mesh.verticies[mesh_face.c - 1];

		triangle_t projected_triangle;

		// Loop all three verticies of this current face and apply tranformations
		for (int j = 0; j < 3; j++) {
			glm::vec3 transformed_vertex = face_vertices[j];

			transformed_vertex -= mesh_center;

			transformed_vertex = glm::rotate(transformed_vertex, mesh.rotation, rotation_axis);

			// Translate the vertex into camera space (world - camera)
			transformed_vertex -= camera_position;

			glm::vec2 projected_point = project(transformed_vertex);

			projected_point.x = projected_point.x + (window_width / 2);
			projected_point.y = -projected_point.y + (window_height / 2);
		
			projected_triangle.points[j] = projected_point;
		}

		// Save the projected triangle to the array of triangles to render
		triangles_to_render.push_back(projected_triangle);
	}
}

static void render()
{
	clear_color_buffer(0xFF000000);

	draw_grid(50, false);

	for (int i = 0; i < triangles_to_render.size(); i++) {
		triangle_t triangle = triangles_to_render[i];

		draw_rect(triangle.points[0].x, triangle.points[0].y, 5, 5, 0xFFFFFF00);
		draw_rect(triangle.points[1].x, triangle.points[1].y, 5, 5, 0xFFFFFF00);
		draw_rect(triangle.points[2].x, triangle.points[2].y, 5, 5, 0xFFFFFF00);

		draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y);
		draw_line(triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y);
		draw_line(triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y);
	}

	triangles_to_render.clear();

	render_color_buffer();

	SDL_RenderPresent(renderer);
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
