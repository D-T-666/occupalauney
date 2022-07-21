#include "occupalauney.h"

float randf() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float randf(float max) { return randf() * max; }

float randf(float min, float max) { return randf() * (max - min) + min; }