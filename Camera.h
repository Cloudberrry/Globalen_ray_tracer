#pragma once
#include <fstream>
#include <random>
#include "Scene.h"
#include "Ray.h"

class Camera {
public:

	Camera(int pixelHeight = 800, int pixelWidth = 800);

	void setPixels(const Scene& S);

	void render();

	Color shootRay(Ray& ray, const Scene& S);
	Color shootShadowRays(const Scene& S, Surface* hitSurface, Vertex hitPoint, Direction n_x);

private:
	int height;
	int width;
	std::vector<std::vector<Color>> pixelImage;
	float iMax;
	float pixelWidth;
};