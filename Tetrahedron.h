#pragma once
#include "Triangle.h"

class Tetrahedron : public Surface {
public:
	Tetrahedron(const Vertex p1, const Vertex p2, const Vertex p3, const Vertex p4, Material m);

	~Tetrahedron() = default;

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

private:
	std::vector<Triangle> triangles;
};