#include "Camera.h"
#include <stdlib.h>

Camera::Camera(int pixHeight, int pixWidth) : height{ pixHeight }, width{ pixWidth }, iMax{ 0.0 } {
	pixelImage.resize(height, std::vector <Color> (width));
	pixelWidth = 2.0f / height;
	std::cout << "Pixel width: " << pixelWidth << std::endl;
}


void Camera::setPixels(const std::vector<Polygon*>& P) {

	int samples = 10;
	
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
			
			Color average_color = { 0.0, 0.0, 0.0 };
			for (int a = 0; a < samples; ++a) {
				average_color += shootRay(firstRay, P);
			}
			average_color = { average_color.x * 255.0f / samples, average_color.y * 255.0f / samples, average_color.z * 255.0f / samples };
			//average_color = { sqrt(average_color.x * 255.0f / samples), sqrt(average_color.y * 255.0f / samples), sqrt(average_color.z * 255.0f / samples) };
		
			pixelImage[i][j] = average_color;

			newiMax = glm::max(glm::max(pixelImage[i][j].x, pixelImage[i][j].y), pixelImage[i][j].z);

			if ( newiMax > iMax) {
				iMax = newiMax;
			}
			delete firstRay;
			firstRay = nullptr;
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

Color Camera::shootRay(Ray*& ray, const std::vector<Polygon*>& P) {

	Vertex intersectionPoint = { 0.0f, 0.0f, 0.0f };		//To calculate distance
	Vertex best_intersectionPoint = { 0.0f, 0.0f, 0.0f };	//For final intersection
	float smallestDist = 100000.0f;
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

	if (smallestDist > 99999.0f) {
		return { 0.0f, 0.0f, 0.0f };
	}

	ray->setEndPoint(best_intersectionPoint);
	Color incomingRayColor = {0.0f, 0.0f, 0.0f};

	int random = std::rand() % 5;

	// Add ray termination condition here
	if (hitFace->getMaterial().getType() == "Lamp") {
		return {1.0f, 1.0f, 1.0f};
	} else if (random != 0) {
		Ray* newRay = new Ray{ best_intersectionPoint, ray->getNewDirection(ray->getDirection(), hitFace->calculateNormal()), hitFace, ray };
		ray->setNextRay(newRay);

		incomingRayColor = shootRay(newRay, P);
		
		delete newRay;
		newRay = nullptr;
	}

	ray->setRayColor(hitFace->getMaterial().getBRDF() * hitFace->getMaterial().getColor() * (dirLight(P[0], best_intersectionPoint, hitFace->calculateNormal()) + incomingRayColor));
	return ray->getColor();
}

//Hur får vi tag på ljuset?
float Camera::dirLight(Polygon* surface, Vertex hitPoint, Direction n_x) {
	
	
	Direction e1 = surface->getPoints()[1] - surface->getPoints()[0];
	Direction e2 = surface->getPoints()[3] - surface->getPoints()[0];

	float lightArea = glm::length(e1) * glm::length(e2);
	float w = lightArea*32.0f;
	float accLight = 0.0;
	int counter = 0;
	int itMax = 20;
	float rand1;
	float rand2;
	Vertex lampCoord;
	Direction distance;
	float distLen;
	float cosy;
	float cosx;

	while (counter < itMax) {
		rand1 = (float)(std::rand() % 100) / 100;
		rand2 = (float)(std::rand() % 100) / 100;
		lampCoord = surface->getPoints()[0] + rand1 * e1 + rand2 * e2;
		distance = lampCoord - hitPoint;
		distLen = glm::length(distance);

		cosy = glm::dot(-surface->calculateNormal(), distance) / distLen;
		cosx = glm::dot(n_x, distance) / distLen;

		accLight += (cosy * cosx) / (distLen * distLen);
		++counter;
	}

	accLight = accLight * (w / counter);
	return accLight;
}