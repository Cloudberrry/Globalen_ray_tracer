#include "Rectangle.h"

Rectangle::Rectangle(const Vertex p1, const Vertex p2, const Vertex p3, const Vertex p4, Material m)
	: Surface{ std::vector<Vertex>{p1, p2, p3, p4}, m} {
	normal = glm::normalize(glm::cross(points[1] - points[0], points[3] - points[0]));
}

bool Rectangle::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {
	if (glm::dot(inDirection, normal) < 0.0) {
		double t = glm::dot((points[0] - start), normal) / glm::dot(inDirection, normal);

		Direction c1 = points[1] - points[0];
		Direction c2 = points[3] - points[0];
		double epsilon = 0.000001;
		Vertex x = start +  t * inDirection;

		double a = glm::dot((x - points[0]), c1) / glm::dot(c1, c1);
		double b = glm::dot((x - points[0]), c2) / glm::dot(c2, c2);
		

		if ((0.0 <= a && a <= 1.0 && 0.0 <= b && b <= 1.0) || (abs(a) < epsilon && 0.0 <= b && b <= 1.0) || (abs(b) < epsilon && 0.0 <= a && a <= 1.0))  {
			refIntersection = x;
			return true;
		}
	}
    return false;
}