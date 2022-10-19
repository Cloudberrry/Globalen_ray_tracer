#include "Ray.h"

Ray::Ray(Vertex startPos, Direction dir, Polygon* P, Ray* prevRay) : start{ startPos }, direction{ dir }, previous{ prevRay } {

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

Vertex Ray::getStartingPoint() {
	return start;
}

Direction Ray::getDirection() {
	return direction;
}

Direction Ray::calculateNewDirection(Direction inDirection, Direction normal) {
	return glm::normalize(inDirection - 2*glm::dot(inDirection, normal)*normal);
}

Color Ray::getColor() {
	return color;
}

Polygon* Ray::getSurface() {
	return surface;
}
