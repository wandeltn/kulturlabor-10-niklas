#include <Vector2.hpp>

Vector2 operator+(const Vector2& a, const Vector2& b)
{
    return Vector2{
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

Vector2 operator*(const double k, const Vector2& v)
{
    return Vector2{
        .x = k * v.x,
        .y = k * v.y};
}