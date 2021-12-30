#include "plane.h"
#include <cmath>

float Line_DistanceTo(const line& l, const vec2d& p) 
{
    const vec2d& A = l.point[0];
    const vec2d& B = l.point[1];

    const vec2d& a = Vector_Subtract(p, A);
    const vec2d& b = Vector_Subtract(A, B);
    const vec2d& c = Vector_Subtract(B, A);

    return Vector_CrossProduct(a, b) / sqrtf(Vector_DotProduct(c, c));
}