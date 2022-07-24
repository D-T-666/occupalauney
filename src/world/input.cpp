#include <iostream>

#include "occupalauney.h"

void World::update(int frameCount, Vector2 _mouse) {
    update(frameCount);
    mouse = _mouse;
}

void World::mouseClicked(int mouse_button) {
    if (mouse_button == 0) {
        int mi = -1, mj = -1;
        Vector2 target = getCursorTarget();
        int tri_group = tris[getTriangleWithPoint(target)].group;


        if (target.x >= 0 && target.x <= w &&
            target.y >= 0 && target.y <= h &&
            (tri_group == turn || tri_group < 1)) {

            mi = (target.x) / s;
            mj = (target.y) / s;
            std::cout << "[" << mi << "," << mj << "]\n";

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