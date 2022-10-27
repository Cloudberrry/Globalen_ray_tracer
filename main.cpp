#include "Camera.h"
#include "Scene.h"

int main() {
	

	int raysPerPixel = 5;
	int numberOfShadowRays = 5;


	std::cout << "Creating scene..." << std::endl;
	Scene myScene;

	std::cout << "Scene complete! Creating camera..." << std::endl;
	Camera myCamera{ 800, 800, raysPerPixel, numberOfShadowRays };

	std::cout << "Camera setup complete! Calculating pixel colors..." << std::endl;
	myCamera.setPixels(myScene);

	std::cout << "Rendering pixels to the image..." << std::endl;
	myCamera.render();
	std::cout << "Render complete!" << std::endl;

	return 0;
}