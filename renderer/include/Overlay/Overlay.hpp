#ifndef Overlay_HPP
#define Overlay_HPP

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <imgui.h>

#include <Common/String.hpp>
#include <stdexcept>
#include <string>

// EXPOSE THE RIGHT GLFW HEADERS
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#elif __unix__
#define GLFW_EXPOSE_NATIVE_X11
#elif __linux__
#define GLFW_EXPOSE_NATIVE_WAYLAND
#elif __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>
#include <bgfx/platform.h>

#include "../../assets/shaders/imgui/fs_imgui.bin.hpp"
#include "../../assets/shaders/imgui/vs_imgui.bin.hpp"
#include "../Context/Inputs.hpp"
#include "ImGuiHelper.hpp"

namespace ovl {

class Overlay {
   private:
    const bgfx::Memory* get_vs_shader();
    const bgfx::Memory* get_fs_shader();
    bgfx::ProgramHandle create_program(const char* name);

   public:
    Overlay();

    void Initialize(GLFWwindow* window);
    void Draw();
    void PollEvents(float dt);
    void Reset(int width, int height);
    void Cleanup();

    void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void glfw_char_callback(GLFWwindow* window, unsigned int codepoint);
    void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

}  // namespace ovl
#endif