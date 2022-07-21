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

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            vert_grid[i][j] = 0;
        }
    }
    vert_grid[0][0] = 1;
    vert_grid[8][0] = 1;
    vert_grid[8][8] = 1;
    vert_grid[0][8] = 1;
    vert_grid[3][3] = 1;
    vert_grid[5][5] = 1;

    createVert(verts, 0, 0);         // A - 0
    createVert(verts, w, 0);         // B - 1
    createVert(verts, w, h);         // C - 2
    createVert(verts, 0, h);         // D - 3
    createVert(verts, w / 2, h / 2); // E - 4

    insertNewTri(verts, tris, 0, 1, 4, 0); // ABE
    insertNewTri(verts, tris, 0, 4, 3, 0); // AED
    insertNewTri(verts, tris, 2, 3, 4, 1); // CDF
    insertNewTri(verts, tris, 2, 4, 1, 1); // CFB
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

    triangulate(verts.size() - 1);

    // for (int i = tris.size() - 1; i >= 0; i--) {
        // Tri t = tris[i];

        // if (pointInCircumcircle(target, verts[t.a], verts[t.b], verts[t.c])) {
            // eraseTri(verts, tris, i);
        // }
    // }

    turn = 1 - turn;
}

void World::triangulate(int i) {
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
                     vertinds[(j + 1) % vertinds.size()], turn);
    }
}

Vector2 World::getCursorTarget() {
    const int cell_w = int(w / 8 - p / 4);
    const int cell_h = int(h / 8 - p / 4);
    
    return {
        float(int(mouse.x + cell_w / 2) / cell_w * cell_w), 
        float(int(mouse.y + cell_h / 2) / cell_h * cell_h)
    };
}