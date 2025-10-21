#pragma once

#include <glm/vec2.hpp>

struct face_t {
	int a;
	int b;
	int c;
};

struct triangle_t {
	glm::vec2 points[3];
};