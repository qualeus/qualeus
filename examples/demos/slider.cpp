#include "../../include/Renderer/Renderer.hpp"

void SliderDemo() {
    Renderer spring = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Spring", false, 0.0f, 0.0f, 100000.0f, 100000.0f, 10, 20);
    int number = 20;
    spring.addCorpse(phy::Circle(rand() % (number * 30), rand() % (number * 30), rand() % number + 20, 1.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, true, false, false), C_SUN);
    spring.addCorpse(phy::Circle(rand() % (number * 30), rand() % (number * 30), rand() % number + 20, 1.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, true, false, false), C_SUN);
    for (int i = 2; i < number; ++i) { spring.addCorpse(phy::Circle(rand() % (number * 30), rand() % (number * 30), rand() % number + 20, 1.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false), C_ASPHALT); }
    phy::Slider slider = phy::Slider(spring.getCorpse(0), spring.getCorpse(1), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, 1, 0, {}, {}, {}, {}, {}, false);
    for (int i = 2; i < number; i++) { slider.addCorpse(spring.getCorpse(i), {0, 0}, true, 0, 0); }
    spring.addConstraint(slider, C_SUN);
}