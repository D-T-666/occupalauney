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

    createVert(verts,             s / 2 - 1,             s / 2 - 1); // A - 0
    createVert(verts, w / s * s - s / 2 + 1,             s / 2 - 1); // B - 1
    createVert(verts, w / s * s - s / 2 + 1, h / s * s - s / 2 + 1); // C - 2
    createVert(verts,             s / 2 - 1, h / s * s - s / 2 + 1); // D - 3

    insertNewTri(verts, tris, 0, 1, 2, 0);
    insertNewTri(verts, tris, 0, 2, 3, 0);

    for (int i = 0; i < w / s + 1; i++) {
        vector<int> col;

        for (int j = 0; j < h / s + 1 ; j++) {
            col.push_back(0);

            if (i % (w / s - 1) != 0 || j % (h / s - 1) != 0)
            if (i + 2 * ((j) % 2) < w / s && j < h / s)
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
}

int World::getTriangleWithPoint(const Vector2 & p) {
    for (int i = 0; i < tris.size(); i++) {
        if (PointInTriangle(p, verts[tris[i].a], verts[tris[i].b], verts[tris[i].c]))
            return i;
    }

    return -1;
}

void World::moveMade() {
    Vector2 target = getCursorTarget();
    createVert(verts, target);

    triangulate(verts.size() - 1, turn);

    turn = 2 - (turn - 1);
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