#include "vec2d.h"
#include <cmath>

vec2d Vector_Add(const vec2d& v1, const vec2d& v2)
{
    return { v1.x + v2.x, v1.y + v2.y };
}

vec2d Vector_Subtract(const vec2d& v1, const vec2d& v2)
{
    return { v1.x - v2.x, v1.y - v2.y };
}

vec2d Vector_SubtractModulus(const vec2d& v1, const vec2d& v2)
{
    return { fabsf(v1.x - v2.x), fabsf(v1.y - v2.y) };
}

vec2d Vector_Multiply(const vec2d& v1, const vec2d& v2)
{
    return { v1.x * v2.x, v1.y * v2.y };
}

vec2d Vector_Divide(const vec2d& v1, const vec2d& v2)
{
    return { v1.x / v2.x, v1.y / v2.y };
}

vec2d Vector_Normalise(const vec2d& v1, const vec2d& v2)
{
    const vec2d& x = Vector_Subtract(v1, v2);
    const vec2d& y = Vector_SubtractModulus(v1, v2);

    return Vector_Divide(x, y);
}

float Vector_CrossProduct(const vec2d& v1, const vec2d& v2)
{
    return (v1.x * v2.y) - (v1.y * v2.x);
}

float Vector_DotProduct(const vec2d& v1, const vec2d& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

vec2d ToVector_Add(const vec2d& v, const float& f)
{
    return { v.x + f, v.y + f };
}

vec2d ToVector_Subtract(const vec2d& v, const float& f)
{
    return { v.x - f, v.y - f };
}

vec2d ToVector_Multiply(const vec2d& v, const float& f)
{
    return { v.x * f, v.y * f };
}

vec2d ToVector_Divide(const vec2d& v, const float& f)
{
    return { v.x / f, v.y / f };
}