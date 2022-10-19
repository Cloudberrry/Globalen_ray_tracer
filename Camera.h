#pragma once
#include <fstream>
#include "Ray.h"

class Camera {
public:

	Camera(int pixelHeight = 800, int pixelWidth = 800);

	void setPixels(const std::vector<Polygon*>& P);

	void render();

	Color shootRay(Ray& ray, const std::vector<Polygon*>& P);
	float shootShadowRay(Polygon* surface, Vertex hitPoint, Direction n_x);

private:
	int height;
	int width;
	std::vector<std::vector<Color>> pixelImage;
	float iMax;
	float pixelWidth;
};