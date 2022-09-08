#pragma once
#include <iostream>

class Color {
public:
	Color(double r = 0.0, double g = 0.0, double b = 0.0) : color{r, g, b} {}

	Color(const Color& c) = default;

	//TODO Normalize color values

	Color& operator+(Color c);
	Color& operator-(Color c);
	Color& operator*(Color c);

private:

	glm::vec3 color;
};
