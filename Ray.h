#pragma once
#include "Triangle.h"
#include "Rectangle.h"

class Ray {
public:

	Ray() = default;

	Ray(Vertex startPos, Direction dir, Polygon* P = nullptr, Ray* prevRay = nullptr);

	~Ray();

	void setEndPoint(Vertex point);

	void setRayColor(Color c);

	void setNextRay(Ray* R);

	Vertex getStartingPoint();

	Direction getDirection();

	Direction getNewDirection(Direction inDirection, Direction normal);

	Color getColor();

	Polygon* getSurface();


private:
	Vertex start;
	Vertex end;
	Direction direction;
	Polygon* surface; // Surface on which the starting vertex is located
	Color color;
	Ray* next;
	Ray* previous;
};