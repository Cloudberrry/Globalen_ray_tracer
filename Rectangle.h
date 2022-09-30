#pragma once
#include "Polygon.h"

class Rectangle : public Polygon {
public:
	Rectangle(const Vertex p1, const Vertex p2, const Vertex p3, const Vertex p4, Material m);

	~Rectangle() = default;

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

	Direction calculateNormal() override;

private:
};