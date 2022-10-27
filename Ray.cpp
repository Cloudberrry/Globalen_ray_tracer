#include "Ray.h"

Ray::Ray(Vertex startPos, Direction dir, Surface* P, Ray* prevRay) : start{ startPos }, direction{ dir }, surface{ P }, previous{ prevRay } {

}

Ray::~Ray() {
	if (previous  != nullptr) {
		previous->next = nullptr;
	}

	surface = nullptr;
	previous = nullptr;
}

void Ray::setEndPoint(Vertex point) {
	end = point;
}

void Ray::setRayColor(Color c) {
	color = c;
}

void Ray::setNextRay(Ray* R) {
	next = R;
}

Vertex Ray::getStartingPoint() const {
	return start;
}

Direction Ray::getDirection() const {
	return direction;
}

Color Ray::getColor() const {
	return color;
}

Surface* Ray::getSurface() const {
	return surface;
}

Direction Ray::calculateNewDirection(Direction inDirection, Direction normal) const {
	return glm::normalize(inDirection - 2*glm::dot(inDirection, normal)*normal);
}

Direction Ray::calculateRefractedRay(Direction inDirection, Direction normal, double R) const {
	return glm::normalize(R * inDirection + normal * (-R * glm::dot(normal, inDirection) - sqrt(1 - pow(R, 2) * (1 - pow(glm::dot(normal, inDirection), 2)))));
}