#pragma once
#include "Polygon.h"

class Triangle : public Polygon {
public:
	Triangle(const Vertex p1, const Vertex p2, const Vertex p3, Material m);

	~Triangle() {}

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

	Direction calculateNormal() override;
private:
};