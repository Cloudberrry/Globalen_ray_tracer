#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "Material.h"

class Polygon {
public:
	virtual ~Polygon() {
		--count_polygons;
	}

	Polygon(const Polygon& C) = delete;

	virtual bool intersection(const Direction inDirection, const Vertex start, Vertex& intPoint) = 0;

	virtual Direction calculateNormal() = 0;

	Material getMaterial(){ return material; }

	static std::size_t get_count_polygons();

protected:

	Polygon(const std::vector<Vertex> P, const Material m)
		: points{ P }, material { m } {
		++count_polygons;
	}

	Material material;
	Direction normal;
	std::vector<Vertex> points;

	static std::size_t count_polygons;
};