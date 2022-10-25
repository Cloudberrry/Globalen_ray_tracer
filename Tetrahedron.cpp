#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(const Vertex p1, const Vertex p2, const Vertex p3, const Vertex p4, Material m)
	: Surface{ std::vector<Vertex>{ p1, p2, p3, p4 }, m }
{
	Triangle t1{ points[0], points[1], points[2], material };
	Triangle t2{ points[0], points[3], points[1], material };
	Triangle t3{ points[1], points[3], points[2], material };
	Triangle t4{ points[2], points[3], points[0], material };
	triangles.push_back(t1);
	triangles.push_back(t2);
	triangles.push_back(t3);
	triangles.push_back(t4);
	
}

bool Tetrahedron::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {
	//std::cout << "( " << triangles[1].getMaterial().getColor().x << ", " << triangles[1].getMaterial().getColor().y << ", " << triangles[1].getMaterial().getColor().z << " )" << std::endl;

	for (int i = 0; i < triangles.size(); ++i) {
		if (triangles[i].intersection(inDirection, start, refIntersection)) {
			normal = triangles[i].getNormal();
			return true;
		}
	}
	return false;
}