#include "occupalauney.h"

bool Application::setup(int _width, int _height) {
    width = _width;
    height = _height;

    InitWindow(width, height, "occupalauney");
    SetWindowPosition(0, 0);

    SetTargetFPS(100);

    setup();

    return true;
}

void Application::start() {
    while (!WindowShouldClose()) {
        frameCount++;

        update();

        BeginDrawing();
        /**/ draw();
        EndDrawing();
    }

    close();
}