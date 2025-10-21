
#include "Mesh.h"


mesh_t mesh = {
	.verticies {},
	.faces {},
	.rotation = 0
};

std::array<glm::vec3, N_CUBE_VERTICES> cube_verticies{
	glm::vec3 {-1,-1,-1}, // 1
	glm::vec3 {-1,1,-1},  // 2
	glm::vec3 {1,1,-1},   // 3
	glm::vec3 {1,-1,-1},  // 4
	glm::vec3 {1,1,1},    // 5
	glm::vec3 {1,-1,1},   // 6
	glm::vec3 {-1,1,1},   // 7
	glm::vec3 {-1,-1,1},  // 8
};

std::array<face_t, N_CUBE_FACES> cube_faces{
	// front
	face_t {.a = 1, .b = 2, .c = 3 },
	face_t {.a = 1, .b = 3, .c = 4 },
	// right
	face_t {.a = 4, .b = 3, .c = 5 },
	face_t {.a = 4, .b = 5, .c = 6 },
	// back
	face_t {.a = 6, .b = 5, .c = 7 },
	face_t {.a = 6, .b = 7, .c = 8 },
	// left
	face_t {.a = 8, .b = 7, .c = 2 },
	face_t {.a = 8, .b = 2, .c = 1 },
	// top
	face_t {.a = 2, .b = 7, .c = 5 },
	face_t {.a = 2, .b = 5, .c = 3 },
	// bottom
	face_t {.a = 6, .b = 8, .c = 1 },
	face_t {.a = 6, .b = 1, .c = 4 },
};

void load_cube_mesh_data() {
	for (int i = 0; i < N_CUBE_VERTICES; i++) {
		mesh.verticies.push_back(cube_verticies[i]);
	}
	
	for (int i = 0; i < N_CUBE_FACES; i++) {
		mesh.faces.push_back(cube_faces[i]);
	}
}