#pragma once
#include "Surface.h"

class Ray {
public:

	Ray() = default;

	Ray(Vertex startPos, Direction dir, Surface* P = nullptr, Ray* prevRay = nullptr);

	~Ray();

	void setEndPoint(Vertex point);

	void setRayColor(Color c);

	void setNextRay(Ray* R);

	Vertex getStartingPoint() const;
	Direction getDirection() const;
	Color getColor() const;
	Surface* getSurface() const;

	Direction calculateNewDirection(Direction inDirection, Direction normal) const;
	Direction calculateRefractedRay(Direction inDirection, Direction normal, double R) const;

private:
	Vertex start;
	Vertex end;
	Direction direction;
	Surface* surface; // Surface on which the starting vertex is located
	Color color;
	Ray* next;
	Ray* previous;
};