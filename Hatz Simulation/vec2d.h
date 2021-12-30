#pragma once

struct vec2d
{
    float x, y;
};

vec2d Vector_Add(const vec2d& v1, const vec2d& v2);
vec2d Vector_Subtract(const vec2d& v1, const vec2d& v2);
vec2d Vector_SubtractModulus(const vec2d& v1, const vec2d& v2);
vec2d Vector_Multiply(const vec2d& v1, const vec2d& v2);
vec2d Vector_Divide(const vec2d& v1, const vec2d& v2);
vec2d Vector_Normalise(const vec2d& v1, const vec2d& v2);
float Vector_CrossProduct(const vec2d& v1, const vec2d& v2);
float Vector_DotProduct(const vec2d& v1, const vec2d& v2);

vec2d ToVector_Add(const vec2d& v, const float& f);
vec2d ToVector_Subtract(const vec2d& v, const float& f);
vec2d ToVector_Multiply(const vec2d& v, const float& f);
vec2d ToVector_Divide(const vec2d& v, const float& f);