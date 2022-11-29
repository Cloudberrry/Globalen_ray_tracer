#pragma once
#include <iostream>
#include <vector>
#include "Material.h"

class Surface {
public:
	// A virtual destructor incase some typ of surface includes pointers
	virtual ~Surface() = default;

	// Copy constructor
	Surface(const Surface& C) = default;

	// Calculates the intersection point and returns true if the function intersects with the surface 
	virtual bool intersection(const Direction inDirection, const Vertex start, Vertex& intPoint) = 0;

	// Get functions for the private variables
	std::vector<Vertex> getPoints() const;
	Material getMaterial() const;
	Direction getNormal() const;

	// Calculates the direction of a reflected ray
	Direction calculateReflectedRayDirection(Direction inDirection, Direction norm) const;

	// Calculates the direction of a refracted ray
	Direction calculateRefractedRayDirection(Direction inDirection, Direction norm, double R) const;

protected:

	// Constructor
	Surface(const std::vector<Vertex>& P, const Material m);
	
	Material material;
	Direction normal;
	std::vector<Vertex> points;
};