#include "Color.h"

Color Color::operator+(Color c)
{
    Color result = { color.x + c.color.x, color.y + c.color.y, color.z + c.color.z };

    return result;
}

Color Color::operator-(Color c)
{
    // Vad gör vi när färgvärden är mindre än 0?
    Color result = { color.x - c.color.x, color.y - c.color.y, color.z - c.color.z };

    return result;
}

Color Color::operator*(Color c)
{
    Color result = { color.x * c.color.x, color.y * c.color.y, color.z * c.color.z};

    return result;
}
