#include "../../include/Mesh/VertexCol.hpp"

namespace drw {

VertexCol::VertexCol(glm::vec3 _position, uint32_t _color) : Vertex(_position) {
    color = _color;
}

VertexCol::VertexCol() : Vertex() {
    color = 0x00000000;
}

}  // namespace drw