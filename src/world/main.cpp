#include <assert.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "occupalauney.h"

using std::vector;

void World::create(int width, int height, int size) {
    w = width;
    h = height;
    s = size;

    int c = w / s;
    int r = h / s;

    // Create the shell
    createVert(verts,         s / 2 - 10,         s / 2 - 10); // A - 0
    createVert(verts, c * s - s / 2 + 10,         s / 2 - 10); // B - 1
    createVert(verts, c * s - s / 2 + 10, r * s - s / 2 + 10); // C - 2
    createVert(verts,         s / 2 - 10, r * s - s / 2 + 10); // D - 3
    insertNewTri(verts, tris, 0, 1, 2, 0);
    insertNewTri(verts, tris, 0, 2, 3, 0);

    // The corners [optional]
    createVert(verts,         s / 2,         s / 2); // A - 0
    createVert(verts, c * s - s / 2,         s / 2); // B - 1
    createVert(verts, c * s - s / 2, r * s - s / 2); // C - 2
    createVert(verts,         s / 2, r * s - s / 2); // D - 3
    for (int i = 4; i < 8; i++)
        triangulate(i, 0);

    for (int i = 0; i < c + 1; i++) {
        vector<int> col;

        for (int j = 0; j < r + 1 ; j++) {
            col.push_back((i % c) * (j % r) == 0);

            if (i % (c - 1) != 0 || j % (r - 1) != 0)
            if (i + 2 * ((j) % 2) < c && j < r)
            if (i % 4 == 0 && j % 3 == 0) {
                createVert(
                    verts, 
                    Vector2{
                        float((i + 2 * ((j) % 2)) * s + s / 2), 
                        float(j * s + s / 2)
                    }
                );
                triangulate(verts.size() - 1, 0);
            }
        }

        vert_grid.push_back(col);
    }

    // Remove the shell
    for (int i = 0; i < 4; i++)
        eraseVert(verts, tris, 0);
}

int World::getTriangleWithPoint(const Vector2 & p) {
    Vector2 a, b, c;
    for (int i = tris.size() - 1; i >= 0; i--) {
        a = verts[tris[i].a];
        b = verts[tris[i].b];
        c = verts[tris[i].c];
        paddTriangleInPlace(a, b, c, -1);

        if (PointInTriangle(p, a, b, c))
            return i;
    }

    return -1;
}

void World::moveMade() {
    Vector2 target = getCursorTarget();
    createVert(verts, target);

    triangulate(verts.size() - 1, turn);

    turn = turn % 6 + 1;
}

void World::triangulate(int i, int new_tri_group) {
    std::vector<int> vertinds;

    auto insvert = [&](int ind) {
        for (int v : vertinds) {
            if (ind == v || v == i) return;
        }

        vertinds.push_back(ind);
    };

    for (int j = tris.size() - 1; j >= 0; j--) {
        Tri tri = tris[j];

        if (pointInCircumcircle(verts[i], verts[tri.a], verts[tri.b],
                                verts[tri.c])) {
            insvert(tri.a);
            insvert(tri.b);
            insvert(tri.c);

            eraseTri(verts, tris, j);
        }
    }

    std::sort(vertinds.begin(), vertinds.end(), [=](int a, int b) {
        return atan2f((verts[a] - verts[i]).x, (verts[a] - verts[i]).y) <
               atan2f((verts[b] - verts[i]).x, (verts[b] - verts[i]).y);
    });

    for (int j = 0; j < vertinds.size(); j++) {
        insertNewTri(verts, tris, i, vertinds[j],
                     vertinds[(j + 1) % vertinds.size()], new_tri_group);
    }
}

Vector2 World::getCursorTarget() {
    return {
        float(int(mouse.x) / s * s + s / 2), 
        float(int(mouse.y) / s * s + s / 2)
    };
}