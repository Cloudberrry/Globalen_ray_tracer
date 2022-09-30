#include "Material.h"

Material::Material(std::string surfaceType, Color surfaceColor, float reflection, float refraction)
	: type{ surfaceType }, color{ surfaceColor }, reflectionCoefficient{ reflection }, refractionIndex{ refraction } {

}

std::string Material::getType() {
	return type;
}

Color Material::getColor() {
	return color;
}

float Material::getReflectionCoefficient() {
	return reflectionCoefficient;
}

float Material::getRefractionIndex() {
	return refractionIndex;
}
