#include "Triangle.h"

Triangle::Triangle(const Vertex p1, const Vertex p2, const Vertex p3, Material m)
    : Surface{ std::vector<Vertex>{p1, p2, p3}, m } {
	// Calculate the normal
	normal = glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
}

bool Triangle::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {
	// Check if the normal is facing the ray
	if (glm::dot(inDirection, normal) < 0.0) {

		// M�ller-Trumbore algoritm
		Direction T = start - points[0];
		Direction E1 = points[1] - points[0];
		Direction E2 = points[2] - points[0];
		Direction D = inDirection;
		Direction P = glm::cross(D, E2);
		Direction Q = glm::cross(T, E1);

		glm::vec3 result = (1.0 / glm::dot(P, E1)) * glm::dvec3(glm::dot(Q, E2), glm::dot(P, T), glm::dot(Q, D));
		double t = result.x;
		double u = result.y;
		double v = result.z;

		double epsilon = 0.00000001;
		
		if ((0.0 <= u && 0.0 <= v && (u + v) <= 1.0) || (abs(u) <= epsilon && 0.0 <= v && v <= 1.0 ) || (abs(v) <= epsilon && 0.0 <= u && u <= 1.0)) {
			refIntersection = start + t * D;

			// Extra check to see if the intersecting surface is very close to the last intersection point
			if (t <= 0.01) {
				return false;
			}

			return true;
		}
		
	}
	return false;
}
