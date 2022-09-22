#pragma once
#include "Polygon.h"

class Rectangle : public Polygon {
public:
	Rectangle(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3, const glm::vec3 p4, const Color c);

	~Rectangle(){}

	bool intersection(const glm::vec3 inVec, const glm::vec3 start, glm::vec3& intPoint) override;

private:
};