#pragma once
#include "Polygon.h"

class Triangle : public Polygon {
public:
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Color c);

	glm::vec4 intersection(const Ray& ray) override;
	glm::vec4 calculateNormal() override;
private:
	std::vector<glm::vec3> points;
};