#include "../../include/Overlay/Overlay.hpp"

namespace ovl {

Overlay::Overlay() {}

void Overlay::Initialize(GLFWwindow *window) {
    // Initialize ImGui
    auto imgui_program = create_program("imgui");
    imgui_init(window, imgui_program);
}

const bgfx::Memory *Overlay::get_vs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::Noop:  // fallthrough
        case bgfx::RendererType::Direct3D9: return bgfx::copy(vs_imgui_dx9, vs_imgui_dx9_size);
        case bgfx::RendererType::Direct3D11:  // fallthrough
        case bgfx::RendererType::Direct3D12: return bgfx::copy(vs_imgui_dx11, vs_imgui_dx11_size);
        case bgfx::RendererType::OpenGL: return bgfx::copy(vs_imgui_glsl, vs_imgui_glsl_size);
        case bgfx::RendererType::OpenGLES: return bgfx::copy(vs_imgui_essl, vs_imgui_essl_size);
        case bgfx::RendererType::Metal: return bgfx::copy(vs_imgui_metal, vs_imgui_metal_size);
        case bgfx::RendererType::Vulkan: return bgfx::copy(vs_imgui_spirv, vs_imgui_spirv_size);
        default: LOG_ERROR("Can't find the shader type");
    }
}

const bgfx::Memory *Overlay::get_fs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::Noop:  // fallthrough
        case bgfx::RendererType::Direct3D9: return bgfx::copy(fs_imgui_dx9, fs_imgui_dx9_size);
        case bgfx::RendererType::Direct3D11:  // fallthrough
        case bgfx::RendererType::Direct3D12: return bgfx::copy(fs_imgui_dx11, fs_imgui_dx11_size);
        case bgfx::RendererType::OpenGL: return bgfx::copy(fs_imgui_glsl, fs_imgui_glsl_size);
        case bgfx::RendererType::OpenGLES: return bgfx::copy(fs_imgui_essl, fs_imgui_essl_size);
        case bgfx::RendererType::Metal: return bgfx::copy(fs_imgui_metal, fs_imgui_metal_size);
        case bgfx::RendererType::Vulkan: return bgfx::copy(fs_imgui_spirv, fs_imgui_spirv_size);
        default: LOG_ERROR("Can't find the shader type");
    }
}

bgfx::ProgramHandle Overlay::create_program(const char *name) {
    const bgfx::Memory *imgui_vs = get_vs_shader();
    const bgfx::Memory *imgui_fs = get_fs_shader();

    bgfx::ShaderHandle vs = bgfx::createShader(imgui_vs);
    bgfx::ShaderHandle fs = bgfx::createShader(imgui_fs);

    return bgfx::createProgram(vs, fs, true);
}

void Overlay::Draw() { imgui_render(); }

void Overlay::PollEvents(float dt) { imgui_events(dt); }

void Overlay::Reset(int width, int height) { imgui_reset(width, height); }

void Overlay::Cleanup() { imgui_shutdown(); }

void Overlay::glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    imgui_key_callback(window, key, scancode, action, mods);

    if (!imgui_want_keyboard()) {  // Ignore when ImGui has keyboard focus
        ctx::Inputs::HandleKeyboardInputs(key, action);
    }
}

void Overlay::glfw_char_callback(GLFWwindow *window, unsigned int codepoint) { imgui_char_callback(window, codepoint); }

void Overlay::glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    imgui_mouse_button_callback(window, button, action, mods);

    if (!imgui_want_mouse()) {  // Ignore when ImGui has mouse focus
        ctx::Inputs::HandleMouseInputs(button, action);
    }
}

void Overlay::glfw_cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    if (!imgui_want_mouse()) {  // Ignore when ImGui has mouse focus
        ctx::Inputs::HandleCursorPos(xpos, ypos);
    }
}

void Overlay::glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    imgui_scroll_callback(window, xoffset, yoffset);

    if (!imgui_want_mouse()) {  // Ignore when ImGui has mouse focus
        ctx::Inputs::HandleMouseScroll(xoffset, yoffset);
    }
}

}  // namespace ovl