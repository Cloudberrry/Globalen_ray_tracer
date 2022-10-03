#pragma once

#include <iostream>
#include <vector>
#include "Triangle.h"
#include "Rectangle.h"

class Scene {
public:
	Scene() {

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
		allPolygons.push_back(&ceilLamp);
	}

	void addPolygon(Polygon* P) { allPolygons.push_back(P); }
	
	// Some colors
	Color red{ 255.0, 0.0, 0.0 };
	Color green{ 0.0, 255.0, 0.0 };
	Color blue{ 0.0, 0.0, 255.0 };
	Color gray{ 50.0, 50.0, 50.0 };
	Color white{ 255.0, 255.0, 255.0 };
	Color yellow{ 255.0, 255.0, 0.0 };
	Color magenta{ 255.0, 0.0, 255.0 };
	Color cyan{ 0.0, 255.0, 255.0 };


	Material mirror{ "Mirror", white, 1.0 };
	Material glass{ "Glass", white, 1.0, 1.5 };
	Material lamp{ "Lamp", white, 0.0, 1.0 };
	std::vector<Polygon*> allPolygons;

private:
	

	// Floor
	Triangle floorTrig1{ {-3, 0, -5}, {0, -6, -5},  {0, 6, -5}, {"Lambertian", gray, 0.5} };
	Triangle floorTrig2{ {10, 6, -5}, {10, -6, -5}, {13, 0, -5},  {"Lambertian", gray, 0.5} };
	Rectangle floorRectangle{ {0, -6, -5}, {10, -6, -5}, {10, 6, -5}, {0, 6, -5}, {"Lambertian", gray, 0.5} };

	// Ceiling
	Triangle ceilTrig1{ {0, -6, 5}, {-3, 0, 5}, {0, 6, 5}, {"Lambertian", gray, 0.5} };
	Triangle ceilTrig2{ {13, 0, 5}, {10, -6, 5}, {10, 6, 5}, {"Lambertian", gray, 0.5} };
	Rectangle ceilRectangle{ {0, -6, 5},  {0, 6, 5}, {10, 6, 5}, {10, -6, 5}, {"Lambertian", gray, 0.5} };

	// Walls
	Rectangle wall1{ {10, -6, -5}, {0, -6, -5}, {0, -6, 5}, {10, -6, 5}, {"Lambertian", red, 0.5} };
	Rectangle wall2{ {13, 0, -5}, {10, -6, -5}, {10, -6, 5}, {13, 0, 5}, mirror };
	Rectangle wall3{ {10, 6, -5}, {13, 0, -5}, {13, 0, 5}, {10, 6, 5}, {"Lambertian", blue, 0.5} };
	Rectangle wall4{ {0, 6, -5}, {10, 6, -5}, {10, 6, 5}, {0, 6, 5}, {"Lambertian", yellow, 0.5} };
	Rectangle wall5{ {-3, 0, -5}, {0, 6, -5}, {0, 6, 5}, {-3, 0, 5}, {"Lambertian", magenta, 0.5} };
	Rectangle wall6{ {0, -6, -5}, {-3, 0, -5}, {-3, 0, 5}, {0, -6, 5}, {"Lambertian", cyan, 0.5} };

	//add lamp
	Rectangle ceilLamp{ {0, -2, 4.99},  {0, 2, 4.99}, {4, 2, 4.99}, {4, -2, 4.99}, lamp };
};