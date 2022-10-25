#include "Sphere.h"

Sphere::Sphere(const double r, const Vertex center,  Material m) : radius{ r }, Surface{ std::vector<Vertex>{ center }, m} {
	
}

bool Sphere::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection){
	
	Direction directionVector = (start - points[0]); // (S - C)

	double c1 = glm::dot(inDirection, inDirection); // c1 = D^2
	double c2 = glm::dot(2.0 * inDirection, directionVector); // c2 = 2D(S-C)
	double c3 = glm::dot(directionVector, directionVector) - pow(radius, 2); // (S - C)^2 - r^2
	

	double arg = pow(c2, 2) - 4.0 * c1 * c3;
	double epsilon = 0.0001;

	if(abs(arg) < epsilon || c2 > 0.0) { 
		return false;
	}
	else if(arg > 0) {
		double t1 = (-c2 + sqrt(arg)) / (2.0 * c1);
		double t2 = (-c2 - sqrt(arg)) / (2.0 * c1);
		
		double t = glm::min(t1, t2);

		Vertex xr = start + inDirection * t;
		normal = glm::normalize(xr - points[0]);

		refIntersection = xr;

		return true;
	}

	return false;
}

