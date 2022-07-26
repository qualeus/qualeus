

#include "../../include/Renderer/Renderer.hpp"

void SpongeDemo() {
    Renderer sponge = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Solf", false, 0.0f, 0.0f, 100000.0f, 100000.0f, 10, 20);
    int width = 10;
    int height = 10;
    int pos_x = 0;
    int pos_y = 0;
    float spacing = 100;
    int point_size = 45;
    float rigidity = 0.6f;
    bool breaking = true;
    float limit_breaking = -600;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) { sponge.addCorpse(phy::Circle(pos_x + j * spacing, pos_y + i * spacing, point_size, 1, 1, 0, 0, 0, 0, false, false, false), C_SUN); }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width - 1; j++) { sponge.addConstraint(phy::Link(sponge.getCorpse(j + i * width), sponge.getCorpse(j + i * width + 1), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity, limit_breaking, limit_breaking, breaking), C_SUN); }
    }

    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width; j++) { sponge.addConstraint(phy::Link(sponge.getCorpse(j + i * width), sponge.getCorpse(j + (i + 1) * width), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity, limit_breaking, limit_breaking, breaking), C_SUN); }
    }
    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width - 1; j++) {
            sponge.addConstraint(phy::Link(sponge.getCorpse(j + i * width), sponge.getCorpse(j + 1 + (i + 1) * width), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity, limit_breaking, limit_breaking, breaking), C_SUN);
            sponge.addConstraint(phy::Link(sponge.getCorpse(j + 1 + i * width), sponge.getCorpse(j + (i + 1) * width), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity, limit_breaking, limit_breaking, breaking), C_SUN);
        }
    }
    sponge.Render();
}
