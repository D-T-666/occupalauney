#include <math.h>
#include <raylib.h>

#include <algorithm>
#include <iostream>

#include "occupalauney.h"

bool PointInTriangle(Vector2 pt, Vector2 v1, Vector2 v2, Vector2 v3) {
    return CheckCollisionPointTriangle(pt, v1, v2, v3);
}

bool pointInCircumcircle(Vector2 pt, Vector2 p1, Vector2 p2, Vector2 p3) {
    Vector2 p[3] = {p1, p2, p3};

    Vector2 pt1 = p1 - pt;
    Vector2 pt2 = p2 - pt;

    Vector2 p31 = p1 - p3;
    Vector2 p32 = p2 - p3;

    Vector2 p21 = p2 - p1;

    Vector2 p2190{-p21.y, p21.x};

    float cp132 = p32 * p31 / (mag(p32) * mag(p31));
    float cp1t2 = pt1 * pt2 / (mag(pt1) * mag(pt2));

    return cp1t2 < cp132 * (((p2190 * pt1 < 0) == (p2190 * p31 < 0)) * 2 - 1);
}

// Gets the area of a triangle
float getTriArea(Vector2 a, Vector2 b, Vector2 c) {
    return fabs((b - a) & (c - a)) / 2.0f;
}

// Gets the degeneracy value of a triangle
float getTriDegeneracy(Vector2 a, Vector2 b, Vector2 c) {
    float e = 0.f;

    e = fmax(e, magSq(a - b));
    e = fmax(e, magSq(c - b));
    e = fmax(e, magSq(a - c));

    return getTriArea(a, b, c) / e;
}