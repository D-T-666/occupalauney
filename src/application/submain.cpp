#include <iostream>
#include "occupalauney.h"

void Application::setup() {
    wld.create(width, height, 30);
    HideCursor();
}

void Application::update() {
    wld.keyGotPressed(tolower(GetKeyPressed()));

    wld.update(frameCount, GetMousePosition());

    for (int i = 0; i < 3; i++) if (IsMouseButtonPressed(i))
        wld.mouseClicked(i);
}

void Application::draw() {
    ClearBackground({28, 26, 33, 255});

    // Draw snap points
    for (int i = wld.s / 2; i <= width; i += wld.s) {
        for (int j = wld.s / 2; j <= height; j += wld.s) {
            DrawCircle(i, j, 2, {255, 255, 255, 40});
        }
    }

    Color colors[7] = {
        GetColor(0x00779911),
        GetColor(0xe50000aa),
        GetColor(0xff8d00aa),
        GetColor(0xffee00aa),
        GetColor(0x028121aa),
        GetColor(0x004cffaa),
        GetColor(0x760088aa)
    };

    int turn = wld.turn;
    int hovering_triangle = wld.getTriangleWithPoint(wld.cursor);

    // Draw triangles
    for (int i = 0; i < wld.tris.size(); i++) {
        Tri t = wld.tris[i];
        int fp = 2; // Fill padding
        DrawTriangleFillPadded(wld.verts[t.a], wld.verts[t.c], wld.verts[t.b], fp, colors[t.group]);
        // if (t.group == 0)
            DrawTriangleLinesPadded(wld.verts[t.a], wld.verts[t.b], wld.verts[t.c], 0, WHITE);
        if (t.group != 0)
        // else
            DrawTriangleLinesPadded(wld.verts[t.a], wld.verts[t.b], wld.verts[t.c], 0, colors[t.group]);
        if (hovering_triangle == i) {
            if (t.group == turn)
                DrawTriangleLinesPadded(wld.verts[t.a], wld.verts[t.b], wld.verts[t.c], 4, WHITE);
            else
                DrawTriangleLinesPadded(wld.verts[t.a], wld.verts[t.b], wld.verts[t.c], 4, {28, 26, 33, 255});
        }
    }

    // Draw existing vertices
    for (Vector2 vert : wld.verts) {
        DrawCircle(vert.x, vert.y, 6, {28, 26, 33, 255});
        DrawCircle(vert.x, vert.y, 4, WHITE);
    }

    // Draw cursor
    int t_group = wld.tris[hovering_triangle].group;
    if (hovering_triangle >= 0 && (t_group == turn || wld.tris[hovering_triangle].group == 0)) {
        DrawCircle(wld.cursor.x, wld.cursor.y, 8, WHITE);
        DrawCircle(wld.cursor.x, wld.cursor.y, 8, colors[turn]);
        DrawCircle(wld.cursor.x, wld.cursor.y, 7, {28, 26, 33, 255});
        DrawCircle(wld.cursor.x, wld.cursor.y, 4, WHITE);
    } else {
        DrawCircle(wld.cursor.x, wld.cursor.y, 8, WHITE);
        DrawCircle(wld.cursor.x, wld.cursor.y, 8, colors[turn]);
        DrawCircle(wld.cursor.x, wld.cursor.y, 7, {28, 26, 33, 255});
    }
}

void Application::close() {
    // UnloadTexture(trexture);
}
