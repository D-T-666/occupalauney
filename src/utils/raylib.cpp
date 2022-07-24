#include <math.h>
#include <raylib.h>

#include "occupalauney.h"

bool operator==(const Color &a, const Color &b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

std::ostream &operator<<(std::ostream &os, const Color &c) {
    // os << "#" << std::hex << (int(c.r) << 16) + (int(c.g) << 8) + (int(c.b)); 
    os << "RGB(" << int(c.r) << ", " << int(c.g) << ", " << int(c.b) << ")";
    return os;
}


void paddTriangleInPlace(Vector2 &p1, Vector2 &p2, Vector2 &p3, int padding) {
    Vector2 p12 = p2 - p1;
    Vector2 p23 = p3 - p2;
    Vector2 p31 = p1 - p3;
    Vector2 p21 = p1 - p2;
    Vector2 p32 = p2 - p3;
    Vector2 p13 = p3 - p1;

    float lpSq12 = magSq(p12);
    float lpSq23 = magSq(p23);
    float lpSq31 = magSq(p31);

    float l1 = (float)padding /
               sqrt(1.0f - (p12 * p13) * (p12 * p13) / (lpSq12 * lpSq31));
    float l2 = (float)padding /
               sqrt(1.0f - (p21 * p23) * (p21 * p23) / (lpSq12 * lpSq23));
    float l3 = (float)padding /
               sqrt(1.0f - (p31 * p32) * (p31 * p32) / (lpSq23 * lpSq31));

    p1 = p1 + (normalized(p12) * l1) + (normalized(p13) * l1);
    p2 = p2 + (normalized(p21) * l2) + (normalized(p23) * l2);
    p3 = p3 + (normalized(p31) * l3) + (normalized(p32) * l3);
}

void DrawTriangleFillPadded(Vector2 p1, Vector2 p2, Vector2 p3, int d,
                            Color color) {
    if (getTriDegeneracy(p1, p2, p3) < 0.01f) return;

    paddTriangleInPlace(p1, p2, p3, d);

    DrawTriangle(p1, p2, p3, color);
}

void DrawTriangleLinesPadded(Vector2 p1, Vector2 p2, Vector2 p3, int d,
                             int weight, Color color) {
    if (getTriDegeneracy(p1, p2, p3) < 0.01f) return;

    paddTriangleInPlace(p1, p2, p3, d);

    DrawLineEx(p1, p2, weight, color);
    DrawLineEx(p2, p3, weight, color);
    DrawLineEx(p3, p1, weight, color);
}

void DrawTriangleLinesPadded(Vector2 p1, Vector2 p2, Vector2 p3, int d,
                             Color color) {
    DrawTriangleLinesPadded(p1, p2, p3, d, 1, color);
}

void DrawTriangleFromTexture(const Texture2D &texture, Vector2 *pos, Vector2 *tc) {
    // float x1 = fmin(pos[0].x, fmin(pos[1].x, pos[2].x)),
    //     x2 = fmax(pos[0].x, fmax(pos[1].x, pos[2].x)),
    //     y1 = fmin(pos[0].y, fmin(pos[1].y, pos[2].y)),
    //     y2 = fmax(pos[0].y, fmax(pos[1].y, pos[2].y));
    // Vector2 c = {(x1 + x2) / 2.0f, (y1 + y2) / 2.0f};
    Vector2 c = (pos[0] + pos[1] + pos[2] + pos[2]) / 4.0f;

    Vector2 points[4] = {
        pos[0] - c,
        pos[1] - c,
        pos[2] - c,
        pos[0] - c,
    };

    Vector2 tex_coords[4] = {
        tc[0],
        tc[1],
        tc[2],
        tc[0],
    };

    DrawTexturePoly(texture, c, points, tex_coords, 4, WHITE);
}

void DrawTriangleFromTexturePadded(const Texture2D &texture, Vector2 *pos,
                                   Vector2 *texcoords, int padding) {
    if (getTriDegeneracy(pos[0], pos[1], pos[2]) < 0.05f) return;

    paddTriangleInPlace(pos[0], pos[1], pos[2], padding);

    Vector2 npos[3] = {pos[0], pos[1], pos[2]};

    DrawTriangleFromTexture(texture, npos, texcoords);
}