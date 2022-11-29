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

	// Get functions for some variables
	Vertex getStartingPoint() const;
	Direction getDirection() const;
	Color getColor() const;
	Surface* getSurface() const;
	Ray* getPrevious() const;

private:
	Vertex start;			// Starting point of the ray
	Vertex end;				// End point of the ray
	Direction direction;	// Direction of the ray
	Surface* surface;		// Surface on which the starting vertex is located
	Color color;			// Color of the ray
	Ray* next;				// Pointer to the next ray in the ray path
	Ray* previous;			// Pointer to the previous ray in the ray path
};