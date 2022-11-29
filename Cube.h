#pragma once
#include "Rectangle.h"

class Cube : public Surface {
public:
	Cube(const std::vector<Vertex> V, Material m);

	~Cube() = default;

	bool intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) override;

private:
	// A cube is made of 6 rectangles
	std::vector<Rectangle> rectangles;
};