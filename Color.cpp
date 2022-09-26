#include "Color.h"

Color Color::operator+(Color c)
{
    Color result = { color.x + c.color.x, color.y + c.color.y, color.z + c.color.z };

    return result;
}

Color Color::operator-(Color c)
{
    // Vad g�r vi n�r f�rgv�rden �r mindre �n 0?
    Color result = { color.x - c.color.x, color.y - c.color.y, color.z - c.color.z };

    return result;
}

Color Color::operator*(Color c)
{
    Color result = { color.x * c.color.x, color.y * c.color.y, color.z * c.color.z};

    return result;
}
