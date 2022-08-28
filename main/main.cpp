
#include <stdlib.h>

#include <Context/Renderer.hpp>

int main(void) {
    ctx::Renderer renderer = ctx::Renderer();

    for (int i = 0; i < 100; ++i) {
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        renderer.add_corpse(phy::Circle(i % 10 + 5, i + 10, r), 0xffffffff);
    }

    renderer.add_corpse(phy::Polygon({{0, 0}, {10, 10}, {2, -3}, {7, -2}}), 0xff1322ff);

    renderer.render();
}