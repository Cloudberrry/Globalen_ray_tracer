#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include "Polygon.h"
#include "Color.h"

class Ray {
public:
	Ray() {}
	~Ray() {
		/*next->previous = previous;
		previous->next = next;*/
	}
private:
	glm::vec4 start;
	glm::vec4 end;
	Polygon* surface; // Surface on which the starting vertex is located
	Color color;
	Ray* next;
	Ray* previous;
	glm::vec3 direction;

};