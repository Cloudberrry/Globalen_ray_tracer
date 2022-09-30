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
	Vertex startingPos = {-1, 0.0, 0.0};
	Direction currentDirection;
	Ray* currentRay;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {

			pixelPos = { 0.0, j * pixelWidth - (1.0 - pixelWidth), i * pixelWidth - (1.0 - pixelWidth) };
			currentDirection = glm::normalize(pixelPos - startingPos);
			currentRay = new Ray{ pixelPos, currentDirection };

			pixelImage[i][j] = shotRay(currentRay, P);

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

Color Camera::shotRay(Ray* ray, const std::vector<Polygon*>& P) {

	Vertex intersectionPoint;

	for (int k = 0; k < P.size(); ++k) {

		if (P[k]->intersection(ray->getDirection(), ray->getStartingPoint(), intersectionPoint)) {

			ray->setEndPoint(intersectionPoint);

			if (P[k]->getMaterial().getType() == "Mirror") {
				Ray* newRay = new Ray{intersectionPoint, ray->getNewDirection(ray->getDirection(), P[k]->calculateNormal()), P[k], ray};
				ray->setNextRay(newRay);
				ray->setRayColor(shotRay(newRay, P));
			}
			else {
				ray->setRayColor(P[k]->getMaterial().getColor());
			}
			return ray->getColor();

			break;
		}
	}
	return { 0.0, 0.0, 0.0 };
}