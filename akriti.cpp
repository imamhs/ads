/*
    Akriti (Collision detection routines for 2D shapes)
    Copyright (C) 2014 Md Imam Hossain (emamhd@gmail.com)
    All rights reserved.
*/

#include "def.h"

#include <cstddef>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cfloat>

float acheck_polycollision (Vec2D *s1, unsigned long np1, Vec2D *s2, unsigned long np2)
{
    unsigned long vc;
    int col = 1;
    float min_pen = FLT_MAX;

    for (vc = 0; vc < np1; vc++) {
        Vec2D norm;
        float pen = 0.0;
        float mi1, mx1, mi2, mx2;
        unsigned long c;
        float *sm1 = new float[np1];
        float *sm2 = new float[np2];
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
        mi1 = *std::min_element (sm1, sm1+np1);
        mx1 = *std::max_element (sm1, sm1+np1);
        mi2 = *std::min_element (sm2, sm2+np2);
        mx2 = *std::max_element (sm2, sm2+np2);
        if ((mx1 < mi2 || mi1 > mx2)) {
            col = 0;
            delete[] sm1;
            delete[] sm2;
            break;
        }
        pen = std::fminf(mx1, mx2) - std::fmaxf(mi1, mi2);
        if (pen < min_pen) min_pen = pen;
        delete[] sm1;
        delete[] sm2;
    }
    if (col == 1) {
        for (vc = 0; vc < np2; vc++) {
            Vec2D norm;
            float pen = 0.0;
            float mi1, mx1, mi2, mx2;
            unsigned long c;
            float *sm1 = new float[np1];
            float *sm2 = new float[np2];
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
            mi1 = *std::min_element (sm1, sm1+np1);
            mx1 = *std::max_element (sm1, sm1+np1);
            mi2 = *std::min_element (sm2, sm2+np2);
            mx2 = *std::max_element (sm2, sm2+np2);
            if ((mx1 < mi2 || mi1 > mx2)) {
                col = 0;
                delete[] sm1;
                delete[] sm2;
                break;
            }
            pen = std::fminf(mx1, mx2) - std::fmaxf(mi1, mi2);
            if (pen < min_pen) min_pen = pen;
            delete[] sm1;
            delete[] sm2;
        }
    }

    if (col) return min_pen;

    return 0.0;
}

int acheck_boxcollision (float b1_left, float b1_right, float b1_top, float b1_bottom, float b2_left, float b2_right, float b2_top, float b2_bottom)
{
    return (((b1_right > b2_left) && (b1_left < b2_right)) && ((b1_bottom > b2_top) && (b1_top < b2_bottom)));
}

void acopy_shape (Vec2D *src, Vec2D *dst, unsigned long s)
{
    std::memcpy((char *)dst, (char *)src, sizeof(Vec2D)*s);
}
