#include <iostream>

#include "occupalauney.h"

void World::update(int frameCount, Vector2 _mouse) {
    update(frameCount);
    mouse = _mouse;
}

void World::mouseClicked(int mouse_button) {
    // TODO: implement mouse click event
    if (mouse_button == 0) {
        int mi = -1, mj = -1;
        Vector2 target = getCursorTarget();

        if (target.x >= p && target.x <= w - p &&
            target.y >= p && target.y <= h - p &&
            tris[getTriangleWithPoint(target)].group == turn) {

            mi = (target.x - p) / int(w / 8 - p / 4);
            mj = (target.y - p) / int(h / 8 - p / 4);

            if (vert_grid[mi][mj] == 0) {
                vert_grid[mi][mj] = 1;
                moveMade();
            }
        }
    }
}

// TODO: make this function functional
void World::keyGotPressed(char key) {
    pressed_key = key;
}