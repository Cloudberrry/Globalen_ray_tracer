#pragma once
#include <iostream>
#include <vector>
#include "Material.h"

class Surface {
public:
	virtual ~Surface() = default;

	Surface(const Surface& C) = delete;

	virtual bool intersection(const Direction inDirection, const Vertex start, Vertex& intPoint) = 0;

	std::vector<Vertex> getPoints() { return points; }

	Material getMaterial() { return material; }

	Direction getNormal() { return normal; }

protected:

	Surface(const std::vector<Vertex> P, const Material m)
		: points{ P }, material { m }
	{

	}

	Material material;
	Direction normal;
	std::vector<Vertex> points;
};