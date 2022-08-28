#include "../../include/Context/Window.hpp"

namespace ctx {

Window::Window(int width, int height, std::string title) : m_overlay(ovl::Overlay()) {
    m_width = width;
    m_height = height;
    m_title = title;
}

void Window::initialize_glfw() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) LOG_ERROR("glfwInit failed.");
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(get_width(), get_height(), m_title.c_str(), nullptr, nullptr);

    if (!m_window) {
        cleanup();
        LOG_ERROR("glfwCreateWindow failed.");
    }

    // Setting some window callbacks
    glfwSetWindowSizeCallback(m_window, glfw_window_size_callback);
    glfwSetKeyCallback(m_window, glfw_key_callback);
    glfwSetCharCallback(m_window, glfw_char_callback);
    glfwSetMouseButtonCallback(m_window, glfw_mouse_button_callback);
    glfwSetScrollCallback(m_window, glfw_scroll_callback);
    glfwSetCursorPosCallback(m_window, glfw_cursor_pos_callback);

    glfwSetWindowUserPointer(m_window, this);
}

void Window::initialize_bgfx() {
    // Tell bgfx about our m_window
    bgfx::PlatformData platform_data = {};

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    platform_data.ndt = glfwGetX11Display();
    platform_data.nwh = (void *)(uintptr_t)glfwGetX11Window(m_window);
#elif BX_PLATFORM_OSX
    platform_data.nwh = glfwGetCocoaWindow(m_window);
#elif BX_PLATFORM_WINDOWS
    platform_data.nwh = glfwGetWin32Window(m_window);
#endif
    bgfx::setPlatformData(platform_data);

    // Init bgfx
    bgfx::Init init;
    // init.type = bgfx::RendererType::Vulkan;  // Select rendering backend
    init.vendorId = BGFX_PCI_ID_NONE;  // Choose graphics card vendor
    init.deviceId = 0;                 // Choose which graphics card to use
    init.callback = nullptr;

    if (!bgfx::init(init)) LOG_ERROR("unable to initialize bgfx.");
}

void Window::initialize_imgui() {
#if ENABLE_IMGUI
    m_overlay.initialize(m_window);
#endif
}

void Window::render() {
    initialize_glfw();
    initialize_bgfx();
    initialize_imgui();

    reset();
}

void Window::reset() {
    bgfx::reset(get_width(), get_height());

#if ENABLE_IMGUI
    m_overlay.reset(get_width(), get_height());
#endif

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, BACKGROUND_COLOR, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void Window::clear() { }

void Window::pre_draw() {
    // Calculate delta time
    m_current_time = (float)glfwGetTime();  // std::static_cast<float>(glfwGetTime());
    m_delta_time = m_current_time - m_last_time;
    m_last_time = m_current_time;

    // Poll events
    Inputs::reset_inputs();
    glfwPollEvents();

#if ENABLE_IMGUI
    m_overlay.poll_events(m_delta_time);
#endif

    // Render
    ImGui::NewFrame();

    bgfx::touch(0);
}

void Window::draw() {
#if ENABLE_IMGUI
    m_overlay.draw();
#endif

    bgfx::frame();
}

void Window::close() {
    glfwDestroyWindow(m_window);
    cleanup();
}

void Window::cleanup() {
#if ENABLE_IMGUI
    m_overlay.cleanup();
#endif

    bgfx::shutdown();
    glfwTerminate();
}

bool Window::is_open() {
    return !glfwWindowShouldClose(m_window);
}
int Window::get_width() {
    return m_width;
}
int Window::get_height() {
    return m_height;
}

void Window::glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void Window::glfw_window_size_callback(GLFWwindow *m_window, int width, int height) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(m_window));
    ctx->m_width = width;
    ctx->m_height = height;
    ctx->reset();
}

void Window::glfw_key_callback(GLFWwindow *m_window, int key, int scancode, int action, int mods) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(m_window));

#if ENABLE_IMGUI
    ctx->m_overlay.glfw_key_callback(m_window, key, scancode, action, mods);
#else
    ctx::Inputs::handle_keyboard_inputs(key, action);
#endif
}

void Window::glfw_char_callback(GLFWwindow *m_window, unsigned int codepoint) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(m_window));

#if ENABLE_IMGUI
    ctx->m_overlay.glfw_char_callback(m_window, codepoint);
#else

#endif
}

void Window::glfw_mouse_button_callback(GLFWwindow *m_window, int button, int action, int mods) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(m_window));

#if ENABLE_IMGUI
    ctx->m_overlay.glfw_mouse_button_callback(m_window, button, action, mods);
#else
    ctx::Inputs::handle_mouse_inputs(button, action);
#endif
}

void Window::glfw_cursor_pos_callback(GLFWwindow *m_window, double xpos, double ypos) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(m_window));

#if ENABLE_IMGUI
    ctx->m_overlay.glfw_cursor_pos_callback(m_window, xpos, ypos);
#else
    ctx::Inputs::handle_cursor_pos(xpos, ypos);
#endif
}

void Window::glfw_scroll_callback(GLFWwindow *m_window, double xoffset, double yoffset) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(m_window));

#if ENABLE_IMGUI
    ctx->m_overlay.glfw_scroll_callback(m_window, xoffset, yoffset);
#else
    ctx::Inputs::handle_mouse_scroll(xoffset, yoffset);
#endif
}

}  // namespace ctx