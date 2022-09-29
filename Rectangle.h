#pragma once
#include "Polygon.h"

class Rectangle : public Polygon {
public:
	Rectangle(const Vertex p1, const Vertex p2, const Vertex p3, const Vertex p4, const Color c);

	~Rectangle(){}

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

	Direction calculateNormal() override;

private:
};