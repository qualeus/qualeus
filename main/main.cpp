
#include <stdlib.h>

#include <Context/Renderer.hpp>
#include <System/System.hpp>

int main(void) {
    ctx::Renderer renderer = ctx::Renderer();

    phy::System system = phy::System();

    /*
    for (int i = 0; i < 100; ++i) {
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        renderer.add_corpse(phy::Circle(i % 10 + 5, i + 10, r), 0xffffffff);
    }
    */

    renderer.render();
}