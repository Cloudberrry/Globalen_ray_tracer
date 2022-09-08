#pragma once
#include <iostream>
#include <vector>
#include "Ray.h"
#include "Color.h"

class Polygon {
public:
	virtual ~Polygon() {
		--count_polygons;
	}

	virtual glm::vec4 intersection(const Ray& ray) = 0;
	virtual glm::vec4 calculateNormal() = 0;

	static std::size_t get_count_polygons();

protected:

	Polygon() {
		++count_polygons;
	}

	Polygon(const Polygon&) {
		++count_polygons;
	}

	Color color;
	glm::vec4 normal;

	static std::size_t count_polygons;
private:
};