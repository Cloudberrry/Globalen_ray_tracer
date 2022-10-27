#include "Camera.h"
#include <stdlib.h>

Camera::Camera(int pixHeight, int pixWidth, int raysPerPixel, int shadowRaysPerIntersection)
	: height{ pixHeight }, width{ pixWidth }, numberOfRays{ raysPerPixel }, numberOfShadowRays{ shadowRaysPerIntersection }, iMax{ 0.0 }, pixelWidth{ 2.0 / pixHeight }
{
	pixelImage.resize(height, std::vector<Color> (width));
}


void Camera::setPixels(const Scene& S) {

	
	double newiMax;
	Vertex pixelPos;
	Vertex eyePosition = {-1.0, 0.0, 0.0};
	Direction currentDirection;
	int rayDepth = -1;
	

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {

			pixelPos = { 0.0, j * pixelWidth - (1.0 - pixelWidth), i * pixelWidth - (1.0 - pixelWidth) };
			currentDirection = glm::normalize(pixelPos - eyePosition);
			Ray firstRay{ pixelPos, currentDirection };
			
			Color average_color = { 0.0, 0.0, 0.0 };
			for (int a = 0; a < numberOfRays; ++a) {
				average_color += shootRay(firstRay, S, rayDepth);
				rayDepth = -1;
			}

			//average_color = { average_color.x * 255.0 / numberOfRays, average_color.y * 255.0 / numberOfRays, average_color.z * 255.0 / numberOfRays };
			average_color = { sqrt(average_color.x * 255.0 / numberOfRays), sqrt(average_color.y * 255.0 / numberOfRays), sqrt(average_color.z * 255.0 / numberOfRays) };
		
			pixelImage[i][j] = average_color;

			newiMax = glm::max(glm::max(pixelImage[i][j].x, pixelImage[i][j].y), pixelImage[i][j].z);

			if ( newiMax > iMax) {
				iMax = newiMax;
			}
		}
	}
}

void Camera::render() const{

	std::ofstream ofs("./scene.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << height << " " << width << "\n255\n";

	std::cout << "iMax: " << iMax << std::endl;

	// Portable pixel map(ppm) writes the coordinates starting from the top left corner and goes down to the bottom right
	for (int i = height-1; i >= 0; --i) {
		for (int j = width-1; j >= 0; --j) {
			ofs << (unsigned char)((pixelImage[i][j].r) * (255.0 / iMax)) <<
				(unsigned char)((pixelImage[i][j].g) * (255.0 / iMax)) <<
				(unsigned char)((pixelImage[i][j].b) * (255.0 / iMax));
		}
	}
	ofs.close();

	std::cout << "Finished" << std::endl;
}

Color Camera::shootRay(Ray& ray, const Scene& S, int& rayDepth) const {

	Vertex intersectionPoint;		// To calculate distance
	Vertex best_intersectionPoint;	// For final intersection
	Direction currentNormal;
	Color incomingRayColor;
	Color incomingRefractedRayColor;
	Color surfaceColor;
	Surface* hitFace = nullptr;
	std::string type;
	double smallestDist = 10000000.0;
	double BRDF;
	

	for (int i = 0; i < S.objects.size(); ++i) {
		if (S.objects[i]->intersection(ray.getDirection(), ray.getStartingPoint(), intersectionPoint)) {

			double newDist = glm::length(intersectionPoint - ray.getStartingPoint());

			if (newDist < smallestDist) {
				hitFace = S.objects[i];
				smallestDist = newDist;
				best_intersectionPoint = intersectionPoint;
				currentNormal = hitFace->getNormal();
			}
		}
	}

	if (hitFace == nullptr) {

		for (int i = 0; i < S.lights.size(); ++i) {
			if (S.lights[i]->intersection(ray.getDirection(), ray.getStartingPoint(), intersectionPoint)) {

				double newDist = glm::length(intersectionPoint - ray.getStartingPoint());

				if (newDist < smallestDist) {
					hitFace = S.lights[i];
					smallestDist = newDist;
					best_intersectionPoint = intersectionPoint;
					currentNormal = hitFace->getNormal();
				}
			}
		}

		// Go through all polygons in the scene
		for (int i = 0; i < S.polygons.size(); ++i) {

			if (S.polygons[i]->intersection(ray.getDirection(), ray.getStartingPoint(), intersectionPoint)) {

				double newDist = glm::length(intersectionPoint - ray.getStartingPoint());

				if (newDist < smallestDist) {
					hitFace = S.polygons[i];
					smallestDist = newDist;
					best_intersectionPoint = intersectionPoint;
					currentNormal = hitFace->getNormal();
				}
			}
		}
	}

	
	// Should never happen, but it does :))))))))))
	if (hitFace == nullptr) {
		ray.setRayColor(S.custom);
		return ray.getColor();
	}

	ray.setEndPoint(best_intersectionPoint);
	type = hitFace->getMaterial().getType();
	surfaceColor = hitFace->getMaterial().getColor();
	BRDF = hitFace->getMaterial().getBRDF();
	
	if (type == "Lamp") {

		ray.setRayColor(S.white);

	} else if (type == "Mirror")  {

		if (rayDepth > 10) {
			return surfaceColor;
		}

		++rayDepth;

		Ray newRay{ best_intersectionPoint, ray.calculateNewDirection(ray.getDirection(), currentNormal), hitFace, &ray };
		ray.setNextRay(&newRay);

		// Shoot the newly created ray into the scene
		incomingRayColor = shootRay(newRay, S, rayDepth); 

		ray.setRayColor(BRDF * surfaceColor * incomingRayColor);

	} else if (type == "Glass") {

		if (rayDepth > 10) {
			return surfaceColor;
		}

		++rayDepth;

		double n1;
		double n2;

		if (glm::dot(ray.getDirection(), currentNormal) > 0) {
			n1 = hitFace->getMaterial().getRefractionIndex();
			n2 = 1.0;
		} else {
			n1 = 1.0;
			n2 = hitFace->getMaterial().getRefractionIndex();
		}


		/*if (n1 * sin(OMEGA / n2)) {

		}*/
		

		Ray reflectedRay{ best_intersectionPoint, ray.calculateNewDirection(ray.getDirection(), currentNormal), hitFace, &ray };
		Ray refractedRay{ best_intersectionPoint, ray.calculateRefractedRay(ray.getDirection(), currentNormal, (n1/n2)), hitFace, &ray };

		incomingRayColor = shootRay(reflectedRay, S, rayDepth); // Shoot the newly created ray into the scene
		incomingRefractedRayColor = shootRay(refractedRay, S, rayDepth); // Shoot the newly created ray into the scene

		ray.setRayColor(BRDF * surfaceColor * incomingRayColor + BRDF * surfaceColor * incomingRefractedRayColor);


	} else if (type == "Lambertian") {

		// Create uniformly distributed numbers between 0 and 1
		std::random_device rand_dev;
		std::mt19937 generator{ rand_dev() };
		std::uniform_real_distribution<double> distribution{ 0.0, 1.0 };
		
		// The random number
		double y = distribution(generator);

		// Inclination angle and azemut depending on the random number
		double inclinationAngle = acos(sqrt(1.0 - y));
		double azimut = 2.0 * M_PI * y / hitFace->getMaterial().getRho();

		if (azimut <= 2.0 * M_PI && rayDepth < 10) {

			++rayDepth;

			// Calculate where the new direction would intersect the hemisphere
			Vertex xO = { cos(azimut) * sin(inclinationAngle), sin(azimut) * sin(inclinationAngle), cos(inclinationAngle) };

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
			Direction newDirection = glm::normalize(xW - best_intersectionPoint);

			// Creates a new ray depending on the new direction
			Ray newRay{ best_intersectionPoint, newDirection, hitFace, &ray };
			ray.setNextRay(&newRay);

			// Shoot a new ray into the scene
			incomingRayColor = shootRay(newRay, S, rayDepth);


			Color totalDirectLight = { 0.0, 0.0, 0.0 };

			for (int i = 0; i < S.lights.size(); ++i) {
				totalDirectLight += shootShadowRays(S, S.lights[i], hitFace, best_intersectionPoint, currentNormal);
			}

			// Set ray color depending on the incoming ray color and the direct light
			//ray.setRayColor( hitFace->getMaterial().getBRDF() * hitFace->getMaterial().getColor() * incomingRayColor);
			ray.setRayColor(BRDF * surfaceColor * incomingRayColor + totalDirectLight);
		} else {

			Color totalDirectLight = {0.0, 0.0, 0.0};

			for (int i = 0; i < S.lights.size(); ++i) {
				totalDirectLight += shootShadowRays(S, S.lights[i], hitFace, best_intersectionPoint, currentNormal);
			}

			ray.setRayColor(totalDirectLight);
			//ray.setRayColor(hitFace->getMaterial().getColor());
		}
	}

	return ray.getColor();
}


Color Camera::shootShadowRays(const Scene& S, Surface* lamp, Surface*& hitSurface, const Vertex& hitPoint, const Direction& n_x) const {
	
	std::random_device rand_dev;
	std::mt19937 generator{ rand_dev() };
	std::uniform_real_distribution<double> distribution{ 0.0, 1.0 };

	Direction e1 = lamp->getPoints()[1] - lamp->getPoints()[0];
	Direction e2 = lamp->getPoints()[3] - lamp->getPoints()[0];
	Vertex intersectionPoint;
	Color accLight = { 0.0, 0.0, 0.0 };

	double lightArea = glm::length(e1) * glm::length(e2);
	double V;
	Vertex Le = {1.0, 1.0, 1.0};
	Vertex w = lightArea * Le * 40.0;

	int counter = 0;
	
	while (counter < numberOfShadowRays) {
		V = 1.0;

		double rand1 = distribution(generator);
		double rand2 = distribution(generator);

		Vertex lampCoordinate = lamp->getPoints()[0] + rand1 * e1 + rand2 * e2;

		Direction distance = lampCoordinate - hitPoint;

		double distLen = glm::length(distance);

		if (glm::dot(n_x, distance) < 0) {
			++counter;
			continue;
		}

		for (int i = 0; i < S.objects.size(); ++i) {
			if (hitSurface != S.objects[i] && S.objects[i]->intersection(glm::normalize(distance), hitPoint, intersectionPoint)) {

				double newDist = glm::length(intersectionPoint - hitPoint);

				if (newDist < distLen) {
					V = 0.0; // The pixel is in shadow
					break;
				}	
			}
		}

		double cosy = glm::dot(-lamp->getNormal(), distance) / distLen;
		double cosx = glm::dot(n_x, distance) / distLen;

		accLight = accLight + V * (cosy * cosx) / pow(distLen, 2);
		
		++counter;
	}

	accLight = accLight * hitSurface->getMaterial().getBRDF() * hitSurface->getMaterial().getColor() * (w / (double)numberOfShadowRays);

	return accLight;
}