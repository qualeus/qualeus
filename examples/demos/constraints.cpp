#include "../../include/Renderer/Renderer.hpp"

void ConstraintDemo() {
    Renderer constraint = Renderer(0.0f, 0.0f, 900.0f, 1600.0f, 1.0f, "Constraint", false, 0.0f, 0.0f, 100000.0f, 100000.0f, 10, 20);
    int number = 10;
    for (int i = 0; i < number; ++i) { constraint.addCorpse(phy::Circle(rand() % (number * 50), rand() % (number * 50), rand() % 20 + 20, 1.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false), C_SUN); }
    constraint.addConstraint(phy::Link(constraint.getCorpse(0), constraint.getCorpse(1), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, 0.01, 0, -1000, false), C_SUN);
    constraint.addConstraint(phy::Link(constraint.getCorpse(0), constraint.getCorpse(2), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, 1, 0, -1000, false), C_SUN);
    constraint.addConstraint(phy::Link(constraint.getCorpse(1), constraint.getCorpse(2), {0, 0}, {0, 0}, 0, 0, true, true, 0, 0, -1, 1, 0, -1000, false), C_SUN);
    constraint.Render();
}