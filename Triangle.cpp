#include "Triangle.h"

Triangle::Triangle(const Vertex p1, const Vertex p2, const Vertex p3, Material m)
    : Polygon{ std::vector<Vertex>{p1, p2, p3}, m }
{
	normal = calculateNormal();
}

bool Triangle::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection)
{
	if (glm::dot(inDirection, normal) < 0) {

		// Trumbore
		Vertex eyePos = { -1, 0, 0 }; // OBS! Hårdkodad!!!
		Direction T = eyePos - points[0];
		Direction E1 = points[1] - points[0];
		Direction E2 = points[2] - points[0];
		Direction D = start - eyePos;
		Direction P = glm::cross(D, E2);
		Direction Q = glm::cross(T, E1);

		glm::vec3 result = (1 / glm::dot(P, E1)) * glm::vec3(glm::dot(Q, E2), glm::dot(P, T), glm::dot(Q, D));
		float t = result.x;
		float u = result.y;
		float v = result.z;

		if (0 <= u && 0 <= v && (u + v) <= 1) {
			refIntersection = eyePos + t * D;
			return true;
		}

		//float t = glm::dot((points[0] - start), normal) / glm::dot(inDirection, normal);

		/*glm::vec3 c1 = points[1] - points[0];
		glm::vec3 c2 = points[2] - points[0];

		glm::vec3 x = start + t * inDirection;

		float a = glm::dot((x - points[0]), c1) / glm::dot(c1, c1);
		float b = glm::dot((x - points[0]), c2) / glm::dot(c2, c2);

		if (0 <= a && 0 <= b && (a + b) <= 1 ) {
			refIntersection = x;
			return true;
		}*/
	}
	return false;

	
}

Direction Triangle::calculateNormal()
{
	return glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
}
