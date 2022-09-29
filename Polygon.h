#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "Definitions.h"

class Polygon {
public:
	virtual ~Polygon() {
		--count_polygons;
	}

	virtual bool intersection(const Direction inDirection, const Vertex start, Vertex& intPoint) = 0;

	virtual Direction calculateNormal() = 0;

	Color getColor(){ return color; }

	static std::size_t get_count_polygons();

protected:

	Polygon(const std::vector<Vertex> P, const Color c)
		: points{ P }, color { c } {
		++count_polygons;
	}

	Polygon(const Polygon& C) {
		++count_polygons;
	}

	Color color;
	Direction normal;
	std::vector<Vertex> points;

	static std::size_t count_polygons;
};