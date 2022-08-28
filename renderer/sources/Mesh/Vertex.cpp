#include "../../include/Mesh/Vertex.hpp"

namespace drw {

Vertex::Vertex(glm::vec3 _position) {
    position = _position;
}

Vertex::Vertex() {
    position = glm::vec3();
}

}  // namespace drw