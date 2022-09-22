#pragma once
#include <iostream>
#include "Ray.h"
#include <vector>
#include <fstream>

class Camera {
public:

	Camera(int pixelHeight = 800, int pixelWidth = 800);

	void setPixels();

	void render();

private:
	int height;
	int width;
	std::vector<std::vector<Color>> pixelImage;
	int iMax = 1;
	double pixelWidth;

};