/*
    Bostu (a simple dynamic object containing a number of boundary points)
    Copyright (C) 2014-2025 Md Imam Hossain (emamhd@gmail.com)
    All rights reserved.
*/

#include "def.h"

#include <cstddef>

int Bostu::create (unsigned long s)
{
    int ret = 1;
    if (PointsN == 0) {
        Points = new Vec2D[s];
        if (Points != NULL) PointsN = s;
        else ret = 0;
    }
    else ret = 0;
    return ret;
}

Bostu::Bostu ()
{
    Points = NULL;
    PointsN = 0;
    Velocity.x = 0.0;
    Velocity.y = 0.0;
    Center.x = 0.0;
    Center.y = 0.0;
    Mass = 0.0;
    Area = 0.0;
}

Bostu::~Bostu ()
{
    if (Points != NULL) delete[] Points;
}
