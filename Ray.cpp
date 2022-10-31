#include "Ray.h"

Ray::Ray(Vertex startPos, Direction dir, Surface* P, Ray* prevRay)
	: start{ startPos }, direction{ dir }, surface{ P }, previous{ prevRay }
{

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