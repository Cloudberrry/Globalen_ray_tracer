#include "Camera.h"
#include <stdlib.h>

Camera::Camera(int pixHeight, int pixWidth) : height{ pixHeight }, width{ pixWidth }, iMax{ 0.0 } {
	pixelImage.resize(height, std::vector <Color> (width));
	pixelWidth = 2.0f / height;
	std::cout << "Pixel width: " << pixelWidth << std::endl;
}


void Camera::setPixels(const Scene& S) {

	int samples = 11;
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
				average_color += shootRay(firstRay, S);
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
			ofs << (unsigned char)((pixelImage[i][j].r) * 255.0f / iMax) <<
				(unsigned char)((pixelImage[i][j].g) * 255.0f / iMax) <<
				(unsigned char)((pixelImage[i][j].b) * 255.0f / iMax);
		}
	}
	ofs.close();

	std::cout << "Finished" << std::endl;
}

Color Camera::shootRay(Ray& ray, const Scene& S) {	//const std::vector<Polygon*>& P) {

	Vertex intersectionPoint;		// To calculate distance
	Vertex best_intersectionPoint;	// For final intersection
	Direction currentNormal;
	Color incomingRayColor;
	Surface* hitFace = nullptr;
	std::string type;
	int random = std::rand() % 3;
	float smallestDist = 10000000.0f;

	for (int k = 0; k < S.polygons.size(); ++k) {

		if (S.polygons[k]->intersection(ray.getDirection(), ray.getStartingPoint(), intersectionPoint)) {
			
			float newDist = glm::length(intersectionPoint - ray.getStartingPoint());
			
			if (newDist < smallestDist) {
				hitFace = S.polygons[k];
				smallestDist = newDist;
				best_intersectionPoint = intersectionPoint; //Skrivs annars över av punkte som inte är den närmaste!!
				currentNormal = hitFace->getNormal();
			}
		}
	}

	for (int i = 0; i < S.spheres.size(); ++i) {
		if (S.spheres[i]->intersection(ray.getDirection(), ray.getStartingPoint(), intersectionPoint)) {

			float newDist = glm::length(intersectionPoint - ray.getStartingPoint());

			if (newDist < smallestDist) {
				hitFace = S.spheres[i];
				smallestDist = newDist;
				best_intersectionPoint = intersectionPoint; //Skrivs annars över av punkte som inte är den närmaste!!
				currentNormal = hitFace->getNormal();
			}
		}
	}

	// Ska egentligen inte hända, men det händer, varför träffar vi inte en yta....
	if (hitFace == nullptr) {
		type = "NoSurface";
		ray.setRayColor(S.custom);
		return ray.getColor();
	}

	if (random == 0) {
		return hitFace->getMaterial().getColor();
	}

	ray.setEndPoint(best_intersectionPoint);
	type = hitFace->getMaterial().getType();
	
	
	if (type == "Lamp") {

		ray.setRayColor(S.white);

	} else if (type == "Mirror") {

		Ray newRay{ best_intersectionPoint, ray.calculateNewDirection(ray.getDirection(), currentNormal), hitFace, &ray };
		ray.setNextRay(&newRay);

		incomingRayColor = shootRay(newRay, S); // Shoot the newly created ray into the scene

		ray.setRayColor(incomingRayColor * hitFace->getMaterial().getColor()); // Could multiply with surface color to get a tinted mirror

	} else if (type == "Lambertian") {

		// Create uniformly distributed numbers between -1 and 1
		std::random_device rand_dev;
		std::mt19937 generator{ rand_dev() };
		std::uniform_real_distribution<float> distribution{ 0.0f, 1.0f };

		// The random number
		float y = distribution(generator);

		// Inclination angle and azemut depending on the random number
		float inclinationAngle = acos(sqrt(1 - y));
		float azemut = 2.0f * M_PI * y;

		// Calculate where the new direction would intersect the hemisphere
		Vertex xO = { cos(azemut) * sin(inclinationAngle), sin(azemut) * sin(inclinationAngle), cos(inclinationAngle)};

		// Local coordinate system
		Direction xL = glm::normalize(-ray.getDirection() + glm::dot(currentNormal, ray.getDirection()) * currentNormal);
		Direction zL = currentNormal;
		Direction yL = glm::cross(zL, xL);

		// Calculate the intersection point between hemisphere and the outgoing ray
		Vertex xW = {
			xO.x * xL.x + xO.y * yL.x + xO.z * zL.x,
			xO.x * xL.y + xO.y * yL.y + xO.z * zL.y,
			xO.x * xL.z + xO.y * yL.z + xO.z * zL.z
		};

		// Calculate the new direction
		Direction newDirection = xW - best_intersectionPoint;

		// Creates a new ray depending on the new direction
		Ray newRay{ best_intersectionPoint, newDirection, hitFace, &ray };
		ray.setNextRay(&newRay);

		// Shoot a new ray into the scene
		incomingRayColor = shootRay(newRay, S);
		
		// Set ray color depending on the incoming ray color and the direct light
		//ray.setRayColor( hitFace->getMaterial().getColor() * incomingRayColor + shootShadowRays(S, hitFace, best_intersectionPoint, currentNormal));
		ray.setRayColor(hitFace->getMaterial().getColor() * hitFace->getMaterial().getBRDF() * (incomingRayColor + shootShadowRays(S, hitFace, best_intersectionPoint, currentNormal)));
	
	}

	return ray.getColor();
}


Color Camera::shootShadowRays(const Scene& S, Surface* hitSurface, Vertex hitPoint ,Direction n_x) {
	
	std::random_device rand_dev;
	std::mt19937 generator{ rand_dev() };
	std::uniform_real_distribution<float> distribution{ 0.0f, 1.0f };

	Surface* lamp = S.polygons[0];
	Direction e1 = lamp->getPoints()[1] - lamp->getPoints()[0];
	Direction e2 = lamp->getPoints()[3] - lamp->getPoints()[0];
	Vertex intersectionPoint;
	Color accLight = { 0.0f, 0.0f, 0.0f };

	float lightArea = glm::length(e1) * glm::length(e2);
	float w = lightArea * 40.0f;
	float V = 1.0f;

	int counter = 0;
	int numberOfShadowRays = 20;

	if (glm::dot(n_x, lamp->getNormal()) > 0) {
		return { 0.0f , 0.0f, 0.0f };
	}

	while (counter < numberOfShadowRays) {

		float rand1 = distribution(generator);
		float rand2 = distribution(generator);

		Vertex lampCoordinate = lamp->getPoints()[0] + rand1 * e1 + rand2 * e2;

		Direction distance = lampCoordinate - hitPoint;
		float distLen = glm::length(distance);

		for (int i = 0; i < S.spheres.size(); ++i) {
			if (S.spheres[i]->intersection(distance, hitPoint, intersectionPoint)) {

				float newDist = glm::length(intersectionPoint - hitPoint);

				if (newDist < distLen) {
					V = 0.0; // The pixel is in shadow
					break;
				}
			}
		}

		Direction cosy = -1.0f*lamp->getNormal() * distance / distLen;
		Direction cosx = n_x * distance / distLen;
		accLight += V * (cosy * cosx) / powf(distLen, 2.0f);

		++counter;
	}

	accLight = accLight * (w / numberOfShadowRays);
	return accLight;
}