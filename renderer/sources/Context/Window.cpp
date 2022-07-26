#include "../../include/Context/Window.hpp"

namespace ctx {

Window::Window(int width, int height, std::string title) : overlay(ovl::Overlay()) {
    this->width = width;
    this->height = height;
    this->title = title;
}

void Window::InitializeGLFW() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) LOG_ERROR("glfwInit failed.");
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    /* Create a windowed mode window and its OpenGL context */
    this->window = glfwCreateWindow(this->get_width(), this->get_height(), this->title.c_str(), nullptr, nullptr);

    if (!this->window) {
        this->Cleanup();
        LOG_ERROR("glfwCreateWindow failed.");
    }

    // Setting some window callbacks
    glfwSetWindowSizeCallback(window, glfw_window_size_callback);
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetCharCallback(window, glfw_char_callback);
    glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
    glfwSetScrollCallback(window, glfw_scroll_callback);
    glfwSetCursorPosCallback(window, glfw_cursor_pos_callback);

    glfwSetWindowUserPointer(window, this);
}

void Window::InitializeBGFX() {
    // Tell bgfx about our window
    bgfx::PlatformData platform_data = {};

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    platform_data.ndt = glfwGetX11Display();
    platform_data.nwh = (void *)(uintptr_t)glfwGetX11Window(this->window);
#elif BX_PLATFORM_OSX
    platform_data.nwh = glfwGetCocoaWindow(this->window);
#elif BX_PLATFORM_WINDOWS
    platform_data.nwh = glfwGetWin32Window(this->window);
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

void Window::InitializeIMGUI() {
#if ENABLE_IMGUI
    this->overlay.Initialize(this->window);
#endif
}

void Window::Render() {
    this->InitializeGLFW();
    this->InitializeBGFX();
    this->InitializeIMGUI();

    this->Reset();
}

void Window::Reset() {
    bgfx::reset(this->get_width(), this->get_height());

#if ENABLE_IMGUI
    this->overlay.Reset(this->get_width(), this->get_height());
#endif

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, BACKGROUND_COLOR, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void Window::Clear() {}

void Window::PreDraw() {
    // Calculate delta time
    this->current_time = (float)glfwGetTime();  // std::static_cast<float>(glfwGetTime());
    this->delta_time = this->current_time - this->last_time;
    this->last_time = this->current_time;

    // Poll events
    Inputs::ResetInputs();
    glfwPollEvents();

#if ENABLE_IMGUI
    this->overlay.PollEvents(this->delta_time);
#endif

    // Render
    ImGui::NewFrame();

    bgfx::touch(0);
}

void Window::Draw() {
#if ENABLE_IMGUI
    this->overlay.Draw();
#endif

    bgfx::frame();
}

void Window::Close() {
    glfwDestroyWindow(this->window);
    this->Cleanup();
}

void Window::Cleanup() {
#if ENABLE_IMGUI
    this->overlay.Cleanup();
#endif

    bgfx::shutdown();
    glfwTerminate();
}

bool Window::isOpen() { return !glfwWindowShouldClose(this->window); }
int Window::get_width() { return this->width; }
int Window::get_height() { return this->height; }

void Window::glfw_error_callback(int error, const char *description) { fprintf(stderr, "GLFW error %d: %s\n", error, description); }

void Window::glfw_window_size_callback(GLFWwindow *window, int width, int height) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(window));
    ctx->width = width;
    ctx->height = height;
    ctx->Reset();
}

void Window::glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(window));

#if ENABLE_IMGUI
    ctx->overlay.glfw_key_callback(window, key, scancode, action, mods);
#else
    ctx::Inputs::HandleKeyboardInputs(key, action);
#endif
}

void Window::glfw_char_callback(GLFWwindow *window, unsigned int codepoint) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(window));

#if ENABLE_IMGUI
    ctx->overlay.glfw_char_callback(window, codepoint);
#else

#endif
}

void Window::glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(window));

#if ENABLE_IMGUI
    ctx->overlay.glfw_mouse_button_callback(window, button, action, mods);
#else
    ctx::Inputs::HandleMouseInputs(button, action);
#endif
}

void Window::glfw_cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(window));

#if ENABLE_IMGUI
    ctx->overlay.glfw_cursor_pos_callback(window, xpos, ypos);
#else
    ctx::Inputs::HandleCursorPos(xpos, ypos);
#endif
}

void Window::glfw_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    Window *ctx = static_cast<Window *>(glfwGetWindowUserPointer(window));

#if ENABLE_IMGUI
    ctx->overlay.glfw_scroll_callback(window, xoffset, yoffset);
#else
    ctx::Inputs::HandleMouseScroll(xoffset, yoffset);
#endif
}

}  // namespace ctx