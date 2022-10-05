#include "Camera.h"
#include "Scene.h"

int main() {
	
	std::cout << "Creating scene.." << std::endl;
	Scene myScene;
	std::cout << "Scene complete! Creating camera.." << std::endl;
	Camera myCamera{ 800, 800 };
	myCamera.setPixels(myScene.allPolygons);
	myCamera.render();

	return 0;
}