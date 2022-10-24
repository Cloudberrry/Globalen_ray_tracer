#pragma once
#include "Tetrahedron.h"
#include "Rectangle.h"
#include "Sphere.h"

class Scene {
public:
	Scene() {

		// Add lights
		polygons.push_back(&ceilLamp);

		// Adds the polygons for the floor
		polygons.push_back(&floorTrig1);
		polygons.push_back(&floorTrig2);
		polygons.push_back(&floorRectangle);

		// Adds the polygons for the ceiling
		polygons.push_back(&ceilTrig1);
		polygons.push_back(&ceilTrig2);
		polygons.push_back(&ceilRectangle);

		// Adds the polygons for the walls
		polygons.push_back(&wall1);
		polygons.push_back(&wall2);
		polygons.push_back(&wall3);
		polygons.push_back(&wall4);
		polygons.push_back(&wall5);
		polygons.push_back(&wall6);

		/*objects.push_back(&sphere1);
		objects.push_back(&sphere2);*/
		objects.push_back(&tetrahedron1);
	}

	void addPolygon(Surface* P) { polygons.push_back(P); }
	
	// Some colors
	Color red{ 1.0, 0.0, 0.0 };
	Color green{ 0.0, 1.0, 0.0 };
	Color blue{ 0.0, 0.0, 1.0 };
	Color gray{ 0.2, 0.2, 0.2 };
	Color white{ 1.0, 1.0, 1.0 };
	Color yellow{ 1.0, 1.0, 0.0 };
	Color magenta{ 1.0, 0.0, 1.0 };
	Color cyan{ 0.0, 1.0, 1.0 };
	Color custom{ 0.75, 1.0, 0.6 };


	Material mirror{ "Mirror", white, 1.0, 1.0 };
	Material glass{ "Glass", white, 1.0, 1.5 };
	Material lamp{ "Lamp", white, 1.0, 1.0 };

	std::vector<Surface*> polygons;
	std::vector<Surface*> objects;
	std::vector<Surface*> lights;

private:
	

	// Floor
	Triangle floorTrig1{ {-3, 0, -5.0}, {0, -6, -5.0},  {0, 6, -5.0}, {"Lambertian", white} };
	Triangle floorTrig2{ {10, 6, -5.0}, {10, -6, -5.0}, {13, 0, -5.0},  {"Lambertian", white} };
	Rectangle floorRectangle{ {0, -6, -5.0}, {10, -6, -5.0}, {10, 6, -5.0}, {0, 6, -5.0}, {"Lambertian", white} };

	// Ceiling
	Triangle ceilTrig1{ {0, -6, 5.0}, {-3, 0, 5.0}, {0, 6, 5.0}, {"Lambertian", white} };
	Triangle ceilTrig2{ {13, 0, 5.0}, {10, -6, 5.0}, {10, 6, 5.0}, {"Lambertian", white} };
	Rectangle ceilRectangle{ {0, -6, 5.0},  {0, 6, 5.0}, {10, 6, 5.0}, {10, -6, 5.0}, {"Lambertian", white} };

	// Walls
	Rectangle wall1{ {10, -6, -5}, {0, -6, -5}, {0, -6, 5}, {10, -6, 5}, {"Lambertian", red} };
	Rectangle wall2{ {13, 0, -5}, {10, -6, -5}, {10, -6, 5}, {13, 0, 5}, mirror };
	Rectangle wall3{ {10, 6, -5}, {13, 0, -5}, {13, 0, 5}, {10, 6, 5}, {"Lambertian", blue} };
	Rectangle wall4{ {0, 6, -5}, {10, 6, -5}, {10, 6, 5}, {0, 6, 5}, {"Lambertian", yellow} };
	Rectangle wall5{ {-3, 0, -5}, {0, 6, -5}, {0, 6, 5}, {-3, 0, 5}, {"Lambertian", magenta} };
	Rectangle wall6{ {0, -6, -5}, {-3, 0, -5}, {-3, 0, 5}, {0, -6, 5}, {"Lambertian", cyan} };

	// Add lamp
	Rectangle ceilLamp{ {2.0, -2.0, 5.0},  {2.0, 2.0, 5.0}, {4.0, 2.0, 5.0}, {4.0, -2.0, 5.0}, lamp };

	// Spheres
	Sphere sphere1{ 2.0, {7.0, 2.0, -2.0}, mirror };
	Sphere sphere2{ 1.0, {9.0, -3.0, 0.0}, {"Lambertian", custom} };

	// Tetrahedrons
	Tetrahedron tetrahedron1{ {6.0, -2.0, -1.0}, {4.0, 0.0, -1.0}, {6.0, 2.0, -1.0}, {5.0, 0.0, 1.0}, {"Lambertian", magenta} };
};