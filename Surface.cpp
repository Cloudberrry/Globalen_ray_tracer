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

Direction Surface::calculateReflectedRayDirection(Direction inDirection, Direction norm) const {
    return glm::normalize(inDirection - 2.0 * glm::dot(inDirection, norm) * norm);
}

Direction Surface::calculateRefractedRayDirection(Direction inDirection, Direction norm, double R) const {
    return glm::normalize(R * inDirection + norm * (-1.0 * R * glm::dot(norm, inDirection) - sqrt(1.0 - pow(R, 2) * (1.0 - pow(glm::dot(norm, inDirection), 2)))));
}

Surface::Surface(const std::vector<Vertex>& P, const Material m)
    : points{ P }, material{ m }
{

}