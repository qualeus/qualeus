#include "../../../../include/Overlay/Gui/GuiManager.hpp"

namespace ovl {

void GuiManager::PopupClearSystem() {
    if (this->state->show_gui["popup_clear"]) {
        ImGui::OpenPopup("Clear System?");
        this->state->show_gui["popup_clear"] = false;
    }

    if (ImGui::ValidationPopup("Clear System?",
                               "Do you really want to erase all the objects in the scene ?\n"
                               "\nIncluding:\n"
                               "     * Corpses\n"
                               "     * Constraints\n"
                               "     * Spawners...\n"
                               "\nThis operation cannot be undone !")) {
        ClearSystem();
    }
}

void GuiManager::ClearSystem() {
    /* Make sure that the arrays are empty */
    /*
    this->selected_corpses_cursor = {};
    this->selected_corpses_index = {};
    this->selected_corpses_fixed = {};
    this->selected_corpses_diff = {};
    this->spawners = {};
    */
    this->state->system.Clear();
}
}