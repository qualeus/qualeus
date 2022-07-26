
#include "../../include/Renderer/Renderer.hpp"

void BaseDemo() {
    Renderer base = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Base Demo", false, 0.0f, 1.0f, 2000.0f, 2000.0f, 10, 10);

    for (int i = 0; i < 100; ++i) { base.addCorpse(phy::Circle(rand() % 500 + 250, rand() % 500, rand() % 20 + 20, 1.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false), C_SUN); }

    base.addCorpse(phy::Polygon({{850, -350}, {950, -350}, {950, 750}, {-50, 750}, {-50, -350}, {50, -350}, {50, 650}, {850, 650}}, 5, 1, 0.0f, 0.0f, 0.0f, 0.0f, true, true, false), C_EMERALD);

    // base.system.addCorpse(phy::Polygon({{750, 750}, {950, 750}, {950, -350}, {750, -350}}, 5, 1, 0.0f, 0.0f, 0.0f, 0.0f, true, true, false, C_NEPHRITIS));
    // base.system.addCorpse(phy::Polygon({{-150, 750}, {50, 750}, {50, -350}, {-150, -350}}, 5, 1, 0.0f, 0.0f, 0.0f, 0.0f, true, true, false, C_NEPHRITIS));
    // base.system.addCorpse(phy::Polygon({{-150, 950}, {950, 950}, {950, 750}, {-150, 750}}, 5, 1, 0.0f, 0.0f, 0.0f, 0.0f, true, true, false, C_NEPHRITIS));

    base.addCorpse(phy::Polygon({{600, 50}, {720, 90}, {820, -150}, {590, -10}}, 5, 1, 0.0f, 0.0f, 0.0f, -1.0f, true, true, false), C_AMETHYST);
    base.addCorpse(phy::Polygon({{0, 0}, {0, 200}, {200, 200}, {200, 0}}, 5, 1, 0.0f, 0.0f, 0.0f, 5.0f, true, true, false), C_CARROT);
    // test.system.addCorpse(phy::Polygon({{0, 0},{200, 200},{0, 200},{200, 0}}, 5, 1, 0.0f, 0.0f, 0.0f, 5.0f, true, true, false, C_CARROT));

    // test.Pause();
    base.Render();
}

void GravityDemo() {
    Renderer gravity = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Gravity", true, 0.0f, 0.0f, 10000.0f, 10000.0f, 10, 10);
    gravity.addCorpse(phy::Circle(0.0f, 0.0f, 100.0f, 1e+6, 2, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false), sf::Color::Red);
    gravity.addCorpse(phy::Circle(500.0f, 0.0f, 20.0f, 5e+1, 2, 0.0f, -5.2f, 0.0f, 0.0f, false, false, false), sf::Color::Blue);
    // gravity.system.addCorpse(phy::Circle(800.0f, 0.0f, 20.0f, 5e+1, 2, 0.0f, -3.2f, 0.0f, 0.0f, false, false, false, sf::Color::Cyan));

    gravity.Render();
}