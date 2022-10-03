#include "Camera.h"
#include <stdlib.h>

Camera::Camera(int pixHeight, int pixWidth) : height{ pixHeight }, width{ pixWidth }, iMax{ 0.0 } {
	pixelImage.resize(height, std::vector <Color> (width));
	pixelWidth = 2.0f / height;
	std::cout << "Pixel width: " << pixelWidth << std::endl;
}


void Camera::setPixels(const std::vector<Polygon*>& P) {

	int samples = 1;
	
	float newiMax;
	Vertex pixelPos;
	Vertex eyePosition = {-1.0, 0.0, 0.0};
	Direction currentDirection;
	Ray* firstRay;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {

			pixelPos = { 0.0, j * pixelWidth - (1.0 - pixelWidth), i * pixelWidth - (1.0 - pixelWidth) };
			currentDirection = glm::normalize(pixelPos - eyePosition);
			firstRay = new Ray{ pixelPos, currentDirection };

			pixelImage[i][j] = shootRay(firstRay, P);

			newiMax = glm::max(glm::max(pixelImage[i][j].x, pixelImage[i][j].y), pixelImage[i][j].z);

			if ( newiMax > iMax) {
				iMax = newiMax;
			}
		}
	}
}

void Camera::render() {

	std::ofstream ofs("./scene.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << height << " " << width << "\n255\n";

	std::cout << "iMax: " << iMax << std::endl;

	// Portable pixel map(ppm) writes the coordinates starting from the top left corner and goes down to the bottom right
	for (int i = height-1; i >= 0; --i) {
		for (int j = width-1; j >= 0; --j) {
			ofs << (unsigned char)((pixelImage[i][j].r) * (float)255 / iMax) <<
				(unsigned char)((pixelImage[i][j].g) * (float)255 / iMax) <<
				(unsigned char)((pixelImage[i][j].b) * (float)255 / iMax);
		}
	}
	ofs.close();

	std::cout << "Finished" << std::endl;
}

Color Camera::shootRay(Ray* ray, const std::vector<Polygon*>& P) {

	Vertex intersectionPoint;		//To calculate distance
	Vertex best_intersectionPoint;	//For final intersection
	float smallestDist = 10000.0f;
	Polygon* hitFace = nullptr;
	for (int k = 0; k < P.size(); ++k) {

		if (P[k]->intersection(ray->getDirection(), ray->getStartingPoint(), intersectionPoint)) {
			
			float newDist = glm::length(intersectionPoint - ray->getStartingPoint());
			
			if (newDist < smallestDist) {
				hitFace = P[k];
				smallestDist = newDist;
				best_intersectionPoint = intersectionPoint; //Skrivs annars över av punkte som inte är den närmaste!!
			}
		}
	}
	//If no surface, return slime 
	if(smallestDist == 10000.0f) return { 153.0f, 255.0f, 51.0f };
	else {
		ray->setEndPoint(best_intersectionPoint);

		// Add ray termination condition here
		if (hitFace->getMaterial().getType() == "Mirror") {
			Ray* newRay = new Ray{ best_intersectionPoint, ray->getNewDirection(ray->getDirection(), hitFace->calculateNormal()), hitFace, ray };
			ray->setNextRay(newRay);
			ray->setRayColor(shootRay(newRay, P));
		}
		else {
			//Light decreases relative to quadratic distance to lamp. Should be random point on lamp though for best approximation
			//Bug where light moves in (x,y) if you change z. 
			float lightFactor = glm::sqrt(1 / glm::length(best_intersectionPoint - (10.0f, 6.0f, 5.0f) ));
			ray->setRayColor(hitFace->getMaterial().getColor()*lightFactor);
		}
		return ray->getColor();
	}
}