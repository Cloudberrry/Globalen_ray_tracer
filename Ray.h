#pragma once
#include "Surface.h"

class Ray {
public:

	// Base constructor
	Ray() = default;

	// Constructor that requires starting position and direction of the ray
	Ray(Vertex startPos, Direction dir, Surface* P = nullptr, Ray* prevRay = nullptr);

	// Destructor since we have pointers as private variables
	~Ray();

	// Sets the end point of a ray
	void setEndPoint(Vertex point);

	// Sets the color of the ray
	void setRayColor(Color c);

	// Sets the next ray
	void setNextRay(Ray* R);

	
	Vertex getStartingPoint() const;
	Direction getDirection() const;
	Color getColor() const;
	Surface* getSurface() const;

private:
	Vertex start;
	Vertex end;
	Direction direction;
	Surface* surface; // Surface on which the starting vertex is located
	Color color;
	Ray* next;
	Ray* previous;
};