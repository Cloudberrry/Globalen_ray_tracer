#pragma once
#include <iostream>
#include <vector>
#include "Material.h"

class Surface {
public:
	virtual ~Surface() = default;

	Surface(const Surface& C) = default;

	virtual bool intersection(const Direction inDirection, const Vertex start, Vertex& intPoint) = 0;

	std::vector<Vertex> getPoints() const { return points; }

	Material getMaterial() const { return material; }

	Direction getNormal() const { return normal; }

protected:

	Surface(const std::vector<Vertex>& P, const Material m)
		: points{ P }, material { m }
	{

	}
	

	Material material;
	Direction normal;
	std::vector<Vertex> points;
};