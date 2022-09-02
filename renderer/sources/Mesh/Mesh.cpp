#include "../../include/Mesh/Mesh.hpp"

namespace drw {

template <typename T>
Mesh<T>::Mesh() {
    vertices = {};
    indexes  = {};
}
template Mesh<VertexCol>::Mesh();
template Mesh<VertexRef>::Mesh();
template Mesh<VertexTex>::Mesh();

}  // namespace drw