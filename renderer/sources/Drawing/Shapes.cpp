#include "../../include/Drawing/Shapes.hpp"

namespace drw {

uint32_t Shapes::triangles = 0;
uint32_t Shapes::rectangles = 0;
uint32_t Shapes::lines = 0;
uint32_t Shapes::arrows = 0;
uint32_t Shapes::circles = 0;
uint32_t Shapes::springs = 0;
uint32_t Shapes::polygons = 0;

Shapes::Shapes() {}

void Shapes::Reset() {
    Shapes::triangles = 0;
    Shapes::rectangles = 0;
    Shapes::lines = 0;
    Shapes::arrows = 0;
    Shapes::circles = 0;
    Shapes::springs = 0;
    Shapes::polygons = 0;
}

template <typename T>
void Shapes::Draw(const Mesh<T>& mesh, const bgfx::ProgramHandle& program) {
    // TODO:: check availlability with bgfx::getAvailTransientVertexBuffer();

    uint32_t maxVertices = BUFFER_SIZE;
    // uint32_t maxIndexes = BUFFER_SIZE;

    bgfx::TransientVertexBuffer tvb;
    // bgfx::TransientIndexBuffer tib;

    bgfx::allocTransientVertexBuffer(&tvb, maxVertices, mesh.declaration);
    // bgfx::allocTransientIndexBuffer(&tib, maxVertices);

    T* tvb_ptr = (T*)tvb.data;
    // uint32_t* tib_ptr = (uint32_t*)tib.data;

    if (mesh.vertices.size() > maxVertices) LOG_ERROR("No more available space in Transient Vertex Buffer");
    // if (mesh.indexes.size() > maxIndexes) LOG_ERROR("No more available space in Transient Index Buffer");

    std::copy(mesh.vertices.begin(), mesh.vertices.end(), tvb_ptr);
    // std::copy(mesh.indexes.begin(), mesh.indexes.end(), tib_ptr);

    bgfx::setVertexBuffer(0, &tvb, 0, mesh.vertices.size());
    // bgfx::setIndexBuffer(&tib, 0, mesh.indexes.size()); // TODO: fon't work, investigte...

    const uint64_t state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_BLEND_ALPHA | BGFX_STATE_MSAA;

    bgfx::setState(state);
    bgfx::submit(0, program);
}
template void Shapes::Draw<VertexCol>(const Mesh<VertexCol>& mesh, const bgfx::ProgramHandle& program);
template void Shapes::Draw<VertexTex>(const Mesh<VertexTex>& mesh, const bgfx::ProgramHandle& program);

void Shapes::DrawTriangle(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, uint32_t color) {
    const int vertices_size = mesh.vertices.size();

    mesh.vertices.push_back(VertexCol(glm::vec3(pt1.x, pt1.y, pt1.z), color));
    mesh.vertices.push_back(VertexCol(glm::vec3(pt2.x, pt2.y, pt2.z), color));
    mesh.vertices.push_back(VertexCol(glm::vec3(pt3.x, pt3.y, pt3.z), color));

    mesh.indexes.push_back(vertices_size + 0);
    mesh.indexes.push_back(vertices_size + 1);
    mesh.indexes.push_back(vertices_size + 2);

    Shapes::triangles++;
}

void Shapes::DrawTriangle(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3,  //
                          const glm::vec2& tex1, const glm::vec2& tex2, const glm::vec2& tex3, uint32_t color) {    //

    const int vertices_size = mesh.vertices.size();

    mesh.vertices.push_back(VertexTex(glm::vec3(pt1.x, pt1.y, pt1.z), tex1, color));
    mesh.vertices.push_back(VertexTex(glm::vec3(pt2.x, pt2.y, pt2.z), tex2, color));
    mesh.vertices.push_back(VertexTex(glm::vec3(pt3.x, pt3.y, pt3.z), tex3, color));

    mesh.indexes.push_back(vertices_size + 0);
    mesh.indexes.push_back(vertices_size + 1);
    mesh.indexes.push_back(vertices_size + 2);

    Shapes::triangles++;
}

void Shapes::DrawPlane(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, const glm::vec3& pt4, uint32_t color) {
    DrawTriangle(mesh, pt1, pt2, pt3, color);
    DrawTriangle(mesh, pt1, pt3, pt4, color);

    Shapes::rectangles++;
}

void Shapes::DrawPlane(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const glm::vec3& pt3, const glm::vec3& pt4, uint32_t color) {
    DrawTriangle(mesh, pt1, pt2, pt3, {0, 0}, {1, 0}, {1, 1}, color);
    DrawTriangle(mesh, pt1, pt3, pt4, {0, 0}, {1, 1}, {0, 1}, color);

    Shapes::rectangles++;
}

template <typename T>
void Shapes::DrawQuad(Mesh<T>& mesh, const glm::vec3& center, const float& radius, uint32_t color) {
    // TODO: normals with screen orientation
    const glm::vec3 pt1 = glm::vec3(center.x - radius, center.y - radius, center.z);
    const glm::vec3 pt2 = glm::vec3(center.x - radius, center.y + radius, center.z);
    const glm::vec3 pt3 = glm::vec3(center.x + radius, center.y + radius, center.z);
    const glm::vec3 pt4 = glm::vec3(center.x + radius, center.y - radius, center.z);

    DrawPlane(mesh, pt1, pt2, pt3, pt4, color);
}
template void Shapes::DrawQuad<VertexCol>(Mesh<VertexCol>& mesh, const glm::vec3& center, const float& radius, uint32_t color);
template void Shapes::DrawQuad<VertexTex>(Mesh<VertexTex>& mesh, const glm::vec3& center, const float& radius, uint32_t color);

template <typename T>
void Shapes::DrawLine(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color) {
    // TODO: normals with screen orientation
    const glm::vec3 vector = pt2 - pt1;
    const glm::vec3 normal = glm::vec3(-vector.y, vector.x, vector.z);
    const glm::vec3 normalized = glm::normalize(normal) * (thickness / 2.0f);

    DrawPlane(mesh, pt1 - normalized, pt1 + normalized, pt2 + normalized, pt2 - normalized, color);

    Shapes::lines++;
}
template void Shapes::DrawLine<VertexCol>(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);
template void Shapes::DrawLine<VertexTex>(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);

template <typename T>
void Shapes::DrawSpring(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& width, const int& number_waves, uint32_t color) {
    // TODO: normals with screen orientation
    const float inv = 0.25f / number_waves;
    const glm::vec3 diff = (pt2 - pt1) * inv;

    const float inv2 = width / std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
    const glm::vec3 diffpn2 = diff * inv2;
    const glm::vec3 diff2 = glm::vec3(-diffpn2.y, diffpn2.x, diffpn2.z);

    glm::vec3 bpt = pt1;

    for (int i = 0; i < number_waves; i++) {
        DrawLine(mesh, bpt, bpt + diff + diff2, thickness, color);
        DrawLine(mesh, bpt + diff + diff2, bpt + 3.0f * diff - diff2, thickness, color);
        DrawLine(mesh, bpt + 3.0f * diff - diff2, bpt + 4.0f * diff, thickness, color);

        bpt += 4.0f * diff;
    }

    Shapes::springs++;
}
template void Shapes::DrawSpring<VertexCol>(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& width, const int& number_waves, uint32_t color);
template void Shapes::DrawSpring<VertexTex>(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& width, const int& number_waves, uint32_t color);

void Shapes::DrawArrow(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, const float& sz_head, uint32_t color) {
    // TODO: normals with screen orientation
    const float angle = glm::angle(glm::normalize(pt2), glm::normalize(pt1));
    const float length = glm::distance(pt1, pt2);

    const glm::vec3 bottom = pt1;
    const glm::vec3 head = pt2;
    const glm::vec3 diff = head - bottom;
    const glm::vec3 normal = glm::vec3(-diff.y, diff.x, diff.z);
    const glm::vec3 normalized = glm::normalize(normal);

    const float ratio = sz_head / glm::distance(bottom, head);

    const glm::vec3 head_basis = bottom + diff * (1 - ratio);

    const glm::vec3 basis_A = head_basis + normalized * (sz_head / 2.0f);
    const glm::vec3 basis_B = head_basis - normalized * (sz_head / 2.0f);

    DrawTriangle(mesh, head, basis_A, basis_B, color);
    DrawLine(mesh, bottom, head_basis, thickness, color);

    Shapes::arrows++;
}

template <typename T>
void Shapes::DrawRectangle(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, uint32_t color) {
    const glm::vec3 diff = pt2 - pt1;
    const glm::vec3 diffx = glm::vec3(diff.x, 0, 0);
    const glm::vec3 diffy = glm::vec3(0, diff.y, 0);
    const glm::vec3 diffz = glm::vec3(0, 0, diff.z);

    const glm::vec3 spt1 = pt1;
    const glm::vec3 spt2 = pt1 + diffx + diffz;
    const glm::vec3 spt3 = pt1 + diffx + diffy + diffz;
    const glm::vec3 spt4 = pt1 + diffy;

    DrawPlane(mesh, spt1, spt2, spt3, spt4, color);

    Shapes::rectangles++;
}
template void Shapes::DrawRectangle<VertexCol>(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, uint32_t color);
template void Shapes::DrawRectangle<VertexTex>(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, uint32_t color);

template <typename T>
void Shapes::DrawRectangleOutlined(Mesh<T>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color) {
    const glm::vec3 diff = pt2 - pt1;
    const glm::vec3 diffx = glm::vec3(diff.x, 0, 0);
    const glm::vec3 diffy = glm::vec3(0, diff.y, 0);
    const glm::vec3 diffz = glm::vec3(0, 0, diff.z);

    const glm::vec3 spt1 = pt1;
    const glm::vec3 spt2 = pt1 + diffx + diffz;
    const glm::vec3 spt3 = pt1 + diffx + diffy + diffz;
    const glm::vec3 spt4 = pt1 + diffy;

    DrawLine(mesh, spt1, spt2, thickness, color);
    DrawLine(mesh, spt2, spt3, thickness, color);
    DrawLine(mesh, spt3, spt4, thickness, color);
    DrawLine(mesh, spt4, spt1, thickness, color);

    Shapes::rectangles++;
}
template void Shapes::DrawRectangleOutlined<VertexCol>(Mesh<VertexCol>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);
template void Shapes::DrawRectangleOutlined<VertexTex>(Mesh<VertexTex>& mesh, const glm::vec3& pt1, const glm::vec3& pt2, const float& thickness, uint32_t color);

void Shapes::DrawPolygon(Mesh<VertexCol>& mesh, const std::vector<glm::vec3>& points, uint32_t color) {
    for (int i = 2; i < points.size(); i++) { DrawTriangle(mesh, points[0], points[i - 1], points[i], color); }

    Shapes::polygons++;
}

template <typename T>
void Shapes::DrawPolygonOutlined(Mesh<T>& mesh, const std::vector<glm::vec3>& points, const float& thickness, uint32_t color) {
    for (int i = 1; i < points.size(); i++) { DrawLine(mesh, points[i - 1], points[i], thickness, color); }
    DrawLine(mesh, points[0], points[points.size() - 1], thickness, color);

    Shapes::polygons++;
}
template void Shapes::DrawPolygonOutlined<VertexCol>(Mesh<VertexCol>& mesh, const std::vector<glm::vec3>& points, const float& thickness, uint32_t color);
template void Shapes::DrawPolygonOutlined<VertexTex>(Mesh<VertexTex>& mesh, const std::vector<glm::vec3>& points, const float& thickness, uint32_t color);

void Shapes::DrawCircleFan(Mesh<VertexCol>& mesh, const glm::vec3& pt1, float radius, uint32_t color) {
    // Using a triangle fan to draw the circle shape. It's quite inneficient, better use a shader
    const int circle_resolution = 100;
    const float fresolution = static_cast<float>(circle_resolution);

    glm::vec3 previous = glm::vec3(pt1.x + radius, pt1.y, pt1.z);

    for (int i = 1; i < circle_resolution; i++) {
        float index = static_cast<float>(i);

        float angle = index * 2.0f * PI / (fresolution - 1.0f);

        glm::vec3 current = glm::vec3(pt1.x + std::cos(angle) * radius, pt1.y + std::sin(angle) * radius, pt1.z);

        DrawTriangle(mesh, pt1, current, previous, color);

        previous = current;
    }
}

void Shapes::DrawCircleFanOutlined(Mesh<VertexCol>& mesh, const glm::vec3& pt1, float radius, const float& thickness, uint32_t color) {
    // Using a triangle fan to draw the circle shape. It's quite inneficient, better use a shader
    const int circle_resolution = 100;
    const float fresolution = static_cast<float>(circle_resolution);

    glm::vec3 previous = glm::vec3(pt1.x + radius, pt1.y, pt1.z);

    for (int i = 1; i < circle_resolution; i++) {
        float index = static_cast<float>(i);

        float angle = index * 2.0f * PI / (fresolution - 1.0f);

        glm::vec3 current = glm::vec3(pt1.x + std::cos(angle) * radius, pt1.y + std::sin(angle) * radius, pt1.z);

        DrawLine(mesh, current, previous, thickness, color);

        previous = current;
    }
}

}  // namespace drw