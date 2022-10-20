#include "Sphere.h"

Sphere::Sphere(const Vertex center, const float r, Material m) : radius{ r }, Surface{ std::vector<Vertex>{ center }, m} {
	
}

bool Sphere::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection){
	
	Direction directionVector = (start - points[0]);

	float c1 = glm::dot(inDirection, inDirection);
	float c2 = 2.0f*glm::dot(inDirection, directionVector);
	float c3 = glm::dot(directionVector, directionVector) - powf(radius, 2.0f);

	float arg = powf(c2, 2.0f) - 4.0f * c1 * c3;
	float epsilon = 0.00001f;

	if(abs(arg) < epsilon) {
		return false;
	}
	else if(arg > 0) {
		float t1 = -(c2 + sqrt(arg)) / (2.0f * c1);
		float t2 = -(c2 - sqrt(arg)) / (2.0f * c1);

		float t = glm::min(t1, t2);

		Direction xr = start + inDirection * t;
		refIntersection = xr;

		normal = glm::normalize((xr - points[0]));

		return true;
	}

	return false;
}

