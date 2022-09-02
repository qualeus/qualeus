#include "../../../include/Overlay/GuiManager.hpp"

namespace ovl {

void GuiManager::editor_corpse(phy::Corpse* corpse) {
    ImGui::Text("corpse id: %i", corpse->get_id());

    ImGui::Dummy(ImVec2(0.0f, 7.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    INPUT_VECTOR2_ACCESSORS(corpse->, pos, 0.1f, -FLT_MAX, FLT_MAX, "pos")  // corpse position
    INPUT_VECTOR2_ACCESSORS(corpse->, vel, 0.1f, -FLT_MAX, FLT_MAX, "vel")  // corpse velocity
    INPUT_VECTOR2_ACCESSORS(corpse->, acc, 0.1f, -FLT_MAX, FLT_MAX, "acc")  // corpse acceleration

    ImGui::Dummy(ImVec2(0.0f, 7.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    INPUT_FLOAT_ACCESSORS(corpse->, rot, "rot")  // corpse rotation
    INPUT_FLOAT_ACCESSORS(corpse->, spi, "spi")  // corpse angular velocity
    INPUT_FLOAT_ACCESSORS(corpse->, tor, "tor")  // corpse torque

    ImGui::Dummy(ImVec2(0.0f, 7.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    INPUT_BOOL_ACCESSORS(corpse->, fixed, "fixed")        //
    INPUT_BOOL_ACCESSORS(corpse->, tied, "tied")          //
    INPUT_BOOL_ACCESSORS(corpse->, etherial, "etherial")  //

    ImGui::Dummy(ImVec2(0.0f, 7.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    ImGui::Text("mass: %.01f", (float)corpse->get_mass());
    ImGui::Text("moment: %.01f", (float)corpse->get_moment());
}

void GuiManager::editor_shape(phy::Shape* shape) {
    INPUT_FLOAT_ACCESSORS(shape->, mass, "mass")          // mass
    INPUT_FLOAT_ACCESSORS(shape->, friction, "friction")  // friction
    INPUT_FLOAT_ACCESSORS(shape->, damping, "damping")    // damping

    ImGui::Dummy(ImVec2(0.0f, 7.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    ImGui::Text("moment: %.01f", (float)shape->get_moment());

    // ImGui::Text("centroid: [ %.1f ; %.1f ]", (float)shape->get_centroid().x, (float)shape->get_centroid().y);

    INPUT_VECTOR2_ACCESSORS(shape->, centroid, 0.1f, -FLT_MAX, FLT_MAX, "centroid")  // corpse position
}

void GuiManager::editor_circle(phy::Circle* circle) {
    INPUT_FLOAT_ACCESSORS(circle->, radius, "radius")  // corpse rotation
}

}  // namespace ovl