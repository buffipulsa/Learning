#pragma once

#include "Triangle.h"

#include <array>
#include <vector>
#include <glm/vec3.hpp>


const int N_CUBE_VERTICES = 8;
const int N_CUBE_FACES = (6 * 2);

extern std::array<glm::vec3, N_CUBE_VERTICES> cube_verticies;

extern std::array<face_t, N_CUBE_FACES> cube_faces;

// Define a struct for dynamic size meshes
struct mesh_t {
	std::vector<glm::vec3> verticies;
	std::vector<face_t> faces;
	float rotation;
};

extern mesh_t mesh;

void load_cube_mesh_data();