#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "Definitions.h"


class Material {
public:
	Material(std::string surfaceType, Color surfaceColor, double reflection = 0.5f, double refraction = 1.0f);

	std::string getType();
	Color getColor();
	double getBRDF();
	double getRho();
	double getRefractionIndex();

private:
	std::string type;
	Color color;
	double BRDF;
	double rho;
	double refractionIndex;
};