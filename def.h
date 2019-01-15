/*
    Copyright (C) 2014 Md Imam Hossain
    All rights reserved
*/

#ifndef _DEF_H_
#define _DEF_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

#define PI 3.141592

struct Vector2D {
float x, y;
};

struct Vector3D {
float x, y, z;
};

typedef struct Vector2D Vec2D;

typedef struct Vector3D Vec3D;

// a simple dynamic object containing a number of boundary points
class Bostu {
public:
Vec2D *Points;
Vec2D Velocity;
Vec2D Size;
float Mass;
unsigned long PointsN;
Bostu ();
~Bostu ();
int create (unsigned long s);
};

// returns a vector by adding the vectors v1 and v2
Vec2D dvec2d_add (Vec2D v1, Vec2D v2);

// returns a vector by substracting the vector v2 from v1
Vec2D dvec2d_sub (Vec2D v1, Vec2D v2);

// returns the magnitude of the vector v
float dvec2d_mag (Vec2D v);

// returns a unit vector of the vector v
Vec2D dvec2d_unit (Vec2D v);

// returns the dot product of the vectors v1 and v2
float dvec2d_dot (Vec2D v1, Vec2D v2);

// returns a vector by projecting vector v1 onto v2
Vec2D dvec2d_proj (Vec2D v1, Vec2D v2);

// returns the magnitude of vector projection of v1 onto v2
float dvec2d_projm (Vec2D v1, Vec2D v2);

// returns a vector scalar multiplication of vector v
Vec2D dvec2d_mult (Vec2D v, float factor);

// returns the angle in degrees between v1 and v2
float dvec2d_angle (Vec2D v1, Vec2D v2);

// returns the normal vector from v1 and v2
Vec2D dvec2d_normal (Vec2D v1, Vec2D v2, int side);

// returns the negative vector of v
Vec2D dvec2d_neg (Vec2D v);

// translate shape vectors array by x and y where np is the number of points in shape
void dmat2d_translate (Vec2D *shape, unsigned long np, float x, float y);

// rotate shape vectors array by a degrees where np is the number of points in shape
void dmat2d_rotate (Vec2D *shape, unsigned long np, float a);

// scale shape vectors array by x and y where np is the number of points in shape
void dmat2d_scale (Vec2D *shape, unsigned long np, float x, float y);

// invert shape vectors array about x and y where np is the number of points in shape
void dmat2d_reflect (Vec2D *shape, unsigned long np, int x, int y);

// returns a 3D vector by adding vector v1 and v2
Vec3D dvec3d_add (Vec3D v1, Vec3D v2);

// returns a 3D vector by substracting vector v2 from v1
Vec3D dvec3d_sub (Vec3D v1, Vec3D v2);

// returns the magnitude of 3D vector v
float dvec3d_mag (Vec3D v);

// returns a 3D vector scalar multiplication of v
Vec3D dvec3d_mult (Vec3D v, float factor);

// returns the dot product of 3D vectors v1 and v2
float dvec3d_dot (Vec3D v1, Vec3D v2);

// returns the angle in degrees between 3D vectors v1 and v2
float dvec3d_angle (Vec3D v1, Vec3D v2);

// returns a unit vector of 3D vector v
Vec3D dvec3d_unit (Vec3D v);

// returns the maximum from numbers array
float dfind_max (float *numbers, unsigned long s);

// returns the minimum from numbers array
float dfind_min (float *numbers, unsigned long s);

// returns collision results from two polygons
int acheck_polycollision (Vec2D *s1, unsigned long np1, Vec2D *s2, unsigned long np2);

// returns collision results from two rectangles
int acheck_boxcollision (float b1_left, float b1_right, float b1_top, float b1_bottom, float b2_left, float b2_right, float b2_top, float b2_bottom);

// copies Vector array from src to dest
void acopy_shape (Vec2D *src, Vec2D *dest, unsigned long s);

#endif
