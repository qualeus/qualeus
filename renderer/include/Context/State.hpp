#ifndef State_HPP
#define State_HPP

#include <System/System.hpp>
#include <unordered_map>

#include "../Drawing/Camera.hpp"

#define G_DEBUG_MIN_FRAME_SIZE 10   // Min size of framerate array
#define G_DEBUG_MAX_FRAME_SIZE 300  // Max size of framerate array

#define G_SIDE_BAR_SIZE 60        // Size in Px
#define G_SIDE_CONTENT_SIZE 300   // Size in Px
#define G_TIME_BAR_SIZE 30        // Size in Px
#define G_HANDLE_SIZE 20          // Size in Px
#define G_OPENED_BAR_SIZE 400     // Size in Px
#define G_UP_DOCK_SIZE 0.10f      // 100% <=> 1.0f
#define G_BOTTOM_DOCK_SIZE 0.20f  // 100% <=> 1.0f
#define G_LEFT_DOCK_SIZE 0.25f    // 100% <=> 1.0f
#define G_RIGHT_DOCK_SIZE 0.25f   // 100% <=> 1.0f

#define G_ANIMATION_SPEED 10.0f

#define G_WINDOW_LABEL_SPACE 100  // remaining space for the label
#define G_WINDOW_LABEL_MIN 400    // minimum width of the widow for the label resize
#define G_WINDOW_BORDER 50        // right border of the window

#define S_MENU_INTERFACE 1
#define S_MENU_QUALEUS 2
#define S_MENU_CONSOLE 3

#define F_SMALLER_SIZE 14
#define F_DEFAULT_SIZE 16
#define F_MEDIUM_SIZE 20
#define F_BIGGER_SIZE 26

#define I_SMALLER_SIZE 16
#define I_DEFAULT_SIZE 20
#define I_MEDIUM_SIZE 30
#define I_BIGGER_SIZE 40

#define F_ROBOTO_DEFAULT 0
#define F_ROBOTO_MEDIUM 1
#define F_ROBOTO_BIGGER 2
#define F_CONSOLAS_SMALLER 3
#define F_PROGGY_SMALLER 4

#define I_MOUSE_TYPE_CURSOR 0
#define I_MOUSE_TYPE_MOVE 1
#define I_MOUSE_TYPE_RESIZE 2

#define I_SIDE_MENU_DEFAULT 0
#define I_SIDE_MENU_SHAPE 1
#define I_SIDE_MENU_SPAWNER 2

namespace ctx {

enum Theme { Classic, Dark, Violet, Light };

struct Spawner {
    phy::Corpse model;
    bool repeat;
    double delay;
    double last = 0;
};

class State {
   private:
   public:
    phy::System system;
    drw::Camera camera;

    Spawner spawners_model = {phy::Corpse(), false, 1};

    std::vector<Spawner> spawners     = {};
    std::vector<int> corpses_selected = {};

    std::unordered_map<int, uint32_t> corpses_colors     = {};
    std::unordered_map<int, uint32_t> constraints_colors = {};

    bool paused            = false;
    bool reset_base_layout = false;

    bool debug_system_edited = false;
    bool locked_accuracy     = true;

    int input_mouse_type = I_MOUSE_TYPE_MOVE;
    int input_side_menu  = I_SIDE_MENU_DEFAULT;

    Theme theme = Theme::Classic;

    std::unordered_map<std::string, bool> show_gui = {
        {"selection", true},    // show_gui_selection
        {"spawners", true},     // show_gui_spawner
        {"state", true},        // show_gui_spawner
        {"console", false},     // show_gui_console
        {"settings", false},    // show_gui_settings
        {"imguidemo", false},   // show_gui_imguidemo
        {"benchmark", false},   // show_gui_benchmark
        {"popup_clear", false}  // show_popup_clear_system
    };

    std::unordered_map<std::string, bool> show_debug = {
        {"contacts", false},  // show_debug_contacts
    };

    std::unordered_map<std::string, bool> post_process = {
        {"grid", false},  // post_process_grid
    };

    State();
};

}  // namespace ctx
#endif
