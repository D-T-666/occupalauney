#include "occupalauney.h"

using std::vector;

int main() {
    Application occupalauney;

    if (occupalauney.setup(570, 570)) occupalauney.start();
}