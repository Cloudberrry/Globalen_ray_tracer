#pragma once
#include <fstream>
#include <random>
#include "Scene.h"
#include "Ray.h"

class Camera {
public:

	// Constructor that sets up a basic camera even if no variables are given
	Camera(int pixHeight = 800, int pixWidth = 800, int raysPerPixel = 5, int shadowRaysPerIntersection = 10);

	// Sets the color of all pixels on the camera plane using the provided scene
	void setPixels(const Scene& S);

	// Writes the pixel values to a file
	void render() const;

	// Set functions for some variables
	void setNumberOfRaysPerPixel(const int rays);
	void setNumberOfShadowRays(const int shadowRays);
	void setMaximumRayDepth(const int depth);

	// Shoots rays recursivly into the scene
	Color shootRay(Ray& ray, const Scene& S, int& rayDepth) const;

	// Shoots shadow rays from the intersection point to random points on a light source
	Color shootShadowRays(const Scene& S, Surface* lamp, Surface*& hitSurface, const Vertex& hitPoint, const Direction& n_x) const;

private:
	int height;										// The height of the camera plane in pixels
	int width;										// The width of the camera plane in pixels
	int numberOfRays;								// The number of rays shot per pixel
	int numberOfShadowRays;							// The number of shado rays shot per intersection
	int maxRayDepth;								// The maximum ray depth
	std::vector<std::vector<Color>> pixelImage;		// The camera plane of pixels as a matrix
	double iMax;									// The maximum color value in the image
	double pixelWidth;								// The width of a pixel in the image
};