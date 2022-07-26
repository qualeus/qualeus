#include "../../include/Mesh/Mesh.hpp"

namespace drw {

template <typename T>
Mesh<T>::Mesh() {
    this->vertices = {};
    this->indexes = {};
}
template Mesh<VertexCol>::Mesh();
template Mesh<VertexTex>::Mesh();

}  // namespace drw