#ifndef Window_HPP
#define Window_HPP

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

#include <Common/String.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

// intern
#include "../Overlay/Overlay.hpp"
#include "Inputs.hpp"

namespace ctx {

#define ENABLE_IMGUI true
#define BACKGROUND_COLOR 0x0F0f0FFF

class Window {
   private:
    GLFWwindow *window;
    ovl::Overlay overlay;

    std::string title;
    int width;
    int height;

    float last_time = 0;
    float current_time = 0;
    float delta_time = 0;

   public:
    Window(int width = 1024, int height = 768, std::string title = "Window");

    void InitializeGLFW();
    void InitializeBGFX();
    void InitializeIMGUI();

    void Render();
    void Reset();
    void Clear();

    void PreDraw();
    void Draw();
    void Close();
    void Cleanup();
    bool isOpen();

    int get_width();
    int get_height();

    static void glfw_error_callback(int error, const char *description);
    static void glfw_window_size_callback(GLFWwindow *window, int width, int height);
    static void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void glfw_char_callback(GLFWwindow *window, unsigned int codepoint);
    static void glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    static void glfw_cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
    static void glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
};

}  // namespace ctx
#endif