#include "../../../../include/Overlay/Gui/GuiManager.hpp"

namespace ovl {

void GuiManager::ShowGuiSelection(bool* p_open) {
    if (ImGui::Begin("Selection", p_open)) {
        if (this->state->corpses_selected.size() > 0) {
            int id = this->state->corpses_selected[0];
            auto corpse = this->state->system.get_corpse_by_id(id);
            ImGui::Text("Selected body id: %i", corpse->get_id());

            ImGui::Dummy(ImVec2(0.0f, 7.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            // INPUT_SLIDER_FLOAT2_ACCESSORS(corpse->, pos_x, pos_y, "position", -1000000.0f, 1000000.0f)
            // INPUT_SLIDER_FLOAT2_ACCESSORS(corpse->, last_pos_x, last_pos_y, "last pos", -1000000.0f, 1000000.0f)
        }
        ImGui::End();
    }
}

}  // namespace ovl