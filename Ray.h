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

	Vertex getStartingPoint();

	Direction getDirection();

	Direction calculateNewDirection(Direction inDirection, Direction normal);
	Direction calculateRefractedRay(Direction inDirection, Direction normal, double R);

	Color getColor();

	Surface* getSurface();

private:
	Vertex start;
	Vertex end;
	Direction direction;
	Surface* surface; // Surface on which the starting vertex is located
	Color color;
	Ray* next;
	Ray* previous;
};