#pragma once
#include "Triangle.h"
#include "Rectangle.h"

class Scene {
public:
	Scene() {

		// Add lights
		allPolygons.push_back(&ceilLamp);

		// Adds the polygons for the floor
		allPolygons.push_back(&floorTrig1);
		allPolygons.push_back(&floorTrig2);
		allPolygons.push_back(&floorRectangle);

		// Adds the polygons for the ceiling
		allPolygons.push_back(&ceilTrig1);
		allPolygons.push_back(&ceilTrig2);
		allPolygons.push_back(&ceilRectangle);

		// Adds the polygons for the walls
		allPolygons.push_back(&wall1);
		allPolygons.push_back(&wall2);
		allPolygons.push_back(&wall3);
		allPolygons.push_back(&wall4);
		allPolygons.push_back(&wall5);
		allPolygons.push_back(&wall6);
	}

	void addPolygon(Polygon* P) { allPolygons.push_back(P); }
	
	// Some colors
	Color red{ 1.0, 0.0, 0.0 };
	Color green{ 0.0, 1.0, 0.0 };
	Color blue{ 0.0, 0.0, 1.0 };
	Color gray{ 0.2, 0.2, 0.2 };
	Color white{ 1.0, 1.0, 1.0 };
	Color yellow{ 1.0, 1.0, 0.0 };
	Color magenta{ 1.0, 0.0, 1.0 };
	Color cyan{ 0.0, 1.0, 1.0 };


	Material mirror{ "Mirror", white, 1.0 };
	Material glass{ "Glass", white, 1.0, 1.5 };
	Material lamp{ "Lamp", white, 1.0, 1.0 };
	std::vector<Polygon*> allPolygons;

private:
	

	// Floor
	Triangle floorTrig1{ {-3, 0, -5}, {0, -6, -5},  {0, 6, -5}, {"Lambertian", white} };
	Triangle floorTrig2{ {10, 6, -5}, {10, -6, -5}, {13, 0, -5},  {"Lambertian", white} };
	Rectangle floorRectangle{ {0, -6, -5}, {10, -6, -5}, {10, 6, -5}, {0, 6, -5}, {"Lambertian", white} };

	// Ceiling
	Triangle ceilTrig1{ {0, -6, 5}, {-3, 0, 5}, {0, 6, 5}, {"Lambertian", white} };
	Triangle ceilTrig2{ {13, 0, 5}, {10, -6, 5}, {10, 6, 5}, {"Lambertian", white} };
	Rectangle ceilRectangle{ {0, -6, 5.0f},  {0, 6, 5.0f}, {10, 6, 5.0f}, {10, -6, 5.0f}, {"Lambertian", white} };

	// Walls
	Rectangle wall1{ {10, -6, -5}, {0, -6, -5}, {0, -6, 5}, {10, -6, 5}, {"Lambertian", red} };
	Rectangle wall2{ {13, 0, -5}, {10, -6, -5}, {10, -6, 5}, {13, 0, 5}, {"Lambertian", green} };
	Rectangle wall3{ {10, 6, -5}, {13, 0, -5}, {13, 0, 5}, {10, 6, 5}, {"Lambertian", blue} };
	Rectangle wall4{ {0, 6, -5}, {10, 6, -5}, {10, 6, 5}, {0, 6, 5}, {"Lambertian", yellow} };
	Rectangle wall5{ {-3, 0, -5}, {0, 6, -5}, {0, 6, 5}, {-3, 0, 5}, {"Lambertian", magenta} };
	Rectangle wall6{ {0, -6, -5}, {-3, 0, -5}, {-3, 0, 5}, {0, -6, 5}, {"Lambertian", cyan} };

	//add lamp
	Rectangle ceilLamp{ {2.0f, -2.0f, 5.0f},  {2, 2, 5.0f}, {6, 2, 5.0f}, {6, -2, 5.0f}, lamp };
};