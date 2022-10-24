#pragma once
#include "Surface.h"

class Sphere : public Surface {
public:
	Sphere(const double r, const Vertex center, Material m);

	~Sphere() = default;

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

private:
	double radius;
};