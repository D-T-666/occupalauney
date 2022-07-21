#include "occupalauney.h"

bool triHasVert(Tri tri, int vert) {
    return tri.a == vert || tri.b == vert || tri.c == vert;
}

float getTriAreaFromVerts(const vector<Vert> &verts, const Tri &tri) {
    return getTriArea(verts[tri.a], verts[tri.b], verts[tri.c]);
}

float triDegeneracyWithVerts(const vector<Vert> &verts, const Tri &tri) {
    return getTriDegeneracy(verts[tri.a], verts[tri.b], verts[tri.c]);
}

void eraseTri(vector<Vert> &verts, vector<Tri> &tris, int i) {
    for (int v = 0; v < verts.size(); v++) {
        for (int t = verts[v].tris.size() - 1; t >= 0; t--) {
            if (verts[v].tris[t] == i) {
                verts[v].tris.erase(verts[v].tris.begin() + t);
            } else if (verts[v].tris[t] > i) {
                verts[v].tris[t]--;
            }
        }
    }

    tris.erase(tris.begin() + i);
}

void insertNewTri(vector<Vert> &verts, vector<Tri> &tris, int a, int b, int c, int group) {
    if (((verts[a] - verts[b]) & (verts[a] - verts[c])) < 0) {
        std::swap(b, c);
    }

    tris.push_back(Tri{a, b, c, group});

    verts[a].tris.push_back(tris.size() - 1);
    verts[b].tris.push_back(tris.size() - 1);
    verts[c].tris.push_back(tris.size() - 1);
}

bool isClockwise(Vector2 a, Vector2 b, Vector2 c) {
    return ((a - b) & (a - c)) > 0;
}