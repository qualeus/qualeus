#ifndef GuiTheme_HPP
#define GuiThemee_HPP

#include "imgui.h"
#include "imgui_internal.h"

namespace ovl {

class GuiTheme {
   private:
    GuiTheme();

   public:
    static void DarkTheme();
    static void VioletTheme();
    static void LightTheme();
    static void ClassicTheme();
};

}  // namespace ovl
#endif