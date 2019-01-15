/*
    Dic (A simple 2D and 3D vectors library)
    Copyright (C) 2014 Md Imam Hossain
    All rights reserved
*/

#include "def.h"

Vec2D dvec2d_add (Vec2D v1, Vec2D v2)
{
Vec2D temp;
temp.x = v1.x + v2.x;
temp.y = v1.y + v2.y;
return temp;
}

Vec2D dvec2d_sub (Vec2D v1, Vec2D v2)
{
Vec2D temp;
temp.x = v1.x - v2.x;
temp.y = v1.y - v2.y;
return temp;
}

float dvec2d_mag (Vec2D v)
{
Vec2D temp;
temp.x = v.x * v.x;
temp.y = v.y * v.y;
return (float) sqrt (temp.x + temp.y);
}

Vec2D dvec2d_unit (Vec2D v)
{
Vec2D temp;
float m = dvec2d_mag (v);
temp.x = v.x / m;
temp.y = v.y / m;
return temp;
}

float dvec2d_dot (Vec2D v1, Vec2D v2)
{
Vec2D temp;
temp.x = v1.x * v2.x;
temp.y = v1.y * v2.y;
return temp.x + temp.y;
}

Vec2D dvec2d_proj (Vec2D v1, Vec2D v2)
{
Vec2D temp;
float f = dvec2d_dot (v1, v2) / dvec2d_dot (v2, v2);
temp.x = f * v2.x;
temp.y = f * v2.y;
return temp;
}

float dvec2d_projm (Vec2D v1, Vec2D v2)
{
float m = dvec2d_mag (v2);
return dvec2d_dot (v1, v2) / m;
}

Vec2D dvec2d_normal (Vec2D v1, Vec2D v2, int side)
{
Vec2D temp;
if (side == 1) {
temp.x = -1 * (v2.y - v1.y);
temp.y = v2.x - v1.x;
}
else {
temp.x = v2.y - v1.y;
temp.y = -1 * (v2.x - v1.x);
}
return temp;
}

Vec2D dvec2d_mult (Vec2D v, float factor)
{
Vec2D temp;
temp.x = v.x * factor;
temp.y = v.y * factor;
return temp;
}

float dvec2d_angle (Vec2D v1, Vec2D v2)
{
float d = dvec2d_dot (v1, v2);
float a = d / (dvec2d_mag (v1) * dvec2d_mag (v2));
return acos (a) * (180 / PI);
}

Vec2D dvec2d_neg (Vec2D v)
{
Vec2D temp;
temp.x = -1 * v.x;
temp.y = -1 * v.y;
return temp;
}

Vec3D dvec3d_add (Vec3D v1, Vec3D v2)
{
Vec3D temp;
temp.x = v1.x + v2.x;
temp.y = v1.y + v2.y;
temp.z = v1.z + v2.z;
return temp;
}

Vec3D dvec3d_sub (Vec3D v1, Vec3D v2)
{
Vec3D temp;
temp.x = v1.x - v2.x;
temp.y = v1.y - v2.y;
temp.z = v1.z - v2.z;
return temp;
}

float dvec3d_mag (Vec3D v)
{
Vec3D temp;
temp.x = v.x * v.x;
temp.y = v.y * v.y;
temp.z = v.z * v.z;
return (float) sqrt (temp.x + temp.y + temp.z);
}

Vec3D dvec3d_mult (Vec3D v, float factor)
{
Vec3D temp;
temp.x = v.x * factor;
temp.y = v.y * factor;
temp.z = v.z * factor;
return temp;
}

float dvec3d_dot (Vec3D v1, Vec3D v2)
{
Vec3D temp;
temp.x = v1.x * v2.x;
temp.y = v1.y * v2.y;
temp.z = v1.z * v2.z;
return temp.x + temp.y + temp.z;
}

float dvec3d_angle (Vec3D v1, Vec3D v2)
{
float d = dvec3d_dot (v1, v2);
float a = d / (dvec3d_mag (v1) * dvec3d_mag (v2));
return acos (a) * (180 / PI);
}

Vec3D dvec3d_unit (Vec3D v)
{
Vec3D temp;
float m = dvec3d_mag (v);
temp.x = v.x / m;
temp.y = v.y / m;
temp.z = v.z / m;
return temp;
}
