#include "../../include/Renderer/Renderer.hpp"



void SpringDemo() {
    Renderer spring = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Spring", false, 0.0f, 0.0f, 100000.0f, 100000.0f, 10, 20);
    int number = 50;
    for (int i = 0; i < number; ++i) { spring.addCorpse(phy::Circle(rand() % (number * 30), rand() % (number * 30), rand() % number + 20, 1.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false), C_SUN); }
    for (int i = 1; i < number; ++i) { spring.addConstraint(phy::Spring(spring.getCorpse(i - 1), spring.getCorpse(i), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, 0.1, 30, 0, -1000, false), C_SUN); }
    spring.Render();
}