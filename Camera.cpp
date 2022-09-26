#include "Camera.h"

Camera::Camera(int pixHeight, int pixWidth) : height{ pixHeight }, width{ pixWidth }
{
	pixelImage.resize(height, std::vector <Color> (width));
	pixelWidth = 2.0f / height;
}

void Camera::setPixels(const std::vector<Polygon*>& P)
{
	int samples = 1;
	glm::vec3 intersectionPoint;
	glm::vec3 direction;
	glm::vec3 pixelPos;
	glm::vec3 startingPos = {-1.0, 0.0, 0.0};

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			pixelPos = { 0.0, j * pixelWidth - (1.0 - pixelWidth), i * pixelWidth - (1.0 - pixelWidth) };
			direction = glm::normalize(pixelPos - startingPos);

			for (int k = 0; k < P.size(); ++k) {
				if (P[k]->intersection(direction, pixelPos, intersectionPoint)) {
					pixelImage[i][j].setColor(P[k]->getColor().getColor());
					break;
				}
			}
		}
	}

}

void Camera::render()
{

	std::ofstream ofs("./scene.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << height << " " << width << "\n255\n";

	std::cout << "iMax: " << iMax << std::endl;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			ofs << (unsigned char)((pixelImage[i][j].getColor().x) * (float)1 / iMax) <<
				(unsigned char)((pixelImage[i][j].getColor().y) * (float)1 / iMax) <<
				(unsigned char)((pixelImage[i][j].getColor().z) * (float)1 / iMax);
		}
	}
	ofs.close();

	std::cout << "Finished" << std::endl;
}
