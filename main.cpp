#include <iostream>
#include "Ray.h"
#include "Rectangle.h"
#include "Triangle.h"

//testkommentar /Amanda <3

int main() {
	Color red{255.0, 0.0, 0.0};
	Color green{ 0.0, 255.0, 0.0 };
	Color blue{ 0.0, 0.0, 255.0 };
	Color gray{ 50.0, 50.0, 50.0 };
	Color white{ 255.0, 255.0, 255.0 };
	Color yellow{ 255.0, 255.0, 0.0 };
	Color magenta{ 255.0, 0.0, 255.0 };
	Color cyan{ 0.0, 255.0, 255.0 };

	Triangle floorTrig1{ {-3, 0, -5}, {0, -6, -5}, {0, 6, -5}, gray };
	Triangle floorTrig2{ {10, -6, -5}, {13, 0, -5}, {10, 6, -5}, gray };
	Rectangle floorRectangle{ {0, -6, -5}, {10, -6, -5}, {10, 6, -5}, {0, 6, -5}, gray };

	Triangle floorTrig1{ {0, -6, 5}, {-3, 0, 5}, {0, 6, 5}, white };
	Triangle floorTrig2{ {13, 0, 5}, {10, -6, 5}, {10, 6, 5}, white };
	Rectangle floorRectangle{ {0, -6, 5},  {0, 6, 5}, {10, 6, 5}, {10, -6, 5}, white };

	Rectangle wall1{ {10, -6, -5}, {0, -6, -5}, {0, -6, 5}, {10, -6, 5}, red };
	Rectangle wall2{ {13, 0, -5}, {10, -6, -5}, {10, -6, 5}, {13, 0, 5}, green };
	Rectangle wall3{ {10, 6, -5}, {13, 0, -5}, {13, 0, 5}, {10, 6, 5}, blue };
	Rectangle wall4{ {0, 6, -5}, {10, 6, -5}, {10, 6, 5}, {0, 6, 5}, yellow };
	Rectangle wall5{ {-3, 0, -5}, {0, 6, -5}, {0, 6, 5}, {-3, 0, 5}, magenta };
	Rectangle wall6{ {0, -6, -5}, {-3, 0, -5}, {-3, 0, 5}, {0, -6, 5}, cyan };

	std::vector<Polygon*> scene;
	scene.push_back(&wall1);
	
	return 0;
}