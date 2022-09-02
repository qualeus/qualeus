#include "../../../include/Overlay/GuiManager.hpp"

namespace ovl {

void GuiManager::draw_gui_menu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                std::string path =
                    srl::FileManager::SelectFile("Open System", srl::FileManager::CurrentPath(), "System (.json, .latio)\0*.json;*.latio\0System (.json)\0*.json\0System (.latio)\0*.latio\0", false);
                if (path != "") { *m_state = srl::FileManager::LoadState(path); }
            }

            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                std::string path =
                    srl::FileManager::SelectFile("Save System", srl::FileManager::CurrentPath(), "System (.json, .latio)\0*.json;*.latio\0System (.json)\0*.json\0System (.latio)\0*.latio\0", true);

                if (path != "") { srl::FileManager::SaveState(*m_state, path); }
            }

            if (ImGui::MenuItem("Clear", "Ctrl+R")) { m_state->show_gui["popup_clear"] = true; }

            ImGui::Dummy(ImVec2(0.0f, 7.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            if (ImGui::MenuItem("Settings")) { m_state->show_gui["settings"] = true; }

            ImGui::Dummy(ImVec2(0.0f, 7.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            if (ImGui::MenuItem("Exit")) {
                // Close();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Do stuff */
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* Do stuff */
            }

            ImGui::Dummy(ImVec2(0.0f, 7.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            if (ImGui::MenuItem("Cut", "Ctrl+X")) { /* Do stuff */
            }
            if (ImGui::MenuItem("Copy", "Ctrl+C")) { /* Do stuff */
            }
            if (ImGui::MenuItem("Paste", "Ctrl+V")) { /* Do stuff */
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools")) {
            if (ImGui::BeginMenu("Layout")) {
                if (ImGui::MenuItem("Reset Base Layout")) { m_state->reset_base_layout = true; }
                ImGui::EndMenu();
            }

            ImGui::Dummy(ImVec2(0.0f, 7.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
            ImGui::MenuItem("Selection", NULL, &m_state->show_gui["selection"]);
            ImGui::MenuItem("Spawners", NULL, &m_state->show_gui["spawners"]);
            ImGui::MenuItem("State", NULL, &m_state->show_gui["state"]);
            ImGui::MenuItem("Console", NULL, &m_state->show_gui["console"]);

            ImGui::Separator();

            ImGui::MenuItem("ImGui Demo", NULL, &m_state->show_gui["imguidemo"]);
            ImGui::PopItemFlag();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug")) {
            ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
            ImGui::MenuItem("Contacts", NULL, &m_state->show_debug["contacts"]);
            ImGui::PopItemFlag();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Shaders")) {
            ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
            ImGui::MenuItem("Grid", NULL, &m_state->post_process["grid"]);
            ImGui::PopItemFlag();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("Documentation")) { /* Do stuff */
            }
            if (ImGui::MenuItem("About")) { /* Do stuff */
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
}  // namespace ovl