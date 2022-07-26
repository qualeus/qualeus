#include "../../include/Renderer/Renderer.hpp"

void ClothDemo() {
    Renderer cloth = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Cloth", false, 0.0f, 2.0f, 100000.0f, 100000.0f, 10, 20);
    int width = 1000;
    int height = 10;
    float spacing_w = 50;
    float spacing_h = 50;
    float pos_x = -500;
    float pos_y = -500;
    float rigidity = 1;
    bool breaking = true;
    float limit_breaking = -100;
    bool etherial = true;
    int point_size = 30;

    auto cloth_color = [&](int i, int j) {
        std::vector<int> interpolated = gmt::interpolate_array({C_ALIZARIN.r, C_ALIZARIN.g, C_ALIZARIN.b}, {C_AMETHYST.r, C_AMETHYST.g, C_AMETHYST.b}, static_cast<float>(i) / static_cast<float>(height));
        return sf::Color(interpolated[0], interpolated[1], interpolated[2]);
        // return sf::Color(25 * i, 25 * j, 10);
        return C_SUN;
    };

    for (int i = 0; i < width; i++) { cloth.addCorpse(phy::Circle(pos_x + i * spacing_w, pos_y + 0, point_size, 1, 1, 0, 0, 0, 0, true, true, etherial), C_ALIZARIN); }
    for (int i = 1; i < height; i++) {
        for (int j = 0; j < width; j++) { cloth.addCorpse(phy::Circle(pos_x + j * spacing_w, pos_y + i * spacing_h, point_size, 1, 1, 0, 0, 0, 0, false, false, etherial), cloth_color(i, j)); }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width - 1; j++) { cloth.addConstraint(phy::Link(cloth.getCorpse(j + i * width), cloth.getCorpse(j + i * width + 1), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity, limit_breaking, limit_breaking, breaking), cloth_color(i, j)); }
    }

    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width; j++) { cloth.addConstraint(phy::Link(cloth.getCorpse(j + i * width), cloth.getCorpse(j + (i + 1) * width), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, rigidity, limit_breaking, limit_breaking, breaking), cloth_color(i, j)); }
    }

    cloth.Render();
}