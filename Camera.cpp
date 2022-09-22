#include "Camera.h"

Camera::Camera(int pixHeight, int pixWidth) : height{ pixHeight }, width{ pixWidth }
{
	pixelImage.resize(height, std::vector <Color> (width));
	pixelWidth = 1.0 / height;
}

void Camera::setPixels()
{
	int samples = 1;
	

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {

		}
	}

}

void Camera::render()
{

	


	std::ofstream ofs("./scene.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << height << " " << width << "\n255\n";
	std::cout << iMax << std::endl;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			ofs << (unsigned char)((pixelImage[i][j].getColor().x) * (float)255 / iMax) <<
				(unsigned char)((pixelImage[i][j].getColor().y) * (float)255 / iMax) <<
				(unsigned char)((pixelImage[i][j].getColor().z) * (float)255 / iMax);
		}
	}
	ofs.close();

	std::cout << "Finished" << std::endl;
}
