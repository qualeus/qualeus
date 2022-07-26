#include "../../include/Mesh/Vertex.hpp"

namespace drw {

Vertex::Vertex(glm::vec3 position) { this->position = position; }

Vertex::Vertex() { this->position = glm::vec3(); }

}  // namespace drw