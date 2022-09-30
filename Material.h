#pragma once
#include <string>
#include "Definitions.h"

class Material {
public:
	Material(std::string surfaceType, Color surfaceColor, float reflection = 0.5, float refraction = 1.0);

	std::string getType();
	Color getColor();
	float getReflectionCoefficient();
	float getRefractionIndex();

private:
	std::string type;
	Color color;
	float reflectionCoefficient;
	float refractionIndex;
};