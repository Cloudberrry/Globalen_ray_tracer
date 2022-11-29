#include "Cube.h"

Cube::Cube(const std::vector<Vertex> V, Material m)
	: Surface{ V, m }
{
	Rectangle r1{ V[0], V[1], V[2], V[3], m };
	Rectangle r2{ V[0], V[4], V[5], V[1], m };
	Rectangle r3{ V[1], V[5], V[6], V[2], m };
	Rectangle r4{ V[2], V[6], V[7], V[3], m };
	Rectangle r5{ V[3], V[7], V[4], V[0], m };
	Rectangle r6{ V[4], V[7], V[6], V[5], m };
	rectangles.push_back(r1);
	rectangles.push_back(r2);
	rectangles.push_back(r3);
	rectangles.push_back(r4);
	rectangles.push_back(r5);
	rectangles.push_back(r6);
}

bool Cube::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {
	for (int i = 0; i < rectangles.size(); ++i) {
		if (glm::dot(rectangles[i].getNormal(), inDirection) < 0 && rectangles[i].intersection(inDirection, start, refIntersection)) {
			normal = rectangles[i].getNormal();
			return true;
		}
	}
	return false;
}
