#include "../../include/Drawing/Shader.hpp"

namespace drw {
const bgfx::Memory *Shader::get_base_vs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::OpenGL: return bgfx::copy(vs_base_glsl, sizeof(vs_base_glsl));
        case bgfx::RendererType::Noop: LOG_ERROR("Can't find the shader type Noop");
        case bgfx::RendererType::Direct3D9: return bgfx::copy(vs_base_dx9, sizeof(vs_base_dx9));
        case bgfx::RendererType::Direct3D11: return bgfx::copy(vs_base_dx11, sizeof(vs_base_dx11));
        case bgfx::RendererType::Direct3D12: LOG_ERROR("Can't find the shader type Direct3D12");
        case bgfx::RendererType::OpenGLES: return bgfx::copy(vs_base_essl, sizeof(vs_base_essl));
        case bgfx::RendererType::Metal: return bgfx::copy(vs_base_metal, sizeof(vs_base_metal));
        case bgfx::RendererType::Vulkan: LOG_ERROR("Can't find the shader type Vulkan");
        default: LOG_ERROR("Can't find the shader type.");
    }
}

const bgfx::Memory *Shader::get_base_fs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::OpenGL: return bgfx::copy(fs_base_glsl, sizeof(fs_base_glsl));
        case bgfx::RendererType::Noop: LOG_ERROR("Can't find the shader type Noop");
        case bgfx::RendererType::Direct3D9: return bgfx::copy(fs_base_dx9, sizeof(fs_base_dx9));
        case bgfx::RendererType::Direct3D11: return bgfx::copy(fs_base_dx11, sizeof(fs_base_dx11));
        case bgfx::RendererType::Direct3D12: LOG_ERROR("Can't find the shader type Direct3D12");
        case bgfx::RendererType::OpenGLES: return bgfx::copy(fs_base_essl, sizeof(fs_base_essl));
        case bgfx::RendererType::Metal: return bgfx::copy(fs_base_metal, sizeof(fs_base_metal));
        case bgfx::RendererType::Vulkan: LOG_ERROR("Can't find the shader type Vulkan");
        default: LOG_ERROR("Can't find the shader type.");
    }
}

const bgfx::Memory *Shader::get_circle_vs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::OpenGL: return bgfx::copy(vs_circle_glsl, sizeof(vs_circle_glsl));
        case bgfx::RendererType::Noop: LOG_ERROR("Can't find the shader type Noop");
        case bgfx::RendererType::Direct3D9: return bgfx::copy(vs_circle_dx9, sizeof(vs_circle_dx9));
        case bgfx::RendererType::Direct3D11: return bgfx::copy(vs_circle_dx11, sizeof(vs_circle_dx11));
        case bgfx::RendererType::Direct3D12: LOG_ERROR("Can't find the shader type Direct3D12");
        case bgfx::RendererType::OpenGLES: return bgfx::copy(vs_circle_essl, sizeof(vs_circle_essl));
        case bgfx::RendererType::Metal: return bgfx::copy(vs_circle_metal, sizeof(vs_circle_metal));
        case bgfx::RendererType::Vulkan: LOG_ERROR("Can't find the shader type Vulkan");
        default: LOG_ERROR("Can't find the shader type.");
    }
}

const bgfx::Memory *Shader::get_circle_fs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::OpenGL: return bgfx::copy(fs_circle_glsl, sizeof(fs_circle_glsl));
        case bgfx::RendererType::Noop: LOG_ERROR("Can't find the shader type Noop");
        case bgfx::RendererType::Direct3D9: return bgfx::copy(fs_circle_dx9, sizeof(fs_circle_dx9));
        case bgfx::RendererType::Direct3D11: return bgfx::copy(fs_circle_dx11, sizeof(fs_circle_dx11));
        case bgfx::RendererType::Direct3D12: LOG_ERROR("Can't find the shader type Direct3D12");
        case bgfx::RendererType::OpenGLES: return bgfx::copy(fs_circle_essl, sizeof(fs_circle_essl));
        case bgfx::RendererType::Metal: return bgfx::copy(fs_circle_metal, sizeof(fs_circle_metal));
        case bgfx::RendererType::Vulkan: LOG_ERROR("Can't find the shader type Vulkan");
        default: LOG_ERROR("Can't find the shader type.");
    }
}

const bgfx::Memory *Shader::get_grid_vs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::OpenGL: return bgfx::copy(vs_grid_glsl, sizeof(vs_grid_glsl));
        case bgfx::RendererType::Noop: LOG_ERROR("Can't find the shader type Noop");
        case bgfx::RendererType::Direct3D9: return bgfx::copy(vs_grid_dx9, sizeof(vs_grid_dx9));
        case bgfx::RendererType::Direct3D11: return bgfx::copy(vs_grid_dx11, sizeof(vs_grid_dx11));
        case bgfx::RendererType::Direct3D12: LOG_ERROR("Can't find the shader type Direct3D12");
        case bgfx::RendererType::OpenGLES: return bgfx::copy(vs_grid_essl, sizeof(vs_grid_essl));
        case bgfx::RendererType::Metal: return bgfx::copy(vs_grid_metal, sizeof(vs_grid_metal));
        case bgfx::RendererType::Vulkan: LOG_ERROR("Can't find the shader type Vulkan");
        default: LOG_ERROR("Can't find the shader type.");
    }
}

const bgfx::Memory *Shader::get_grid_fs_shader() {
    switch (bgfx::getRendererType()) {
        case bgfx::RendererType::OpenGL: return bgfx::copy(fs_grid_glsl, sizeof(fs_grid_glsl));
        case bgfx::RendererType::Noop: LOG_ERROR("Can't find the shader type Noop");
        case bgfx::RendererType::Direct3D9: return bgfx::copy(fs_grid_dx9, sizeof(fs_grid_dx9));
        case bgfx::RendererType::Direct3D11: return bgfx::copy(fs_grid_dx11, sizeof(fs_grid_dx11));
        case bgfx::RendererType::Direct3D12: LOG_ERROR("Can't find the shader type Direct3D12");
        case bgfx::RendererType::OpenGLES: return bgfx::copy(fs_grid_essl, sizeof(fs_grid_essl));
        case bgfx::RendererType::Metal: return bgfx::copy(fs_grid_metal, sizeof(fs_grid_metal));
        case bgfx::RendererType::Vulkan: LOG_ERROR("Can't find the shader type Vulkan");
        default: LOG_ERROR("Can't find the shader type.");
    }
}

bgfx::ProgramHandle Shader::create_program(const char *name, const bgfx::Memory *memory_vs, const bgfx::Memory *memory_fs) {
    bgfx::ShaderHandle vs = bgfx::createShader(memory_vs);
    bgfx::ShaderHandle fs = bgfx::createShader(memory_fs);

    return bgfx::createProgram(vs, fs, true);
}
}  // namespace drw