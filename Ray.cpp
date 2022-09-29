#include "Ray.h"

Ray::Ray(Vertex startPos, Direction dir, Polygon* P, Ray* prevRay) : start{ startPos }, direction{ dir }, previous{ prevRay } {

}

Ray::~Ray() {
	/*
	Ray* temp = next->previous;
	next->previous = previous;
	previous->next = next;
	delete temp;
	*/
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

Direction Ray::getNewDirection(Direction inDirection, Direction normal) {
	return glm::normalize(inDirection - 2*glm::dot(inDirection, normal) * normal);
}

Color Ray::getColor() {
	return color;
}

Polygon* Ray::getSurface() {
	return surface;
}
