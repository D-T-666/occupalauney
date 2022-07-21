#include "occupalauney.h"

void createVert(vector<Vert> &verts, float x, float y) {
    verts.push_back(Vert(x, y));
}

void createVert(vector<Vert> &verts, Vector2 v) { createVert(verts, v.x, v.y); }

void eraseVert(vector<Vert> &verts, vector<Tri> &tris, int vert) {
    for (int i = tris.size() - 1; i >= 0; i--) {
        for (int x = 0; x < 3; x++) tris[i][x] -= tris[i][x] > vert;
    }

    for (int i = verts[vert].tris.size() - 1; i >= 0; i--) {
        eraseTri(verts, tris, verts[vert].tris[i]);
    }

    verts.erase(verts.begin() + vert);
}