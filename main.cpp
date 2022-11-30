#include "Camera.h"
#include "Scene.h"
#include <time.h>

int main() {
	

	clock_t tStart = clock();

	
	// Declare and define properties for the image
	int raysPerPixel = 5;
	int numberOfShadowRays = 5;
	int maximumMirrorBounces = 20;

	// Create the scene
	Scene myScene;

	// Create the camera object
	Camera myCamera{ 800, 800, raysPerPixel, numberOfShadowRays };

	myCamera.setNumberOfRaysPerPixel(raysPerPixel);
	myCamera.setNumberOfShadowRays(numberOfShadowRays);
	myCamera.setMaximumRayDepth(maximumMirrorBounces);

	
	myCamera.setPixels(myScene);

	myCamera.render();

	std::cout << (double)(clock() - tStart) / CLOCKS_PER_SEC << std::endl;

	return 0;
}