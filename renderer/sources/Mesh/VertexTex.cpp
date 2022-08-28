#include "../../include/Mesh/VertexTex.hpp"

namespace drw {

VertexTex::VertexTex(glm::vec3 _position, glm::vec2 _texture, uint32_t _color) : Vertex(_position) {
    texture = _texture;
    color = _color;
}

VertexTex::VertexTex() : Vertex() {
    texture = glm::vec2();
    color = 0x00000000;
}

}  // namespace drw