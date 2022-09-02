#include "../../../include/Overlay/GuiManager.hpp"

namespace ovl {

void GuiManager::show_gui_selection(bool *p_open) {
    if (ImGui::Begin("Selection", p_open)) {
        for (int i = 0; i < m_state->corpses_selected.size(); i++) {

            int id = m_state->corpses_selected[i];

            if (ImGui::CollapsingHeader(("Selected corpse [ id = " + com::to_string(id) + " ]").c_str(), ImGuiTreeNodeFlags_None)) {

                auto corpse = m_state->system.get_corpse_by_id(id);

                editor_corpse(corpse.get());

                ImGui::Dummy(ImVec2(0.0f, 7.0f));
                ImGui::Separator();
                ImGui::Dummy(ImVec2(0.0f, 7.0f));

                for (int j = 0; j < corpse->get_shapes_size(); j++) {
                    auto shape = corpse->get_shape(j);

                    if (ImGui::TreeNode(("Shape " + com::to_string(j)).c_str())) {

                        ImGui::Dummy(ImVec2(0.0f, 7.0f));

                        editor_shape(shape.get());

                        ImGui::Dummy(ImVec2(0.0f, 7.0f));

                        if (phy::Circle *circle = dynamic_cast<phy::Circle *>(shape.get())) { editor_circle(circle); }

                        ImGui::TreePop();
                    }
                }
            }
        }

        ImGui::End();
    }
}

}  // namespace ovl