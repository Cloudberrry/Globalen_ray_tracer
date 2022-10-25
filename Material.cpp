#include "Material.h"

Material::Material(std::string surfaceType, Color surfaceColor, double reflection, double refraction)
	: type{ surfaceType }, color{ surfaceColor }, BRDF{ (reflection / M_PI) }, rho{ reflection }, refractionIndex{ refraction }
{

}

std::string Material::getType() {
	return type;
}

Color Material::getColor() {
	return color;
}

double Material::getBRDF() {
	return BRDF;
}

double Material::getRho() {
	return rho;
}

double Material::getRefractionIndex() {
	return refractionIndex;
}

bool Material::operator==(const Material& M) {
	if (type == M.type && color == M.color && BRDF == M.BRDF && rho == M.rho && refractionIndex == M.refractionIndex) {
		return true;
	}
	return false;
}

bool Material::operator!=(const Material& M) {
	return !operator==(M);
}
