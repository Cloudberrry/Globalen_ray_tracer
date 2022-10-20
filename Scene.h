#pragma once
#include "Triangle.h"
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

		spheres.push_back(&sphere1);
	}

	void addPolygon(Surface* P) { polygons.push_back(P); }
	
	// Some colors
	Color red{ 1.0f, 0.0f, 0.0f };
	Color green{ 0.0f, 1.0f, 0.0f };
	Color blue{ 0.0f, 0.0f, 1.0f };
	Color gray{ 0.2f, 0.2f, 0.2f };
	Color white{ 1.0f, 1.0f, 1.0f };
	Color yellow{ 1.0f, 1.0f, 0.0f };
	Color magenta{ 1.0f, 0.0f, 1.0f };
	Color cyan{ 0.0f, 1.0f, 1.0f };
	Color custom{ 0.75f, 1.0f, 0.6f };


	Material mirror{ "Mirror", white, 1.0f, 1.0f };
	Material glass{ "Glass", white, 1.0f, 1.5f };
	Material lamp{ "Lamp", white, 1.0f, 1.0f };
	std::vector<Surface*> polygons;
	std::vector<Surface*> spheres;

private:
	

	// Floor
	Triangle floorTrig1{ {-3, 0, -5.0f}, {0, -6, -5.0f},  {0, 6, -5.0f}, {"Lambertian", white} };
	Triangle floorTrig2{ {10, 6, -5.0f}, {10, -6, -5.0f}, {13, 0, -5.0f},  {"Lambertian", white} };
	Rectangle floorRectangle{ {0, -6, -5.0f}, {10, -6, -5.0f}, {10, 6, -5.0f}, {0, 6, -5.0f}, {"Lambertian", white} };

	// Ceiling
	Triangle ceilTrig1{ {0, -6, 5.0f}, {-3, 0, 5.0f}, {0, 6, 5.0f}, {"Lambertian", white} };
	Triangle ceilTrig2{ {13, 0, 5.0f}, {10, -6, 5.0f}, {10, 6, 5.0f}, {"Lambertian", white} };
	Rectangle ceilRectangle{ {0, -6, 5.0f},  {0, 6, 5.0f}, {10, 6, 5.0f}, {10, -6, 5.0f}, {"Lambertian", white} };

	// Walls
	Rectangle wall1{ {10, -6, -5}, {0, -6, -5}, {0, -6, 5}, {10, -6, 5}, {"Lambertian", red} };
	Rectangle wall2{ {13, 0, -5}, {10, -6, -5}, {10, -6, 5}, {13, 0, 5}, mirror};
	Rectangle wall3{ {10, 6, -5}, {13, 0, -5}, {13, 0, 5}, {10, 6, 5}, {"Lambertian", blue} };
	Rectangle wall4{ {0, 6, -5}, {10, 6, -5}, {10, 6, 5}, {0, 6, 5}, {"Lambertian", yellow} };
	Rectangle wall5{ {-3, 0, -5}, {0, 6, -5}, {0, 6, 5}, {-3, 0, 5}, {"Lambertian", magenta} };
	Rectangle wall6{ {0, -6, -5}, {-3, 0, -5}, {-3, 0, 5}, {0, -6, 5}, {"Lambertian", cyan} };

	// Add lamp
	Rectangle ceilLamp{ {6.0f, -1.0f, 5.0f},  {6.0f, 1.0f, 5.0f}, {8.0f, 1.0f, 5.0f}, {8.0f, -1.0f, 5.0f}, lamp };

	// Spheres
	Sphere sphere1{ {8.0f, 0.0f, 0.0f}, 2.0f, {"Lambertian", red} };
};