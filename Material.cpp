#include "Material.h"

Material::Material(std::string surfaceType, Color surfaceColor, float reflection, float refraction)
	: type{ surfaceType }, color{ surfaceColor }, BRDF{ reflection }, refractionIndex{ refraction } {

}

std::string Material::getType() {
	return type;
}

Color Material::getColor() {
	return color;
}

float Material::getBRDF() {
	return BRDF;
}

float Material::getRefractionIndex() {
	return refractionIndex;
}
