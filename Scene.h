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
	std::vector<Polygon*> allPolygons;

private:
	

	// Floor
	Triangle floorTrig1{ {-3, 0, -5}, {0, -6, -5},  {0, 6, -5}, gray };
	Triangle floorTrig2{ {10, 6, -5}, {10, -6, -5}, {13, 0, -5},  gray };
	Rectangle floorRectangle{ {0, -6, -5}, {10, -6, -5}, {10, 6, -5}, {0, 6, -5}, gray };

	// Ceiling
	Triangle ceilTrig1{ {0, -6, 5}, {-3, 0, 5}, {0, 6, 5}, white };
	Triangle ceilTrig2{ {13, 0, 5}, {10, -6, 5}, {10, 6, 5}, white };
	Rectangle ceilRectangle{ {0, -6, 5},  {0, 6, 5}, {10, 6, 5}, {10, -6, 5}, white };

	// Walls
	Rectangle wall1{ {10, -6, -5}, {0, -6, -5}, {0, -6, 5}, {10, -6, 5}, red };
	Rectangle wall2{ {13, 0, -5}, {10, -6, -5}, {10, -6, 5}, {13, 0, 5}, green };
	Rectangle wall3{ {10, 6, -5}, {13, 0, -5}, {13, 0, 5}, {10, 6, 5}, blue };
	Rectangle wall4{ {0, 6, -5}, {10, 6, -5}, {10, 6, 5}, {0, 6, 5}, yellow };
	Rectangle wall5{ {-3, 0, -5}, {0, 6, -5}, {0, 6, 5}, {-3, 0, 5}, magenta };
	Rectangle wall6{ {0, -6, -5}, {-3, 0, -5}, {-3, 0, 5}, {0, -6, 5}, cyan };
};