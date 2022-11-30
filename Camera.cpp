#include "Camera.h"
#include <stdlib.h>

Camera::Camera(int pixHeight, int pixWidth, int raysPerPixel, int shadowRaysPerIntersection)
	: height{ pixHeight }, width{ pixWidth }, numberOfRays{ raysPerPixel }, numberOfShadowRays{ shadowRaysPerIntersection }, iMax{ 0.0 }, pixelWidth{ 2.0 / pixHeight }
{
	std::cout << "Setting up camera object..." << std::endl;
	pixelImage.resize(height, std::vector<Color> (width));
}


void Camera::setPixels(const Scene& S) {

	std::cout << "Calculating pixel colors..." << std::endl;

	// Declaration of some constants and some variables
	const Vertex eyePosition = { -1.0, 0.0, 0.0 };
	Vertex pixelPos;
	Direction currentDirection;
	int rayDepth = 0;
	std::random_device rand_dev;
	std::mt19937 generator{ rand_dev() };
	std::uniform_real_distribution<double> distribution{ 0.0, pixelWidth };

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Color average_color = { 0.0, 0.0, 0.0 };
			for (int a = 0; a < numberOfRays; ++a) {

				// Two random numbers
				double y = distribution(generator);
				double z = distribution(generator);

				// Calculate the pixel position on the camera plane
				pixelPos = { 0.0, j * pixelWidth - (1.0 - pixelWidth - y), i * pixelWidth - (1.0 - pixelWidth - z) };
				currentDirection = glm::normalize(pixelPos - eyePosition);
				Ray firstRay{ pixelPos, currentDirection };

				average_color += shootRay(firstRay, S, rayDepth);
				rayDepth = 0;
			}

			//average_color = { average_color.x * 255.0 / numberOfRays, average_color.y * 255.0 / numberOfRays, average_color.z * 255.0 / numberOfRays };
			average_color = { sqrt(average_color.x / numberOfRays) * 255.0, sqrt(average_color.y / numberOfRays) * 255.0, sqrt(average_color.z / numberOfRays) * 255.0 };
		
			pixelImage[i][j] = average_color;

			double newiMax = glm::max(glm::max(pixelImage[i][j].x, pixelImage[i][j].y), pixelImage[i][j].z);

			if ( newiMax > iMax) {
				iMax = newiMax;
			}
		}
	}
}

void Camera::render() const{

	std::cout << "Rendering pixels to the image..." << std::endl;

	// ofstream operator to write the pixel colors to a ppm file
	std::ofstream ofs("./scene.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << height << " " << width << "\n255\n";

	std::cout << "Maximum color value: " << iMax << std::endl;

	// Portable pixel map(ppm) writes the coordinates starting from the top left corner and goes down to the bottom right
	for (int i = height-1; i >= 0; --i) {
		for (int j = width-1; j >= 0; --j) {
			ofs << (unsigned char)((pixelImage[i][j].r) * (255.0 / iMax)) <<
				(unsigned char)((pixelImage[i][j].g) * (255.0 / iMax)) <<
				(unsigned char)((pixelImage[i][j].b) * (255.0 / iMax));
		}
	}
	ofs.close();

	std::cout << "Render complete!" << std::endl;
}

void Camera::setNumberOfRaysPerPixel(const int rays) {
	numberOfRays = rays;
}

void Camera::setNumberOfShadowRays(const int shadowRays) {
	numberOfShadowRays = shadowRays;
}

void Camera::setMaximumRayDepth(const int depth) {
	maxRayDepth = depth;
}

Color Camera::shootRay(Ray& ray, const Scene& S, int& rayDepth) const {

	Vertex intersectionPoint;			// The intersection point
	Vertex closest_intersectionPoint;	// The intersection point with the smallest distance to the starting point of the ray
	Vertex currentStartingPoint = ray.getStartingPoint();
	Direction currentNormal;			// The normal of the intersected surface at the intersection point
	Direction currentDirection = ray.getDirection();
	Color surfaceColor;					// The color of the intersected surface
	Surface* hitSurface = nullptr;		// A pointer to the intersected surface
	std::string type;					// The type of the intersected surface
	double smallestDist = 10000000.0;	// The current smallest distance to an intersection point
	double BRDF;						// The value of the BRDF
	

	// Check if ray intersects any of the objects in the scene
	for (int i = 0; i < S.objects.size(); ++i) {

		// Sphere intersects itself!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (S.objects[i]->intersection(currentDirection, currentStartingPoint, intersectionPoint)) {

			// The distance between the intersection point and the starting oint of the ray
			double newDist = glm::length(intersectionPoint - currentStartingPoint);

			// Check if the intersected surface is closer than any other intersected surface
			if (newDist < smallestDist) {
				hitSurface = S.objects[i];
				smallestDist = newDist;
				closest_intersectionPoint = intersectionPoint;
				currentNormal = hitSurface->getNormal();
			}
		}
	}

	// If the ray did not intersect with any object in the scene, the ray must intersect either the wall, floor, ceiling, or a light source
	if (hitSurface == nullptr) {

		// Go through all the light sources in the scene
		for (int i = 0; i < S.lights.size(); ++i) {
			if (S.lights[i]->intersection(currentDirection, currentStartingPoint, intersectionPoint)) {

				// The distance between the intersection point and the starting oint of the ray
				double newDist = glm::length(intersectionPoint - currentStartingPoint);

				// Check if the intersected surface is closer than any other intersected surface
				if (newDist < smallestDist) {
					hitSurface = S.lights[i];
					smallestDist = newDist;
					closest_intersectionPoint = intersectionPoint;
					currentNormal = hitSurface->getNormal();
				}
			}
		}

		// Go through all polygons in the scene
		for (int i = 0; i < S.polygons.size(); ++i) {
			if (S.polygons[i]->intersection(currentDirection, currentStartingPoint, intersectionPoint)) {

				// The distance between the intersection point and the starting oint of the ray
				double newDist = glm::length(intersectionPoint - currentStartingPoint);

				// Check if the intersected surface is closer than any other intersected surface
				if (newDist < smallestDist) {
					hitSurface = S.polygons[i];
					smallestDist = newDist;
					closest_intersectionPoint = intersectionPoint;
					currentNormal = hitSurface->getNormal();
					break;
				}
			}
		}
	}

	
	// If the ray did not intersect with any surface (Which shouldn't happen) set the returning color to a bright green-ish color
	if (hitSurface == nullptr) {
		ray.setRayColor({0.0, 0.0, 0.0});
		return ray.getColor();
	}

	// Set the end point of the ray as well as the type, surfaceColor, and BRDF of the intersected surface
	ray.setEndPoint(closest_intersectionPoint);
	type = hitSurface->getMaterial().getType();
	surfaceColor = hitSurface->getMaterial().getColor();
	BRDF = hitSurface->getMaterial().getBRDF();
	

	// Create uniformly distributed numbers between 0 and 1
	std::random_device rand_dev;
	std::mt19937 generator{ rand_dev() };
	std::uniform_real_distribution<double> distribution{ 0.0, 1.0 };

	// The random number
	double y = distribution(generator);

	// Decide what should happen when the ray intersects with different types of materials.

	if (type == "Lamp") {

		// If the ray intersects with a lamp, return {1.0, 1.0, 1.0} (white, which is defined in Scene.h)
		ray.setRayColor(S.white);
		
	} else if (type == "Mirror")  {

		if (rayDepth > maxRayDepth) {
			return (BRDF * surfaceColor);
		}

		++rayDepth;
		// Create a new ray with starting point at the intersection point and shoot it in the reflected direction
		Ray newRay{ closest_intersectionPoint, hitSurface->calculateReflectedRayDirection(currentDirection, currentNormal), hitSurface, &ray };
		ray.setNextRay(&newRay);

		// Shoot the newly created ray into the scene
		newRay.setRayColor(shootRay(newRay, S, rayDepth));

		// Set the color of the ray
		ray.setRayColor(BRDF * surfaceColor * newRay.getColor());

	} else if (type == "Glass") {

		// Declare variables
		double n1;
		double n2;
		double omega;

		// Check From which direction the ray is intersecting the object
		if (ray.getRayState() == "Inside") {
			std::cout << "inne" << std::endl;
			currentNormal = -currentNormal;

			// The ray comes from within the glass object
			n1 = hitSurface->getMaterial().getRefractionIndex();
			n2 = 1.0;
			omega = acos(glm::dot(-currentDirection, currentNormal) / (glm::length(currentDirection) * glm::length(currentNormal)));

			// Calculate BRDF for the reflected(R) and the refracted(T) ray
			double R0 = pow(((n1 - n2) / (n1 + n2)), 2);
			double R = R0 + (1.0 - R0) * pow((1.0 - cos(omega)), 5);
			double T = 1.0 - R;

			double alpha = asin(n1 / n2);


			if (omega > alpha || y < R) {

				// Shoot reflected ray
				Ray reflectedRay{ closest_intersectionPoint, hitSurface->calculateReflectedRayDirection(currentDirection, currentNormal), hitSurface, &ray };
				ray.setNextRay(&reflectedRay);

				reflectedRay.setRayColor(shootRay(reflectedRay, S, rayDepth)); // Shoot the newly created ray into the scene
				ray.setRayColor(R * surfaceColor * reflectedRay.getColor());
			}
			else {

				// Shoot refracted ray
				Ray refractedRay{ closest_intersectionPoint, hitSurface->calculateRefractedRayDirection(currentDirection, currentNormal, (n1 / n2)), hitSurface, &ray };
				ray.setNextRay(&refractedRay);
				refractedRay.setRayState("Outside");


				refractedRay.setRayColor(shootRay(refractedRay, S, rayDepth)); // Shoot the newly created ray into the scene
				ray.setRayColor(T * surfaceColor * refractedRay.getColor());
			}
		} else {

			// The ray comes from outside the glass object
			n1 = 1.0;
			n2 = hitSurface->getMaterial().getRefractionIndex();
			omega = acos(glm::dot(-currentDirection, currentNormal) / (glm::length(-currentDirection) * glm::length(currentNormal)));

			// Calculate BRDF for the reflected(R) and the refracted(T) ray
			double R0 = pow(((n1 - n2) / (n1 + n2)), 2);
			double R = R0 + (1.0 - R0) * pow((1.0 - cos(omega)), 5);
			double T = 1.0 - R;


			if (y < R) {


				// Shoot reflected ray
				Ray reflectedRay{ closest_intersectionPoint, hitSurface->calculateReflectedRayDirection(currentDirection, currentNormal), hitSurface, &ray };
				ray.setNextRay(&reflectedRay);

				reflectedRay.setRayColor(shootRay(reflectedRay, S, rayDepth)); // Shoot the newly created ray into the scene
				ray.setRayColor(R * surfaceColor * reflectedRay.getColor());
			}
			else {

				// Shoot refracted ray
				Ray refractedRay{ closest_intersectionPoint, hitSurface->calculateRefractedRayDirection(currentDirection, currentNormal, (n1 / n2)), hitSurface, &ray };
				ray.setNextRay(&refractedRay);
				refractedRay.setRayState("Inside");


				refractedRay.setRayColor(shootRay(refractedRay, S, rayDepth)); // Shoot the newly created ray into the scene
				ray.setRayColor(T * surfaceColor * refractedRay.getColor());
			}
		}
		
		

	} else if (type == "Lambertian") {

		// Calculate the inclination angle and azimuth depending on the random number
		double inclinationAngle = acos(sqrt(1.0 - y));
		double azimuth = 2.0 * M_PI * y / hitSurface->getMaterial().getRho();

		if (azimuth <= 2.0 * M_PI) {

			// Calculate where the random direction would intersect the hemisphere
			Vertex xO = { cos(azimuth) * sin(inclinationAngle), sin(azimuth) * sin(inclinationAngle), cos(inclinationAngle) };

			// Create the local coordinate system
			Direction xL = glm::normalize(-1.0 * currentDirection + glm::dot(currentNormal, currentDirection) * currentNormal);
			Direction zL = currentNormal;
			Direction yL = glm::cross(zL, xL);

			// Calculate the intersection point between hemisphere and the outgoing ray in the world system
			Vertex xW = {
				xO.x * xL.x + xO.y * yL.x + xO.z * zL.x,
				xO.x * xL.y + xO.y * yL.y + xO.z * zL.y,
				xO.x * xL.z + xO.y * yL.z + xO.z * zL.z
			};

			// Calculate the new direction (Should already be normalized)
			Direction newDirection = glm::normalize(xW - closest_intersectionPoint);

			// Creates a new ray with the new direction
			Ray newRay{ closest_intersectionPoint, newDirection, hitSurface, &ray };
			ray.setNextRay(&newRay);

			// Shoot a new ray into the scene
			newRay.setRayColor(shootRay(newRay, S, rayDepth));


			Color totalDirectLight = { 0.0, 0.0, 0.0 };

			// Calculate the total direct illumination from all the light sources
			for (int i = 0; i < S.lights.size(); ++i) {
				totalDirectLight += shootShadowRays(S, S.lights[i], hitSurface, closest_intersectionPoint, currentNormal);
			}

			// Set ray color depending on the incoming ray color and the direct light
			ray.setRayColor(BRDF * surfaceColor * newRay.getColor() + totalDirectLight);

		} else {

			// If the ray is terminated, calculate the total direct light and return the color
			Color totalDirectLight = {0.0, 0.0, 0.0};

			for (int i = 0; i < S.lights.size(); ++i) {
				totalDirectLight += shootShadowRays(S, S.lights[i], hitSurface, closest_intersectionPoint, currentNormal);
			}

			// Set ray color depending on the direct light
			ray.setRayColor(totalDirectLight);
			//ray.setRayColor(hitFace->getMaterial().getColor());
		}
	}

	return ray.getColor();
}


Color Camera::shootShadowRays(const Scene& S, Surface* lamp, Surface*& hitSurface, const Vertex& intersectionPoint, const Direction& n_x) const {
	
	// Create uniformly distributed numbers between 0 and 1
	std::random_device rand_dev;
	std::mt19937 generator{ rand_dev() };
	std::uniform_real_distribution<double> distribution{ 0.0, 1.0 };

	// Get two edges of the lamp
	Direction e1 = lamp->getPoints()[1] - lamp->getPoints()[0];
	Direction e2 = lamp->getPoints()[3] - lamp->getPoints()[0];

	// The intersection point between shadow ray and
	Vertex objectPoint;
	Color accLight = { 0.0, 0.0, 0.0 };

	// Calculate the area of the light source
	double lightArea = glm::length(e1) * glm::length(e2);

	// If V = 0, the pixel is in shadow, otherwise it gets light from the light source
	double V;

	Vertex Le = {1.0, 1.0, 1.0};

	// Unsure how to decide how strong the light sources are, so they are scaled until it looks good
	Vertex w = lightArea * Le * 40.0;

	// Counter for the while loop, could probably be done with a for-loop instead of a while-loop
	int counter = 0;
	
	while (counter < numberOfShadowRays) {

		// Reset V to 1 for every iteration
		V = 1.0;

		// Calculate two random numbers
		double rand1 = distribution(generator);
		double rand2 = distribution(generator);

		// Calculate a random coordinate on the light source
		Vertex lampCoordinate = lamp->getPoints()[0] + rand1 * e1 + rand2 * e2;

		// Calculate the vector going from the intersection point on the surface and a point on the light source
		Direction shadowRay = lampCoordinate - intersectionPoint;

		// Calculate the distance between the intersection point on the surface and a point on the light source
		double distLen = glm::length(shadowRay);

		// If the dot product between the vector from the intersection point of the surface and the light source is negative, the point does not contribute any light (V = 0)
		if (glm::dot(n_x, shadowRay) < 0) {
			++counter;
			continue;
		}

		// Check if the shadow ray intersects any object in the scene (Shadow rays does not intersect its own starting surface)
		for (int i = 0; i < S.objects.size(); ++i) {
			if (hitSurface != S.objects[i] && S.objects[i]->intersection(glm::normalize(shadowRay), intersectionPoint, objectPoint)) {

				// The pixel is in shadow and we don't need to check if the shadow ray intersects any other objects
				V = 0.0; 
				break;
			}
		}

		// Calculate cos(y) and cos(x)
		double cosy = glm::dot(-1.0 * lamp->getNormal(), shadowRay) / distLen;
		double cosx = glm::dot(n_x, shadowRay) / distLen;

		// Add to the accumulated light
		accLight += V * (cosy * cosx) / pow(distLen, 2);
		
		++counter;
	}

	// Multiply the accumulated light with everything outside of the sum
	accLight *= hitSurface->getMaterial().getBRDF() * hitSurface->getMaterial().getColor() * (w / (double)numberOfShadowRays);

	return accLight;
}