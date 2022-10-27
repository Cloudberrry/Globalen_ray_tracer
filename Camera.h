#pragma once
#include <fstream>
#include <random>
#include "Scene.h"
#include "Ray.h"

class Camera {
public:

	Camera(int pixHeight = 800, int pixWidth = 800, int raysPerPixel = 5, int shadowRaysPerIntersection = 10);

	void setPixels(const Scene& S);

	void render() const;

	Color shootRay(Ray& ray, const Scene& S, int& rayDepth) const;
	Color shootShadowRays(const Scene& S, Surface* lamp, Surface*& hitSurface, const Vertex& hitPoint, const Direction& n_x) const;

private:
	int height;
	int width;
	int numberOfRays;
	int numberOfShadowRays;
	std::vector<std::vector<Color>> pixelImage;
	double iMax;
	double pixelWidth;
};