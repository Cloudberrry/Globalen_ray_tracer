#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "Color.h"

class Polygon {
public:
	virtual ~Polygon() {
		--count_polygons;
	}

	virtual bool intersection(const glm::vec3 inVec, const glm::vec3 start, glm::vec3& intPoint) = 0;

	static std::size_t get_count_polygons();

protected:

	Polygon(const std::vector<glm::vec3> P, const Color c)
		: points{ P }, color { c }, normal{ glm::vec3(0.0, 0.0, 0.0) } {
		++count_polygons;
	}

	Polygon(const Polygon& C) {
		++count_polygons;
	}

	Color color;
	glm::vec3 normal;
	std::vector<glm::vec3> points;

	static std::size_t count_polygons;
};