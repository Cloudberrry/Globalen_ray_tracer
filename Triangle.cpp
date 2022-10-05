#include "Triangle.h"

Triangle::Triangle(const Vertex p1, const Vertex p2, const Vertex p3, Material m)
    : Polygon{ std::vector<Vertex>{p1, p2, p3}, m } {
	normal = calculateNormal();
}

bool Triangle::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {
	if (glm::dot(inDirection, normal) < 0) {

		// Trumbore
		Direction T = start - points[0];
		Direction E1 = points[1] - points[0];
		Direction E2 = points[2] - points[0];
		Direction D = inDirection;
		Direction P = glm::cross(D, E2);
		Direction Q = glm::cross(T, E1);

		glm::vec3 result = (1 / glm::dot(P, E1)) * glm::vec3(glm::dot(Q, E2), glm::dot(P, T), glm::dot(Q, D));
		float t = result.x;
		float u = result.y;
		float v = result.z;

		float epsilon = 0.0000000000001f;

		if ((0 <= u && 0 <= v && (u + v) <= 1) || (abs(u) < epsilon && v <= 1 && 0 <= v) || (abs(v) < epsilon && u <= 1 && 0 <= u)) {
			refIntersection = start + t * D; //+normal * epsilon;
			return true;
		}
	}
	return false;
}

Direction Triangle::calculateNormal() {
	return glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
}
