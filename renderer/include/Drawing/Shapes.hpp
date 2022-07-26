#ifndef Shapes_HPP
#define Shapes_HPP

#include <GLFW/glfw3.h>

#include <Common/String.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../Mesh/Mesh.hpp"
#include "../Mesh/Vertex.hpp"
#include "../Mesh/VertexCol.hpp"
#include "../Mesh/VertexTex.hpp"

namespace drw {

#define BUFFER_SIZE 100000

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
    static void Draw(const Mesh<T>& mesh, const bgfx::ProgramHandle& program);

    static void DrawTriangle(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, uint32_t color);
    static void DrawTriangle(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3,  //
                             const glm::vec2& tex1, const glm::vec2& tex2, const glm::vec2& tex3, uint32_t color);     //

    static void DrawPlane(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, const glm::vec3& pt4, uint32_t color);
    static void DrawPlane(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, const glm::vec3& pt4, uint32_t color);

    template <typename T>
    static void DrawQuad(Mesh<T>& mesh, const glm::vec3& center, const float& radius, uint32_t color);

    template <typename T>
    static void DrawLine(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);

    template <typename T>
    static void DrawSpring(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& width, const int& number_waves, uint32_t color);

    static void DrawArrow(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& sz_head, uint32_t color);

    template <typename T>
    static void DrawRectangle(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, uint32_t color);

    template <typename T>
    static void DrawRectangleOutlined(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);

    static void DrawPolygon(Mesh<VertexCol>& mesh, const std::vector<glm::vec3>& points, uint32_t color);

    template <typename T>
    static void DrawPolygonOutlined(Mesh<T>& mesh, const std::vector<glm::vec3>& points, const float& thickness, uint32_t color);

    static void DrawCircleFan(Mesh<VertexCol>& mesh, const glm::vec3& pt1, float radius, uint32_t color);

    static void DrawCircleFanOutlined(Mesh<VertexCol>& mesh, const glm::vec3& pt1, float radius, const float& thickness, uint32_t color);

    static void Reset();
};

}  // namespace drw
#endif