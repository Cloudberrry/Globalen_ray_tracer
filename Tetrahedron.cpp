#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(const std::vector<Vertex> V, Material m)
	: Surface{ V, m }
{
	// Create triangles from the vertecies and add to the triangles vector
	Triangle t1{ V[0], V[1], V[2], material };
	Triangle t2{ V[0], V[3], V[1], material };
	Triangle t3{ V[1], V[3], V[2], material };
	Triangle t4{ V[2], V[3], V[0], material };
	triangles.push_back(t1);
	triangles.push_back(t2);
	triangles.push_back(t3);
	triangles.push_back(t4);
}

bool Tetrahedron::intersection(const Direction inDirection, const Vertex start, Vertex& refIntersection) {

	// Use triangle intersection algorithm for all triangles belonging to the tetrahedron
	for (int i = 0; i < triangles.size(); ++i) {
		if (glm::dot(triangles[i].getNormal(), inDirection) < 0 && triangles[i].intersection(inDirection, start, refIntersection)) {
			normal = triangles[i].getNormal();
			return true;
		}
	}
	return false;
}
