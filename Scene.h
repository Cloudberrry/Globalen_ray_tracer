#pragma once
#include "Tetrahedron.h"
#include "Rectangle.h"
#include "Sphere.h"

class Scene {
public:
	Scene() {

		// Add lights
		lights.push_back(&ceilLamp);
		lights.push_back(&wallLamp);

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

		objects.push_back(&sphere1);
		objects.push_back(&sphere2);
		objects.push_back(&tetrahedron1);
	}

	void addPolygon(Surface* P) { polygons.push_back(P); }
	
	// Some colors
	const Color red{ 0.8, 0.05, 0.05 };
	const Color green{ 0.05, 0.8, 0.05 };
	const Color blue{ 0.05, 0.05, 0.8 };
	const Color gray{ 0.2, 0.2, 0.2 };
	const Color yellow{ 0.8, 0.8, 0.05 };
	const Color magenta{ 0.8, 0.05, 0.8 };
	const Color cyan{ 0.05, 0.8, 0.8 };

	const Color white{ 1.0, 1.0, 1.0 };
	const Color almostWhite{ 0.9, 0.9, 0.9 };

	const Color custom{ 0.55, 0.8, 0.4 };


	const Material mirror{ "Mirror", white, 1.0, 0.0 };
	const Material lowReflectiveMirror{ "Mirror", white, 0.4, 0.0 };

	const Material glass{ "Glass", white, 1.0, 1.5 };
	const Material lowReflectiveGlass{ "Glass", white, 0.4, 1.5 };

	const Material lamp{ "Lamp", white, 1.0};

	std::vector<Surface*> polygons;
	std::vector<Surface*> objects;
	std::vector<Surface*> lights;

private:
	

	// Floor
	Triangle floorTrig1{ {-3.0, 0.0, -5.0}, {0.0, -6.0, -5.0},  {0.0, 6.0, -5.0}, {"Lambertian", almostWhite} };
	Triangle floorTrig2{ {10.0, 6.0, -5.0}, {10.0, -6.0, -5.0}, {13.0, 0.0, -5.0},  {"Lambertian", almostWhite} };
	Rectangle floorRectangle{ {0.0, -6.0, -5.0}, {10.0, -6.0, -5.0}, {10.0, 6.0, -5.0}, {0.0, 6.0, -5.0}, {"Lambertian", almostWhite} };

	// Ceiling
	Triangle ceilTrig1{ {0.0, -6.0, 5.0}, {-3.0, 0.0, 5.0}, {0.0, 6.0, 5.0}, {"Lambertian", almostWhite} };
	Triangle ceilTrig2{ {13.0, 0.0, 5.0}, {10.0, -6.0, 5.0}, {10, 6.0, 5.0}, {"Lambertian", almostWhite} };
	Rectangle ceilRectangle{ {0.0, -6.0, 5.0},  {0.0, 6.0, 5.0}, {10.0, 6.0, 5.0}, {10.0, -6.0, 5.0}, {"Lambertian", almostWhite} };

	// Walls
	Rectangle wall1{ {10.0, -6.0, -5.0}, {0.0, -6.0, -5.0}, {0.0, -6.0, 5.0}, {10.0, -6.0, 5.0}, {"Lambertian", red, 0.2} };
	Rectangle wall2{ {13.0, 0.0, -5.0}, {10.0, -6.0, -5.0}, {10.0, -6.0, 5.0}, {13.0, 0.0, 5.0}, mirror };
	Rectangle wall3{ {10.0, 6.0, -5.0}, {13.0, 0.0, -5.0}, {13.0, 0.0, 5.0}, {10.0, 6.0, 5.0}, {"Lambertian", blue, 0.9} };
	Rectangle wall4{ {0.0, 6.0, -5.0}, {10.0, 6.0, -5.0}, {10.0, 6.0, 5.0}, {0.0, 6.0, 5.0}, {"Lambertian", yellow, 0.7} };
	Rectangle wall5{ {-3.0, 0.0, -5.0}, {0.0, 6.0, -5.0}, {0.0, 6.0, 5.0}, {-3.0, 0.0, 5.0}, {"Lambertian", magenta, 0.6} };
	Rectangle wall6{ {0.0, -6.0, -5.0}, {-3.0, 0.0, -5.0}, {-3.0, 0.0, 5.0}, {0.0, -6.0, 5.0}, {"Lambertian", cyan, 0.4} };

	// Add lamp
	Rectangle ceilLamp{ {4.0, -1.0, 5.0},  {4.0, 1.0, 5.0}, {6.0, 1.0, 5.0}, {6.0, -1.0, 5.0}, lamp };
	Rectangle wallLamp{ {4.0, 6.0, -1.0},  {6.0, 6.0, -1.0}, {6.0, 6.0, 1.0}, {4.0, 6.0, 1.0}, lamp };

	// Spheres
	Sphere sphere1{ 2.0, {7.0, 2.0, -2.0}, mirror };
	Sphere sphere2{ 1.0, {6.0, -3.0, 0.0}, {"Lambertian", custom, 0.5} };

	// Tetrahedrons
	Tetrahedron tetrahedron1{ {5.0, -3.0, -4.0}, {3.0, -1.0, -4.0}, {5.0, 1.0, -4.0}, {4.0, -1.0, -2.0}, {"Lambertian", magenta, 1.0} };
};