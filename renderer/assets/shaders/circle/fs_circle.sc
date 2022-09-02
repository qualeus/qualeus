// clang-format off

$input v_color0, v_texcoord0 

#include <bgfx_shader.sh>
#include <shaderlib.sh>

vec4 circle(vec2 uv, vec2 pos, float rad, vec4 color) {
    // float dx = abs(pos.x - uv.x);
    // float dy = abs(pos.y - uv.y);
    // float dist = sqrt(dx*dx + dy*dy);
    // return vec4(color[0], color[1], color[2], dist < rad);

    vec2 dist = uv - pos;
    float opacity = 1.0 - smoothstep(rad - (rad * 0.01), rad + (rad * 0.01), dot(dist, dist) * 4.0);
    return vec4(color[0], color[1], color[2], opacity);
}

void main() {
    vec2 uv = v_texcoord0.xy;
    vec2 pos = vec2(0.5, 0.5);
    gl_FragColor = circle(uv, pos, 1.0, v_color0);
}

// clang-format on