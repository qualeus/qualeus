// clang-format off

$input v_color0, v_texcoord0 

#include <bgfx_shader.sh>
#include <shaderlib.sh>

vec4 circle(vec2 uv, vec2 pos, float rad, vec4 color) {
    float dx = abs(pos.x - uv.x);
    float dy = abs(pos.y - uv.y);
    float dist = sqrt(dx*dx + dy*dy);
    return vec4(color[0], color[1], color[2], dist < rad);
}

void main() {
    vec2 uv = v_texcoord0.xy;
    vec2 center = vec2(0.5, 0.5);
    gl_FragColor = circle(uv, center, 0.5, v_color0);
}

// clang-format on