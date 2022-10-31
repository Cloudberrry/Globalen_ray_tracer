#include "Surface.h"

std::vector<Vertex> Surface::getPoints() const {
    return points;
}

Material Surface::getMaterial() const {
    return material;
}

Direction Surface::getNormal() const {
    return normal;
}

Direction Surface::calculateReflectedRayDirection(Direction inDirection) const {
    return glm::normalize(inDirection - 2 * glm::dot(inDirection, normal) * normal);
}

Direction Surface::calculateRefractedRayDirection(Direction inDirection, double R) const {
    return glm::normalize(R * inDirection + normal * (-R * glm::dot(normal, inDirection) - sqrt(1 - pow(R, 2) * (1 - pow(glm::dot(normal, inDirection), 2)))));
}

Surface::Surface(const std::vector<Vertex>& P, const Material m)
    : points{ P }, material{ m }
{

}