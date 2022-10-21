#include "Sphere.h"

Sphere::Sphere(const Vertex center, const double r, Material m) : radius{ r }, Surface{ std::vector<Vertex>{ center }, m} {
	
}

bool Sphere::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection){
	
	Direction directionVector = (start - points[0]);

	double c1 = glm::dot(inDirection, inDirection);
	double c2 = 2.0*glm::dot(inDirection, directionVector);
	double c3 = glm::dot(directionVector, directionVector) - pow(radius, 2);

	double arg = pow(c2, 2) - 4 * c1 * c3;
	double epsilon = 0.000001;

	if(abs(arg) < epsilon) {
		return false;
	}
	else if(arg > 0) {
		double t1 = -(c2 + sqrt(arg)) / (2 * c1);
		double t2 = -(c2 - sqrt(arg)) / (2 * c1);

		double t = glm::min(t1, t2);

		Vertex xr = start + inDirection * t;
		normal = glm::normalize(-(points[0] - xr));

		refIntersection = xr + normal * epsilon;

		return true;
	}

	return false;
}

