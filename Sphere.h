#pragma once
#include "Surface.h"

class Sphere : public Surface {
public:
	Sphere(const Vertex center, const float r, Material m);

	~Sphere() = default;

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

private:
	float radius;
};