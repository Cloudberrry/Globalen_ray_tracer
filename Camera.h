#pragma once
#include <iostream>
#include "Ray.h"

class Camera {
public:
	struct Pixel {
		Color color;
		Ray ray;
	};

	void render();
private:
	const int height = 800;
	const int width = 800;
	std::vector<std::vector<Pixel>> pixelImage;

};