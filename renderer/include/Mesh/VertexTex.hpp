#ifndef VertexTex_HPP
#define VertexTex_HPP

#include "Vertex.hpp"

namespace drw {

class VertexTex : public Vertex {
   public:
    glm::vec2 texture;
    uint32_t color;

    VertexTex(glm::vec3 position, glm::vec2 texture, uint32_t color);
    VertexTex();
};

}  // namespace drw

#endif