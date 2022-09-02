#ifndef Shapes_HPP
#define Shapes_HPP

#include <GLFW/glfw3.h>

#include <Common/String.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../Mesh/Mesh.hpp"
#include "../Mesh/Vertex.hpp"
#include "../Mesh/VertexCol.hpp"
#include "../Mesh/VertexRef.hpp"
#include "../Mesh/VertexTex.hpp"

namespace drw {

#define BUFFER_SIZE 50000

class Shapes {
   private:
    Shapes();

   public:
    static uint32_t triangles;
    static uint32_t rectangles;
    static uint32_t lines;
    static uint32_t arrows;
    static uint32_t circles;
    static uint32_t springs;
    static uint32_t polygons;

    template <typename T>
    static void draw(const Mesh<T>& mesh, const bgfx::ProgramHandle& program, uint32_t maxVertices);

    static void draw_triangle(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, uint32_t color);
    static void draw_triangle(Mesh<VertexTex>& mesh,
                              const glm::vec3& pt1,  // vertices positions
                              const glm::vec3& pt2,
                              const glm::vec3& pt3,
                              const glm::vec2& tex1,  // vertices texture points
                              const glm::vec2& tex2,
                              const glm::vec2& tex3,
                              uint32_t color);

    static void draw_triangle(Mesh<VertexRef>& mesh,
                              const glm::vec3& pt1,  // vertices positions
                              const glm::vec3& pt2,
                              const glm::vec3& pt3,
                              const glm::vec2& tex1,  // vertices texture points
                              const glm::vec2& tex2,
                              const glm::vec2& tex3,
                              const glm::vec2& res,     // shape real size
                              const glm::vec2& offset,  // camera offset from origin
                              const float& zoom,        // camera zoom in absolute
                              uint32_t color);

    static void draw_plane(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, const glm::vec3& pt4, uint32_t color);
    static void draw_plane(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, const glm::vec3& pt4, uint32_t color);
    static void draw_plane(Mesh<VertexRef>& mesh,
                           const glm::vec3& pt1,
                           const glm::vec3& pt2,
                           const glm::vec3& pt3,
                           const glm::vec3& pt4,
                           const glm::vec2& res,     // shape real size
                           const glm::vec2& offset,  // camera offset from origin
                           const float& zoom,        // camera zoom in absolute
                           uint32_t color);

    template <typename T>
    static void draw_quad(Mesh<T>& mesh, const glm::vec3& center, const float& radius, uint32_t color);

    template <typename T>
    static void draw_line(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);

    template <typename T>
    static void draw_spring(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& width, const int& number_waves, uint32_t color);

    static void draw_arrow(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& sz_head, uint32_t color);

    template <typename T>
    static void draw_rectangle(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, uint32_t color);

    template <typename T>
    static void draw_rectangle_outlined(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);

    static void draw_polygon(Mesh<VertexCol>& mesh, const std::vector<glm::vec3>& points, uint32_t color);

    template <typename T>
    static void draw_polygon_outlined(Mesh<T>& mesh, const std::vector<glm::vec3>& points, const float& thickness, uint32_t color);

    static void draw_circle_fan(Mesh<VertexCol>& mesh, const glm::vec3& pt1, float radius, uint32_t color);

    static void draw_circle_fan_outlined(Mesh<VertexCol>& mesh, const glm::vec3& pt1, float radius, const float& thickness, uint32_t color);

    static void reset();
};

}  // namespace drw
#endif