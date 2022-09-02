#include "../../../include/Overlay/GuiManager.hpp"

namespace ovl {

void GuiManager::popup_clear_system() {
    if (m_state->show_gui["popup_clear"]) {
        ImGui::OpenPopup("Clear System?");
        m_state->show_gui["popup_clear"] = false;
    }

    if (ImGui::ValidationPopup("Clear System?",
                               "Do you really want to erase all the objects in the scene ?\n"
                               "\nIncluding:\n"
                               "     * Corpses\n"
                               "     * Constraints\n"
                               "     * Spawners...\n"
                               "\nThis operation cannot be undone !")) {
        clear_system();
    }
}

void GuiManager::clear_system() {
    /* Make sure that the arrays are empty */
    /*
    m_selected_corpses_cursor = {};
    m_selected_corpses_index = {};
    m_selected_corpses_fixed = {};
    m_selected_corpses_diff = {};
    m_spawners = {};
    */
    // m_state->system.clear();
}
}