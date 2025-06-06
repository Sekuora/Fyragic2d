#pragma once
#include <glm/glm.hpp>

using glm::vec2;

struct TransformComponent
{
	vec2 location;
	vec2 scale;
	double rotation;

	TransformComponent(vec2 location(0, 0), vec2 scale(1, 1), double rotation = 0.0)
	{
		this->location = location;
		this->scale = scale;
		this->rotation = rotation;
	}
};