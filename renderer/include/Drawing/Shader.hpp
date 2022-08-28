#ifndef Shader_HPP
#define Shader_HPP

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <Common/String.hpp>
#include <glm/vec3.hpp>
#include <stdexcept>
#include <string>

// base shader
#include "../../assets/shaders/default/fs_shaders/fs_base_dx11.bin.hpp"
#include "../../assets/shaders/default/fs_shaders/fs_base_dx9.bin.hpp"
#include "../../assets/shaders/default/fs_shaders/fs_base_essl.bin.hpp"
#include "../../assets/shaders/default/fs_shaders/fs_base_glsl.bin.hpp"
#include "../../assets/shaders/default/fs_shaders/fs_base_metal.bin.hpp"
#include "../../assets/shaders/default/vs_shaders/vs_base_dx11.bin.hpp"
#include "../../assets/shaders/default/vs_shaders/vs_base_dx9.bin.hpp"
#include "../../assets/shaders/default/vs_shaders/vs_base_essl.bin.hpp"
#include "../../assets/shaders/default/vs_shaders/vs_base_glsl.bin.hpp"
#include "../../assets/shaders/default/vs_shaders/vs_base_metal.bin.hpp"

// circle shader
#include "../../assets/shaders/circle/fs_shaders/fs_circle_dx11.bin.hpp"
#include "../../assets/shaders/circle/fs_shaders/fs_circle_dx9.bin.hpp"
#include "../../assets/shaders/circle/fs_shaders/fs_circle_essl.bin.hpp"
#include "../../assets/shaders/circle/fs_shaders/fs_circle_glsl.bin.hpp"
#include "../../assets/shaders/circle/fs_shaders/fs_circle_metal.bin.hpp"
#include "../../assets/shaders/circle/vs_shaders/vs_circle_dx11.bin.hpp"
#include "../../assets/shaders/circle/vs_shaders/vs_circle_dx9.bin.hpp"
#include "../../assets/shaders/circle/vs_shaders/vs_circle_essl.bin.hpp"
#include "../../assets/shaders/circle/vs_shaders/vs_circle_glsl.bin.hpp"
#include "../../assets/shaders/circle/vs_shaders/vs_circle_metal.bin.hpp"

namespace drw {

// Triangle mesh
class Shader {
   public:
    static const bgfx::Memory *get_base_vs_shader();
    static const bgfx::Memory *get_base_fs_shader();

    static const bgfx::Memory *get_circle_vs_shader();
    static const bgfx::Memory *get_circle_fs_shader();

    static bgfx::ProgramHandle create_program(const char *name, const bgfx::Memory *memory_vs, const bgfx::Memory *memory_fs);
};

}  // namespace drw

#endif