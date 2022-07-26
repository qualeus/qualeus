#ifndef Vertex_HPP
#define Vertex_HPP

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <sstream>
#include <string>

namespace drw {

class Vertex {
   public:
    glm::vec3 position;

    Vertex(glm::vec3 position);
    Vertex();
};

}  // namespace drw

#endif