#include "Triangle.h"

Triangle::Triangle(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3, const Color c)
    : Polygon{ std::vector<glm::vec3>{p1, p2, p3}, c }
{
	normal = calculateNormal();
}

bool Triangle::intersection(const glm::vec3 inDirection, const glm::vec3 start, glm::vec3& refIntersection)
{
	if (glm::dot(inDirection, normal) < 0) {

		float t = glm::dot((points[0] - start), normal) / glm::dot(inDirection, normal);

		// Trumbore
		/*glm::vec3 T = start - points[0];
		glm::vec3 E1 = points[1] - points[0];
		glm::vec3 E2 = points[2] - points[0];
		glm::vec3 P = glm::cross(inDirection, E2);
		glm::vec3 Q = glm::cross(T, E1);

		float t = glm::dot(Q, E2) / glm::dot(P, E1);*/

		glm::vec3 c1 = points[1] - points[0];
		glm::vec3 c2 = points[2] - points[0];

		glm::vec3 x = start + t * inDirection;

		float a = glm::dot((x - points[0]), c1) / glm::dot(c1, c1);
		float b = glm::dot((x - points[0]), c2) / glm::dot(c2, c2);

		if (0 <= a && 0 <= b && (a + b) <= 1) {
			refIntersection = x;
			return true;
		}
	}
	return false;
}

glm::vec3 Triangle::calculateNormal()
{
	return glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
}
