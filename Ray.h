#pragma once
#include <iostream>
#include "Triangle.h"
#include "Rectangle.h"

class Ray {
public:
	Ray(glm::vec3 p0, glm::vec3 p1, Ray* nextRay = nullptr, Ray* prevRay = nullptr, Color c = 0) : start{ p0 }, end{ p1 }, next{ nextRay }, previous{ prevRay }, color{ c } {
		direction = glm::normalize(p1 - p0);
	}


	~Ray() {
		/*
		Ray* temp = next->previous;
		next->previous = previous;
		previous->next = next;
		delete temp;
		*/
	}

private:
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 direction;
	//Polygon* surface; // Surface on which the starting vertex is located
	Color color;
	Ray* next;
	Ray* previous;
};