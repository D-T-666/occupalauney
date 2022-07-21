#include "occupalauney.h"

using std::vector;

int main() {
    Application occupalauney;

    if (occupalauney.setup(600, 600)) occupalauney.start();
}