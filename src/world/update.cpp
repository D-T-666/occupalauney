#include <iostream>
#include <vector>

#include "occupalauney.h"

void World::update(int frameCount) {
    cursor = lerp(
        cursor, 
        getCursorTarget(),
        0.7f);
}