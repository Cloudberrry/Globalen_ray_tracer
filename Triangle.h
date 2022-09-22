#pragma once
#include "Polygon.h"

class Triangle : public Polygon {
public:
	Triangle(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3, const Color c);

	~Triangle() {}

	bool intersection(const glm::vec3 inVec, const glm::vec3 start, glm::vec3& intPoint) override;
private:
};