/*
    Akriti (Collision detection routines for 2D shapes)
    Copyright (C) 2014 Md Imam Hossain
    All rights reserved
*/

#include "def.h"

float dfind_max (float *numbers, unsigned long s)
{
float m = numbers[0];
unsigned long i;
for (i = 1; i < s; i++) if (m < numbers[i]) m = numbers[i];
return m;
}

float dfind_min (float *numbers, unsigned long s)
{
float m = numbers[0];
unsigned long i;
for (i = 1; i < s; i++) if (m > numbers[i]) m = numbers[i];
return m;
}

int acheck_polycollision (Vec2D *s1, unsigned long np1, Vec2D *s2, unsigned long np2)
{
unsigned long vc;
int col = 1;
for (vc = 0; vc < np1; vc++) {
Vec2D norm;
float mi1, mx1, mi2, mx2;
unsigned long c;
float *sm1 = (float *) malloc (sizeof(float) * np1);
float *sm2 = (float *) malloc (sizeof(float) * np2);
if ((sm1 == NULL) || (sm2 == NULL)) {
col = -1;
break;
}
if (vc == (np1 - 1)) {
norm.x = -1 * (s1[0].y - s1[vc].y);
norm.y = s1[0].x - s1[vc].x;
}
else {
norm.x = -1 * (s1[vc+1].y - s1[vc].y);
norm.y = s1[vc+1].x - s1[vc].x;
}
for (c = 0; c < np1; c++) sm1[c] = dvec2d_projm (s1[c], norm);
for (c = 0; c < np2; c++) sm2[c] = dvec2d_projm (s2[c], norm);
mi1 = dfind_min (sm1, np1);
mx1 = dfind_max (sm1, np1);
mi2 = dfind_min (sm2, np2);
mx2 = dfind_max (sm2, np2);
if ((mx1 < mi2 || mi1 > mx2)) {
col = 0;
free (sm1);
free (sm2);
break;
}
free (sm1);
free (sm2);
}
if (col == 1) {
for (vc = 0; vc < np2; vc++) {
Vec2D norm;
float mi1, mx1, mi2, mx2;
unsigned long c;
float *sm1 = (float *) malloc (sizeof(float) * np1);
float *sm2 = (float *) malloc (sizeof(float) * np2);
if ((sm1 == NULL) || (sm2 == NULL)) {
col = -1;
break;
}
if (vc == (np2 - 1)) {
norm.x = -1 * (s2[0].y - s2[vc].y);
norm.y = s2[0].x - s2[vc].x;
}
else {
norm.x = -1 * (s2[vc+1].y - s2[vc].y);
norm.y = s2[vc+1].x - s2[vc].x;
}
for (c = 0; c < np1; c++) sm1[c] = dvec2d_projm (s1[c], norm);
for (c = 0; c < np2; c++) sm2[c] = dvec2d_projm (s2[c], norm);
mi1 = dfind_min (sm1, np1);
mx1 = dfind_max (sm1, np1);
mi2 = dfind_min (sm2, np2);
mx2 = dfind_max (sm2, np2);
if ((mx1 < mi2 || mi1 > mx2)) {
col = 0;
free (sm1);
free (sm2);
break;
}
free (sm1);
free (sm2);
}
}
return col;
}

int acheck_boxcollision (float b1_left, float b1_right, float b1_top, float b1_bottom, float b2_left, float b2_right, float b2_top, float b2_bottom)
{
return (((b1_right > b2_left) && (b1_left < b2_right)) && ((b1_bottom > b2_top) && (b1_top < b2_bottom)));
}

void acopy_shape (Vec2D *src, Vec2D *dest, unsigned long s)
{
unsigned long vc;
for (vc = 0; vc < s; vc++) {
dest[vc].x = src[vc].x;
dest[vc].y = src[vc].y;
}
}
