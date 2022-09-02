#ifndef Mesh_HPP
#define Mesh_HPP

#include <bgfx/bgfx.h>

#include <Common/String.hpp>
#include <glm/vec3.hpp>
#include <vector>

#include "Vertex.hpp"
#include "VertexCol.hpp"
#include "VertexRef.hpp"
#include "VertexTex.hpp"

namespace drw {

template <typename T>
class Mesh {
   public:
    std::vector<T> vertices;
    std::vector<uint32_t> indexes;
    bgfx::VertexLayout declaration;

    Mesh();
};

}  // namespace drw
#endif