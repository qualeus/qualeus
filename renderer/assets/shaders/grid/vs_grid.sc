// clang-format off

$input a_position, a_color0, a_texture_res0, a_offset_zoom0
$output v_color0, v_texture_res0, v_offset_zoom0

#include <bgfx_shader.sh>
#include <shaderlib.sh>

void main() {
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
    v_color0 = a_color0;
	v_texture_res0 = a_texture_res0;
    v_offset_zoom0 = a_offset_zoom0;
}

// clang-format on