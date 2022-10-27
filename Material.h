#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "Definitions.h"


class Material {
public:
	Material(std::string surfaceType, Color surfaceColor, double reflection = 0.5, double refraction = 1.0);

	std::string getType() const;
	Color getColor() const;
	double getBRDF() const;
	double getRho() const;
	double getRefractionIndex() const;

private:
	std::string type;
	Color color;
	double reflectiveIndex;
	double refractionIndex;
};