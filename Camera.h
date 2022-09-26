#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Ray.h"

class Camera {
public:

	Camera(int pixelHeight = 800, int pixelWidth = 800);

	void setPixels(const std::vector<Polygon*>& P);

	void render();

private:
	int height;
	int width;
	std::vector<std::vector<Color>> pixelImage;
	int iMax = 1;
	float pixelWidth;

};