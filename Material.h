#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "Definitions.h"


class Material {
public:
	// Constructor with base reflection of 0.5 and refraction 1.0 if nothing else is specified
	Material(std::string surfaceType, Color surfaceColor, double reflection = 0.5, double refraction = 1.0);

	// Get functions for all private variables + rho
	std::string getType() const;
	Color getColor() const;
	double getBRDF() const;
	double getRho() const;
	double getRefractionIndex() const;

private:
	// Type is either Lambertian, Lamp, Glass or Mirror
	std::string type;
	Color color;
	double reflectiveIndex;
	double refractionIndex;
};