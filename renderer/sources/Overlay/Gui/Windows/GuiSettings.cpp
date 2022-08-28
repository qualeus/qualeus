#include "../../../../include/Overlay/Gui/GuiManager.hpp"

namespace ovl {

void GuiManager::show_gui_settings(bool* p_open) {
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

    static int selected_menu = 0;

    if (ImGui::Begin("Settings", p_open)) {
        ImGui::BeginChild("###SettingsMenu", ImVec2(150, 0), true);

        ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth;
        ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_None;

        ImGui::SetNextTreeNodeOpen(true, ImGuiCond_FirstUseEver);
        if (ImGui::TreeNode("WorkBench")) {
            ImGui::SetNextTreeNodeOpen(true, ImGuiCond_FirstUseEver);
            if (ImGui::TreeNodeEx("Styles", ImGuiTreeNodeFlags_SpanFullWidth)) {
                node_flags = base_flags;
                if (selected_menu == S_MENU_INTERFACE) node_flags |= ImGuiTreeNodeFlags_Selected;

                ImGui::TreeNodeEx("Interface", node_flags, "Interface", S_MENU_INTERFACE);
                if (ImGui::IsItemClicked()) selected_menu = S_MENU_INTERFACE;

                node_flags = base_flags;
                if (selected_menu == S_MENU_QUALEUS) node_flags |= ImGuiTreeNodeFlags_Selected;

                ImGui::TreeNodeEx("Qualeus", node_flags, "Qualeus", S_MENU_QUALEUS);
                if (ImGui::IsItemClicked()) selected_menu = S_MENU_QUALEUS;

                node_flags = base_flags;
                if (selected_menu == S_MENU_CONSOLE) node_flags |= ImGuiTreeNodeFlags_Selected;

                ImGui::TreeNodeEx("Console", node_flags, "Console", S_MENU_CONSOLE);
                if (ImGui::IsItemClicked()) selected_menu = S_MENU_CONSOLE;

                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("SettingsPage", ImVec2(0, 0), true);

    switch (selected_menu) {
        case S_MENU_INTERFACE: {
            ImGui::Text("Interface Style");

            ImGui::Dummy(ImVec2(0.0f, 7.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            if (ImGui::Combo("Theme", reinterpret_cast<int*>(&m_state->theme), "Classic\0Dark\0Violet\0Light\0")) { update_theme(); }

            ImGui::Dummy(ImVec2(0.0f, 7.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 7.0f));

            ImGui::ShowStyleEditor();
        } break;
        case S_MENU_QUALEUS: {
            INPUT_SLIDER_FLOAT_ACCESSORS(m_state->camera., fov, "FOV", 0.f, 180.f)
            INPUT_SLIDER_FLOAT_ACCESSORS(m_state->camera., near, "NEAR", 0.f, 300.f)
            INPUT_SLIDER_FLOAT_ACCESSORS(m_state->camera., far, "FAR", 0.f, 300.f)

            INPUT_SLIDER_VEC3_ACCESSORS(m_state->camera., position, "POS", 0.f, 300.f)
            INPUT_SLIDER_VEC3_ACCESSORS(m_state->camera., towards, "TOW", 0.f, 300.f)
        } break;
        case S_MENU_CONSOLE: {
            ImGui::ShowStyleSelector("style");
        } break;

        default: {
        } break;
    }

    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();
}

}  // namespace ovl