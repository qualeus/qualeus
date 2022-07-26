#include "../../include/Mesh/VertexTex.hpp"

namespace drw {

VertexTex::VertexTex(glm::vec3 position, glm::vec2 texture, uint32_t color) : Vertex(position) {
    this->texture = texture;
    this->color = color;
}

VertexTex::VertexTex() : Vertex() {
    this->texture = glm::vec2();
    this->color = 0x00000000;
}

}  // namespace drw