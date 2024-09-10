#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <cmath>

class Vector2
{
public:
    float x = 0, y = 0;

    Vector2() = default;
    ~Vector2() = default;

    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    void operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
    }
    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
    void operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
    }
    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }
    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }
    void operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
    }

    float length() const
    {
        return std::sqrt(x * x + y * y);
    }
    Vector2 normalized()
    {
        float len = length();
        if (len != 0)
        {
            return *this * (1.0f / len);
        }
        return Vector2(0, 0);
    }

};

#endif // VECTOR2_H