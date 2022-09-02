#include "../../include/Mesh/VertexRef.hpp"

namespace drw {

VertexRef::VertexRef(glm::vec3 _position, glm::vec2 _texture, glm::vec2 _resolution, glm::vec2 _offset, float _zoom, uint32_t _color) : Vertex(_position) {
    texture_res = glm::vec4(_texture.x, _texture.y, _resolution.x, _resolution.y);
    offset_zoom = glm::vec3(_offset.x, _offset.y, _zoom);
    color       = _color;
}

VertexRef::VertexRef() : Vertex() {
    texture_res = glm::vec4();
    offset_zoom = glm::vec3();
    color       = 0x00000000;
}

}  // namespace drw