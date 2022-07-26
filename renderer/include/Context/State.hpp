#ifndef State_HPP
#define State_HPP

#include <Structures/System.hpp>
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

class State {
   private:
   public:
    phy::System system;
    drw::Camera camera;

    std::vector<int> corpses_selected;

    std::unordered_map<int, uint32_t> corpses_colors;
    std::unordered_map<int, uint32_t> constraints_colors;

    bool paused = false;
    bool reset_base_layout = false;

    bool debug_system_edited = false;
    bool locked_accuracy = true;

    int input_mouse_type = I_MOUSE_TYPE_MOVE;
    int input_side_menu = I_SIDE_MENU_DEFAULT;

    Theme theme = Theme::Classic;

    std::unordered_map<std::string, bool> show_gui = {
        {"console", false},       // show_gui_console
        {"selection", false},     // show_gui_selection
        {"overlay", false},       // show_gui_overlay
        {"settings", false},      // show_gui_settings
        {"imguidemo", false},     // show_gui_imguidemo
        {"spawner", false},       // show_gui_spawner
        {"benchmark", false},     // show_gui_benchmark
        {"side_bar", false},      // show_side_bar
        {"side_content", false},  // show_side_content
        {"time_bar", false},      // show_time_bar
        {"popup_clear", false}    // show_popup_clear_system
    };

    std::unordered_map<std::string, bool> show_debug = {
        {"quadtree", false},     // show_debug_quadtree
        {"bounds", false},       // show_debug_bounds
        {"centroids", false},    // show_debug_centroids
        {"edges", false},        // show_debug_edges
        {"projections", false},  // show_debug_projections
        {"vertices", false},     // show_debug_vertices
        {"normals", false},      // show_debug_normals
        {"velocity", false},     // show_debug_velocity
        {"xyvelocity", false},   // show_debug_xyvelocity
        {"pairs", false},        // show_debug_pairs
        {"quadpairs", false},    // show_debug_quadpairs
        {"contacts", false},     // show_debug_contacts
        {"collisions", false}    // show_debug_collisions
    };

    std::unordered_map<std::string, bool> post_process = {
        {"blur", false},    // post_process_blur
        {"grid", false},    // post_process_grid
        {"gravity", false}  // post_process_gravity
    };

    float side_bar_size = show_gui["side_bar"] ? G_SIDE_BAR_SIZE : 0.0f;
    float side_content_size = show_gui["side_content"] ? G_SIDE_CONTENT_SIZE : 0.0f;
    float time_bar_size = show_gui["time_bar"] ? G_TIME_BAR_SIZE : 0.0f;

    State();
};

}  // namespace ctx
#endif
