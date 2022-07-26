#ifndef GuiManager_HPP
#define GuiManager_HPP

#include <bgfx/bgfx.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <Common/String.hpp>

#include "../../../assets/fonts/consolas.hpp"
#include "../../../assets/fonts/forkawersome.hpp"
#include "../../../assets/fonts/icons.hpp"
#include "../../../assets/fonts/proggy.hpp"
#include "../../../assets/fonts/roboto.hpp"
#include "../../../assets/icon/ricon.hpp"
#include "../../Context/State.hpp"
#include "../../Serialization/FileManager.hpp"
#include "../../Serialization/Serialization.hpp"
#include "Config.hpp"
#include "GuiModule.hpp"
#include "GuiTheme.hpp"

namespace ovl {

class GuiManager {
   private:
    ctx::State* state;

    ImGui::Console console;

    ImGuiID dockspace_id;
    ImGuiID dockspace_bottom_id;
    ImGuiID dockspace_left_id;
    ImGuiID dockspace_right_id;
    ImGuiID dockspace_up_id;

    bgfx::TextureHandle roboto_default;
    bgfx::TextureHandle roboto_medium;
    bgfx::TextureHandle roboto_bigger;
    bgfx::TextureHandle consolas_smaller;
    bgfx::TextureHandle proggy_smaller;

   public:
    GuiManager(ctx::State* state);
    bgfx::TextureHandle addFont(const std::string font_name, const void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, float icon_pixels);
    void Setup();
    void SetupGuiBaseLayout();
    void DrawGuiDocking();
    void DrawGui();
    void UpdateTheme();

    /* GuiMenu */
    void DrawGuiMenu();
    void PopupClearSystem();
    void ClearSystem();

    void ShowGuiSettingsInterface();
    void ShowGuiSettings(bool* p_open);
    void ShowGuiSelection(bool* p_open);
};

}  // namespace ovl

#endif