#include "Camera.h"
#include "Scene.h"

int main() {
	
	// Declare and define properties for the image
	int raysPerPixel = 5;
	int numberOfShadowRays = 5;
	int maximumRayDepth = 10;

	// Create the scene
	Scene myScene;

	// Create the camera object
	Camera myCamera{ 800, 800, raysPerPixel, numberOfShadowRays };

	myCamera.setNumberOfRaysPerPixel(raysPerPixel);
	myCamera.setNumberOfShadowRays(numberOfShadowRays);
	myCamera.setMaximumRayDepth(maximumRayDepth);

	
	myCamera.setPixels(myScene);

	
	myCamera.render();
	

	return 0;
}