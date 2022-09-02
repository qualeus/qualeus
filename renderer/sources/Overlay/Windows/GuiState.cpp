#include "../../../include/Overlay/GuiManager.hpp"

namespace ovl {

void GuiManager::show_gui_state(bool *p_open) {
    if (ImGui::Begin("State", p_open)) {

        static ImGuiTextBuffer json_state;

        if (ImGui::Button("Refresh JSON state", {-1, 25}) || json_state.empty()) {
            json_state.clear();

            std::stringstream ss;
            cereal::JSONOutputArchive oarchive = cereal::JSONOutputArchive(ss);
            oarchive(cereal::make_nvp<ctx::State>("state", *m_state));

            int line = 1;
            std::string temp_line;
            while (std::getline(ss, temp_line)) {
                std::string line_pagination = com::to_string(line++) + "     ";
                json_state.appendf("%s| %s\n", line_pagination.substr(0, 5).c_str(), temp_line.c_str());
            }
        }

        ImGui::Dummy(ImVec2(0.0f, 7.0f));

        ImGui::TextUnformatted(json_state.begin(), json_state.end());

        ImGui::End();
    }
}

}  // namespace ovl