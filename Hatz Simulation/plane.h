#pragma once
#include "vec2d.h"

struct line
{
    vec2d point[2];
};

struct plane
{
    line line[4];
};

//Returns the distance from a point to a line
float Line_DistanceTo(line& l, vec2d& p);