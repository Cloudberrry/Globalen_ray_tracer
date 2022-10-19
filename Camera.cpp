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
	

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {

			pixelPos = { 0.0, j * pixelWidth - (1.0 - pixelWidth), i * pixelWidth - (1.0 - pixelWidth) };
			currentDirection = glm::normalize(pixelPos - eyePosition);
			Ray firstRay{ pixelPos, currentDirection };
			
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

Color Camera::shootRay(Ray& ray, const std::vector<Polygon*>& P) {

	Vertex intersectionPoint;		// To calculate distance
	Vertex best_intersectionPoint;	// For final intersection
	Direction currentNormal;
	Color incomingRayColor;
	Polygon* hitFace = nullptr;
	std::string type;
	int random = std::rand() % 5;
	float smallestDist = 10000000.0f;

	for (int k = 0; k < P.size(); ++k) {

		if (P[k]->intersection(ray.getDirection(), ray.getStartingPoint(), intersectionPoint)) {
			
			float newDist = glm::length(intersectionPoint - ray.getStartingPoint());
			
			if (newDist < smallestDist) {
				hitFace = P[k];
				smallestDist = newDist;
				best_intersectionPoint = intersectionPoint; //Skrivs annars över av punkte som inte är den närmaste!!
			}
		}
	}


	// Ska egentligen inte hända, men det händer, varför träffar vi inte en yta....
	if (hitFace == nullptr) {
		type = "NoSurface";
		ray.setRayColor({0.75f, 1.0f, 0.6f });
		return ray.getColor();
	}

	if (random == 0) {
		return hitFace->getMaterial().getColor();
	}

	type = hitFace->getMaterial().getType();
	currentNormal = hitFace->calculateNormal();
	
	if (type == "Lamp") {

		ray.setEndPoint(best_intersectionPoint);
		ray.setRayColor({ 1.0f, 1.0f, 1.0f });

	} else if (type == "Mirror" && random != 0) {

		ray.setEndPoint(best_intersectionPoint);

		Ray newRay{ best_intersectionPoint, ray.calculateNewDirection(ray.getDirection(), currentNormal), hitFace, &ray };
		ray.setNextRay(&newRay);

		incomingRayColor = shootRay(newRay, P); // Shoot the newly created ray into the scene

		ray.setRayColor(incomingRayColor * hitFace->getMaterial().getColor()); // Could multiply with surface color to get a tinted mirror

	} else if (type == "Lambertian") {

		ray.setEndPoint(best_intersectionPoint);

		int a = rand();
		int b = rand();
		int c = rand();
		Direction new_dir = glm::normalize(Direction{ a, b, c });

		// Checks if the new direction vector goes back into the surface, if so we flip it to always get a direction out from the surface
		if (glm::dot(currentNormal, new_dir) < 0) {
			new_dir = -new_dir;
		}

		glm::dot(currentNormal, new_dir) / (glm::length(new_dir));

		// Creates a new ray depending on the new direction
		Ray newRay{ best_intersectionPoint, new_dir, hitFace, &ray };
		ray.setNextRay(&newRay);

		incomingRayColor = shootRay(newRay, P); // Shoot the newly created ray into the scene
		
		ray.setRayColor(hitFace->getMaterial().getBRDF() * hitFace->getMaterial().getColor() * (incomingRayColor + shootShadowRay(P[0], best_intersectionPoint, currentNormal)));
	
	}

	return ray.getColor();
}

//Hur får vi tag på ljuset?
float Camera::shootShadowRay(Polygon* surface, Vertex hitPoint, Direction n_x) {
	
	Direction e1 = surface->getPoints()[1] - surface->getPoints()[0];
	Direction e2 = surface->getPoints()[3] - surface->getPoints()[0];

	float lightArea = glm::length(e1) * glm::length(e2);
	float w = lightArea * 50.f;
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