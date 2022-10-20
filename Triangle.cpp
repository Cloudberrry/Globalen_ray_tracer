#include "Triangle.h"

Triangle::Triangle(const Vertex p1, const Vertex p2, const Vertex p3, Material m)
    : Surface{ std::vector<Vertex>{p1, p2, p3}, m } {
	normal = glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
}

bool Triangle::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {
	if (glm::dot(inDirection, normal) < 0.0f) {

		// Trumbore
		Direction T = start - points[0];
		Direction E1 = points[1] - points[0];
		Direction E2 = points[2] - points[0];
		Direction D = inDirection;
		Direction P = glm::cross(D, E2);
		Direction Q = glm::cross(T, E1);

		glm::vec3 result = (1.0f / glm::dot(P, E1)) * glm::vec3(glm::dot(Q, E2), glm::dot(P, T), glm::dot(Q, D));
		float t = result.x;
		float u = result.y;
		float v = result.z;

		float epsilon = 0.000001f;

		if ((0.0f <= u && 0.0f <= v && (u + v) <= 1.0f) || (abs(u) < epsilon && 0.0f <= v && v <= 1.0f ) || (abs(v) < epsilon && 0.0f <= u && u <= 1.0f)) {
			refIntersection = start + t * D;
			return true;
		}
	}
	return false;
}