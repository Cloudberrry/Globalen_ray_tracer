#include "Material.h"

Material::Material(std::string surfaceType, Color surfaceColor, double reflection, double refraction)
	: type{ surfaceType }, color{ surfaceColor }, reflectiveIndex{ reflection }, refractionIndex{ refraction }
{

}

std::string Material::getType() const {
	return type;
}

Color Material::getColor() const {
	return color;
}

double Material::getBRDF() const {
	if (type == "Lambertian") {
		return reflectiveIndex / M_PI;
	}
	return reflectiveIndex;
}

double Material::getRho() const {
	return reflectiveIndex;
}

double Material::getRefractionIndex() const {
	return refractionIndex;
}
