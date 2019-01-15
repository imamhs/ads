/*
    Shari (A simple 2D matrix library)
    Copyright (C) 2014 Md Imam Hossain
    All rights reserved
*/

#include "def.h"

void dmat2d_translate (Vec2D *shape, unsigned long np, float x, float y)
{
unsigned long vc;
for (vc = 0; vc < np; vc++) {
shape[vc].x = shape[vc].x + x;
shape[vc].y = shape[vc].y + y;
}
}

void dmat2d_rotate (Vec2D *shape, unsigned long np, float a)
{
unsigned long vc;
float ad = a * (PI / 180);
for (vc = 0; vc < np; vc++) {
Vec2D p;
p.x = shape[vc].x;
p.y = shape[vc].y;
shape[vc].x = (cos (ad) * p.x) + (-1 * sin (ad) * p.y);
shape[vc].y = (sin (ad) * p.x) + (cos (ad) * p.y);
}
}

void dmat2d_scale (Vec2D *shape, unsigned long np, float x, float y)
{
unsigned long vc;
for (vc = 0; vc < np; vc++) {
shape[vc].x = x * shape[vc].x;
shape[vc].y = y * shape[vc].y;
}
}

void dmat2d_reflect (Vec2D *shape, unsigned long np, int x, int y)
{
unsigned long vc;
if (x == 1) {
for (vc = 0; vc < np; vc++) shape[vc].y = -1 * shape[vc].y;
}
if (y == 1) {
for (vc = 0; vc < np; vc++) shape[vc].x = -1 * shape[vc].x;
}
}
