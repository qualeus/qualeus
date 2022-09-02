#ifndef VertexRef_HPP
#define VertexRef_HPP

#include "Vertex.hpp"

namespace drw {

class VertexRef : public Vertex {
   public:
    glm::vec4 texture_res;
    glm::vec3 offset_zoom;
    uint32_t color;

    VertexRef(glm::vec3 position, glm::vec2 texture, glm::vec2 resolution, glm::vec2 offset, float zoom, uint32_t color);
    VertexRef();
};

}  // namespace drw

#endif