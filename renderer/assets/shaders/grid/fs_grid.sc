// clang-format off

$input v_color0, v_texture_res0, v_offset_zoom0

#include <bgfx_shader.sh>
#include <shaderlib.sh>

float grid(vec2 pos, float width, float zoom) {
    
    const float GRID_DEPTH = 5.0;

    // initiliaze color to black.
    float transparency = 0.0;

    // we must first take the log2 of our current zoom level to aquire
    // the amount of times we have zoomed in 2x.
    float lz = log2(zoom);

    // our gridlines are integer powers of 2 so we floor lz.
    // the minus makes it such that we can multiply rather than divide 
    // later on in the code, after we have exponentiated, which is faster.
    float clz = -ceil(lz);
    
    // when we take the fractional part of lz we get a measure of how close
    // we where to the next integer power of 2.
    float rlz = fract(-lz);
    
    // fz is now an integer power of 2 nearest to 1./zoom.
    float fz = pow(2.0, clz);
    
    // w is the width of the gridlines calculated such
    // that they are always visible on every zoom level
    float w = width * zoom;

    LOOP for (float d = 0.0; d <= GRID_DEPTH; d++) {

        // first and last layer should fade in and out
        float fade = d == 0.0 ? (1.0 - rlz) : d == GRID_DEPTH ? rlz : 1.0;
        
        // horizontal and vertical distance to current gridlines
        vec2 m = abs(fract(pos * fz - 0.5) - 0.5) / fz; 
        
        // and the final coloring
    	transparency += smoothstep(w, w * 0.25, min(m.x, m.y)) / GRID_DEPTH * fade;

        // make the grid finer for the next iteration
        fz *= 2.0;
    }

    return transparency;
}

void main() {
    vec2 uv = v_texture_res0.xy;
    vec2 res = v_texture_res0.wz;

    vec2 offset = v_offset_zoom0.xy;
    float zoom = abs(1.0 + v_offset_zoom0.z) / 100.0;

    vec2 pos = (uv * vec2(res.y, res.x) * res * zoom - offset) / 100.0;
    float col = grid(pos, 0.005, zoom);
    
    gl_FragColor = vec4(col, col, col, col);
}

// clang-format on