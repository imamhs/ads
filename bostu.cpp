/*
    Bostu (a simple dynamic object containing a number of boundary points)
    Copyright (C) 2014 Md Imam Hossain
    All rights reserved
*/

#include "def.h"

int Bostu::create (unsigned long s)
{
int ret = 1;
if (PointsN == 0) {
Points = (Vec2D *) malloc (sizeof (Vec2D) * s);
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
Velocity.x = 0;
Velocity.y = 0;
Mass = 0;
Size.x = 0;
Size.y = 0;
}

Bostu::~Bostu ()
{
if (Points != NULL) free (Points);
}
