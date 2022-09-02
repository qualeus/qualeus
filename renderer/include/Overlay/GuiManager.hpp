#ifndef GuiManager_HPP
#define GuiManager_HPP

#include <bgfx/bgfx.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <Common/String.hpp>

#include "../../assets/fonts/consolas.hpp"
#include "../../assets/fonts/forkawersome.hpp"
#include "../../assets/fonts/icons.hpp"
#include "../../assets/fonts/proggy.hpp"
#include "../../assets/fonts/roboto.hpp"
#include "../../assets/icon/ricon.hpp"
#include "../Context/State.hpp"
#include "../Serialization/FileManager.hpp"
#include "../Serialization/Serialization.hpp"
#include "Config.hpp"
#include "GuiModule.hpp"
#include "GuiTheme.hpp"

namespace ovl {

class GuiManager {
   private:
    ctx::State* m_state;

    ImGui::Console m_console;

    ImGuiID m_dockspace_id;
    ImGuiID m_dockspace_bottom_id;
    ImGuiID m_dockspace_left_id;
    ImGuiID m_dockspace_right_id;
    ImGuiID m_dockspace_up_id;

    bgfx::TextureHandle m_roboto_default;
    bgfx::TextureHandle m_roboto_medium;
    bgfx::TextureHandle m_roboto_bigger;
    bgfx::TextureHandle m_consolas_smaller;
    bgfx::TextureHandle m_proggy_smaller;

   public:
    GuiManager(ctx::State* state);

    bgfx::TextureHandle add_font(const std::string font_name, const void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, float icon_pixels);
    void setup();
    void setup_gui_base_layout();
    void draw_gui_docking();
    void draw_gui();
    void update_theme();

    /* GuiMenu */
    void draw_gui_menu();
    void popup_clear_system();
    void clear_system();

    void show_gui_settings(bool* p_open);
    void show_gui_selection(bool* p_open);
    void show_gui_spawner(bool* p_open);
    void show_gui_state(bool* p_open);

    void show_tab_new_spawner();
    void show_tab_list_spawners();

    void editor_corpse(phy::Corpse* corpse);
    void editor_shape(phy::Shape* shape);
    void editor_circle(phy::Circle* circle);
};

}  // namespace ovl

#endif