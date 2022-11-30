#pragma once
#include "Tetrahedron.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Cube.h"

class Scene {
public:
	// Constructor which adds objects to the scene
	Scene() {

		std::cout << "Setting up the scene..." << std::endl;

		// Add the lights
		addLight(&ceilLamp);
		addLight(&wallLamp);

		// Adds the polygons for the floor
		addPolygon(&floorTrig1);
		addPolygon(&floorTrig2);
		addPolygon(&floorRectangle);

		// Adds the polygons for the ceiling
		addPolygon(&ceilTrig1);
		addPolygon(&ceilTrig2);
		addPolygon(&ceilRectangle);

		// Adds the polygons for the walls
		addPolygon(&wall1);
		addPolygon(&wall2);
		addPolygon(&wall3);
		addPolygon(&wall4);
		addPolygon(&wall5);
		addPolygon(&wall6);

		// Adds the objects
		addObject(&sphere1);
		addObject(&sphere2);
		addObject(&sphere3);
		addObject(&tetrahedron1);
		//addObject(&cube1);

	}


	// Functions for adding surfaces to the vectors
	void addPolygon(Surface* P) { polygons.push_back(P); }
	void addLight(Surface* P) { lights.push_back(P); }
	void addObject(Surface* P) { objects.push_back(P); }
	
	// Definition of some colors
	const Color red{ 0.8, 0.1, 0.1 };
	const Color green{ 0.1, 0.8, 0.1 };
	const Color blue{ 0.1, 0.1, 0.8 };
	const Color gray{ 0.2, 0.2, 0.2 };
	const Color yellow{ 0.8, 0.8, 0.1 };
	const Color magenta{ 0.8, 0.1, 0.8 };
	const Color cyan{ 0.1, 0.8, 0.8 };

	const Color white{ 1.0, 1.0, 1.0 };
	const Color almostWhite{ 0.9, 0.9, 0.9 };

	const Color custom{ 0.55, 0.8, 0.4 };



	// Definition of some materials
	const Material mirror{ "Mirror", white, 1.0, 1.0 };
	const Material lowReflectiveMirror{ "Mirror", white, 0.4, 1.0 };

	const Material glass{ "Glass", white, 1.0, 1.5 };
	const Material highRefractionGlass{ "Glass", white, 1.0, 1.8 };
	const Material lowReflectiveGlass{ "Glass", white, 0.4, 1.5 };

	const Material lamp{ "Lamp", white, 1.0};



	// Declaration of vectors for surfaces in the scene
	std::vector<Surface*> polygons;
	std::vector<Surface*> objects;
	std::vector<Surface*> lights;

private:
	
	// Room vertecies
	Vertex p1{ -3.0, 0.0, -5.0 };
	Vertex p2{ 0.0, -6.0, -5.0 };
	Vertex p3{ 10.0, -6.0, -5.0 };
	Vertex p4{ 13.0, 0.0, -5.0 };
	Vertex p5{ 10.0, 6.0, -5.0 };
	Vertex p6{ 0.0, 6.0, -5.0 };
	Vertex p7{ -3.0, 0.0, 5.0 };
	Vertex p8{ 0.0, -6.0, 5.0 };
	Vertex p9{ 10.0, -6.0, 5.0 };
	Vertex p10{ 13.0, 0.0, 5.0 };
	Vertex p11{ 10.0, 6.0, 5.0 };
	Vertex p12{ 0.0, 6.0, 5.0 };

	// Tetrahedron vertecies
	Vertex t1{ 7.0, -4.0, -3.5 };
	Vertex t2{ 5.0, -2.0, -3.5 };
	Vertex t3{ 7.0, 0.0, -3.5 };
	Vertex t4{ 6.0, -2.0, -1.0 };

	// Cube vertecies
	Vertex r1{ 5.0, -3.0, -5.0 };
	Vertex r2{ 7.0, -1.0, -5.0 };
	Vertex r3{ 9.0, -3.0, -5.0 };
	Vertex r4{ 7.0, -5.0, -5.0 };
	Vertex r5{ 5.0, -3.0, -2.5 };
	Vertex r6{ 7.0, -1.0, -2.5 };
	Vertex r7{ 9.0, -3.0, -2.5 };
	Vertex r8{ 7.0, -5.0, -2.5 };

	// Floor
	Triangle floorTrig1{ p1, p2, p6, {"Lambertian", almostWhite} };
	Triangle floorTrig2{ p3, p4, p5,  {"Lambertian", almostWhite} };
	Rectangle floorRectangle{ p2, p3, p5, p6, {"Lambertian", almostWhite} };

	// Ceiling
	Triangle ceilTrig1{ p7, p12, p8, {"Lambertian", almostWhite} };
	Triangle ceilTrig2{ p10, p9, p11, {"Lambertian", almostWhite} };
	Rectangle ceilRectangle{ p8,  p12, p11, p9, {"Lambertian", almostWhite} };

	// Walls
	Rectangle wall1{ p2, p8, p9, p3, {"Lambertian", red, 0.5} };
	Rectangle wall2{ p3, p9, p10, p4, {"Lambertian", blue, 0.6} };
	Rectangle wall3{ p4, p10, p11, p5, {"Lambertian", green, 0.4} };
	Rectangle wall4{ p5, p11, p12, p6, {"Lambertian", yellow, 0.7} };
	Rectangle wall5{ p6, p12, p7, p1, {"Lambertian", magenta, 0.6} };
	Rectangle wall6{ p1, p7, p8, p2, {"Lambertian", cyan, 0.4} };

	// Lights
	Rectangle ceilLamp{ {4.0, -1.0, 5.0},  {4.0, 1.0, 5.0}, {6.0, 1.0, 5.0}, {6.0, -1.0, 5.0}, lamp };
	Rectangle wallLamp{ {4.0, 6.0, 0.0},  {6.0, 6.0, 0.0}, {6.0, 6.0, 2.0}, {4.0, 6.0, 2.0}, lamp };

	// Spheres
	Sphere sphere1{ 1.2, {9.0, 0.1, -0.5}, glass };
	Sphere sphere2{ 1.1, {5.0, 2.5, -3.0}, {"Lambertian", custom * yellow, 0.7} };
	Sphere sphere3{ 1.3, {7.0, -3.0, 1.0}, {"Lambertian", custom*yellow, 0.7} };

	// Tetrahedrons
	Tetrahedron tetrahedron1{ std::vector<Vertex>{t1,t2,t3,t4}, {"Lambertian", custom*blue, 0.6} };

	// Cubes
	Cube cube1{ std::vector<Vertex>{r1,r2,r3,r4,r5,r6,r7,r8}, {"Lambertian", custom*cyan, 0.7} };
};