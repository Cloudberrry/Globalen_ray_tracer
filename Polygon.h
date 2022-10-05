#pragma once
#include <iostream>
#include <vector>
#include "Material.h"

class Polygon {
public:
	virtual ~Polygon() = default;

	Polygon(const Polygon& C) = delete;

	virtual bool intersection(const Direction inDirection, const Vertex start, Vertex& intPoint) = 0;

	virtual Direction calculateNormal() = 0;

	std::vector<Vertex> getPoints() { return points; }

	Material getMaterial() { return material; }

protected:

	Polygon(const std::vector<Vertex> P, const Material m)
		: points{ P }, material { m } {
	}

	Material material;
	Direction normal;
	std::vector<Vertex> points;
};