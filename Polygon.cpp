#include "Polygon.h"

std::size_t Polygon::count_polygons = 0;

std::size_t Polygon::get_count_polygons()
{
    return Polygon::count_polygons;
}
