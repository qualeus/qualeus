#include "../../../include/Overlay/GuiManager.hpp"

namespace ovl {

void GuiManager::show_gui_spawner(bool *p_open) {
    if (ImGui::Begin("Spawner", p_open)) {

        if (ImGui::BeginTabBar("SpawnerTabBar", ImGuiTabBarFlags_None)) {
            if (ImGui::BeginTabItem("New spawner")) {
                show_tab_new_spawner();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("List spawners")) {
                show_tab_list_spawners();
                ImGui::EndTabItem();
            }
        }

        ImGui::End();
    }
}

void GuiManager::show_tab_new_spawner() {

    auto corpse = &m_state->spawners_model.model;

    editor_corpse(corpse);

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

        ImGui::SameLine();

        if (ImGui::Button("Remove")) { corpse->remove_shape(j); }
    }

    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    if (ImGui::Button("Add circle shape")) { corpse->add_shape(std::make_shared<phy::Circle>(phy::Circle({0.f, 0.f}, 1.f, 0.f, 1.f, 1.f))); }

    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    ImGui::Checkbox("Repeat", &m_state->spawners_model.repeat);
    ImGui::InputDouble("Delay", &m_state->spawners_model.delay, 0.01f, 10000.0f, "%.3f");

    ImGui::Dummy(ImVec2(0.0f, 7.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 7.0f));

    if (ImGui::Button("Create Spawner", {-1, 25})) { m_state->spawners.push_back(m_state->spawners_model); }
}

void GuiManager::show_tab_list_spawners() {
    for (int i = 0; i < m_state->spawners.size(); i++) {
        ImGui::Text("Spawner [ id = %i ]", i);

        ImGui::SameLine();

        if (ImGui::Button("Remove")) { com::remove(i, m_state->spawners); }
    }
}

}  // namespace ovl