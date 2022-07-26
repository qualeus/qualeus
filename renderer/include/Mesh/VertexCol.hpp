#ifndef VertexCol_HPP
#define VertexCol_HPP

#include "Vertex.hpp"

namespace drw {

class VertexCol : public Vertex {
   public:
    uint32_t color;

    VertexCol(glm::vec3 position, uint32_t color);
    VertexCol();
};

}  // namespace drw

#endif