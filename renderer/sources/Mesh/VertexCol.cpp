#include "../../include/Mesh/VertexCol.hpp"

namespace drw {

VertexCol::VertexCol(glm::vec3 position, uint32_t color) : Vertex(position) { this->color = color; }

VertexCol::VertexCol() : Vertex() { this->color = 0x00000000; }

}  // namespace drw