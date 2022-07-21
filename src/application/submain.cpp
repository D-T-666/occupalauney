#include <iostream>
#include "occupalauney.h"

void Application::setup() {
    wld.create(width, height);
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
    for (int i = wld.p % int(wld.w / 8 - wld.p / 4); i <= width; i += int(wld.w / 8 - wld.p / 4)) {
        for (int j = wld.p % int(wld.h / 8 - wld.p / 4); j <= height; j += int(wld.h / 8 - wld.p / 4)) {
            DrawCircle(i, j, 2, {255, 255, 255, 40});
        }
    }

    Color colors[2] = {
        {255, 218, 54, 80}, 
        {98, 255, 54, 80}
    };

    int turn = wld.turn;
    int hovering_triangle = wld.getTriangleWithPoint(wld.cursor);

    // Draw triangles
    for (int i = 0; i < wld.tris.size(); i++) {
        Tri t = wld.tris[i];
        int fp = 6; // Fill padding
        if (hovering_triangle == i)
            fp = (t.group == turn) ? 4 : 8;
        DrawTriangleFillPadded(wld.verts[t.a], wld.verts[t.c], wld.verts[t.b], fp, colors[t.group]);
        DrawTriangleLinesPadded(wld.verts[t.a], wld.verts[t.b], wld.verts[t.c], 0, WHITE);
    }

    // Draw existing vertices
    for (Vector2 vert : wld.verts) {
        DrawCircle(vert.x, vert.y, 6, {28, 26, 33, 255});
        DrawCircle(vert.x, vert.y, 4, WHITE);
    }

    // Draw cursor
    if (hovering_triangle >= 0 &&wld.tris[hovering_triangle].group == turn) {
        DrawCircle(wld.cursor.x, wld.cursor.y, 8, WHITE);
        DrawCircle(wld.cursor.x, wld.cursor.y, 7, {28, 26, 33, 255});
        DrawCircle(wld.cursor.x, wld.cursor.y, 4, WHITE);
    } else {
        DrawCircle(wld.cursor.x, wld.cursor.y, 8, WHITE);
        DrawCircle(wld.cursor.x, wld.cursor.y, 7, {28, 26, 33, 255});
    }
}

void Application::close() {
    // UnloadTexture(trexture);
}
