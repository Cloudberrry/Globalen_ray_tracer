#include <iostream>
#include "Camera.h"
#include "Scene.h"
#include <string>


int main() {
	
	Scene myScene;
	Camera myCamera{ 800, 800 };

	myCamera.setPixels(myScene.allPolygons);
	myCamera.render();

	return 0;
}