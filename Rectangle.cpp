#include "Rectangle.h"

Rectangle::Rectangle(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3, const glm::vec3 p4, const Color c)
	: Polygon{ std::vector<glm::vec3>{p1, p2, p3, p4}, c }
{
	normal = calculateNormal();
}

bool Rectangle::intersection(const glm::vec3 inDirection, const glm::vec3 start, glm::vec3& refIntersection)
{
	if (glm::dot(inDirection, normal) < 0) {
		float t = glm::dot((points[0] - start), normal) / glm::dot(inDirection, normal);

		glm::vec3 c1 = points[1] - points[0];
		glm::vec3 c2 = points[3] - points[0];

		glm::vec3 x = start +  t * inDirection;

		float a = glm::dot((x - points[0]), c1) / glm::dot(c1, c1);
		float b = glm::dot((x - points[0]), c2) / glm::dot(c2, c2);

		if (0 <= a && a <= 1 && 0 <= b && b <= 1) {
			refIntersection = x;
			return true;
		}
	}
    return false;
}

glm::vec3 Rectangle::calculateNormal()
{
	return glm::normalize(glm::cross(points[1] - points[0], points[2] - points[1]));
}
