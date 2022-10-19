#include "Rectangle.h"

Rectangle::Rectangle(const Vertex p1, const Vertex p2, const Vertex p3, const Vertex p4, Material m)
	: Polygon{ std::vector<Vertex>{p1, p2, p3, p4}, m} {
	normal = calculateNormal();
}

bool Rectangle::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {
	if (glm::dot(inDirection, normal) < 0.0f) {
		float t = glm::dot((points[0] - start), normal) / glm::dot(inDirection, normal);

		Direction c1 = points[1] - points[0];
		Direction c2 = points[3] - points[0];
		float epsilon = 0.000001f;
		Vertex x = start +  t * inDirection;

		float a = glm::dot((x - points[0]), c1) / glm::dot(c1, c1);
		float b = glm::dot((x - points[0]), c2) / glm::dot(c2, c2);
		

		if ((0.0f <= a && a <= 1.0f && 0.0f <= b && b <= 1.0f) || (abs(a) < epsilon && 0.0f <= b && b <= 1.0f) || (abs(b) < epsilon && 0.0f <= a && a <= 1.0f))  {
			refIntersection = x;
			return true;
		}
	}
    return false;
}

Direction Rectangle::calculateNormal() {
	return glm::normalize(glm::cross(points[1] - points[0], points[2] - points[1]));
}
