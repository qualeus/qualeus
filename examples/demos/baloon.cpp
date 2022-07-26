
#include "../../include/Renderer/Renderer.hpp"

void BaloonDemo() {
    Renderer balloon = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Balloon", false, 0.0f, 0.0f, 100000.0f, 100000.0f, 10, 20);
    int number = 10;
    int radius = 400;
    bool breaking = true;
    float rigidity_outside = 1.0f;
    float rigidity_inside = 0.3f;
    float limit_breaking_outside = -1000.0f;
    float limit_breaking_inside = -300.0f;

    for (int i = 0; i < number; i++) {
        float angle = static_cast<float>(i) * 2.0f * PI / static_cast<float>(number);
        balloon.addCorpse(phy::Circle(std::cos(angle) * radius, std::sin(angle) * radius, 20, 1.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false), C_RED);
    }

    for (int i = 0; i < number; i++) { balloon.addConstraint(phy::Link(balloon.getCorpse(i), balloon.getCorpse((i + 1) % number), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity_outside, limit_breaking_outside, limit_breaking_outside, breaking), C_RED); }

    std::vector<std::pair<int, int>> inside = gmt::non_touching_pairs(gmt::create_vector(0, number, [](int i) { return i++; }));

    for (int i = 0; i < inside.size(); i++) {
        balloon.addConstraint(phy::Link(balloon.getCorpse(inside[i].first), balloon.getCorpse(inside[i].second), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity_inside, limit_breaking_inside, limit_breaking_inside, breaking), sf::Color(255, 255, 255, 10));
    }

    balloon.Render();
}