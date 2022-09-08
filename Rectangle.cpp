#include "Rectangle.h"

Rectangle::Rectangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, Color c) : points{ p1, p2, p3, p4 }
{
	glm::vec3 temp = glm::normalize(glm::cross(p2 - p1, p3 - p2));
	normal = glm::vec4(temp, 1.0);
	color = c;
}

glm::vec4 Rectangle::intersection(const Ray& ray)
{
    return glm::vec4();
}

glm::vec4 Rectangle::calculateNormal()
{
	//Kryssprodukt mellan två basvektorer
	//Glöm inte normera
    return glm::vec4();
}
