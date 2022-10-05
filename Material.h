#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "Definitions.h"


class Material {
public:
	Material(std::string surfaceType, Color surfaceColor, float reflection = (1.0f / M_PI), float refraction = 1.0f);

	std::string getType();
	Color getColor();
	float getBRDF();
	float getRefractionIndex();

private:
	std::string type;
	Color color;
	float BRDF;
	float refractionIndex;
};