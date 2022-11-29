#pragma once
#include "Triangle.h"

class Tetrahedron : public Surface {
public:
	Tetrahedron(const std::vector<Vertex> V, Material m);

	~Tetrahedron() = default;

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

private:
	// A tetrahedron is built up by 4 triangles
	std::vector<Triangle> triangles;
};