#include "../../include/Drawing/Camera.hpp"

namespace drw {
Camera::Camera(glm::vec3 position, glm::vec3 towards, glm::vec4 viewport) {
    m_position = position;
    m_towards = towards;
    m_viewport = viewport;
}

glm::vec3 Camera::get_position() const {
    return m_position;
}
void Camera::set_position(glm::vec3 position) {
    m_position = position;
}

glm::vec3 Camera::get_towards() const {
    return m_towards;
}
void Camera::set_towards(glm::vec3 towards) {
    m_towards = towards;
}

void Camera::set_view_matrix(float* view_matrix) {
    m_view = glm::make_mat4(view_matrix);
}
glm::mat4 Camera::get_view_matrix() const {
    return m_view;
}

void Camera::set_proj_matrix(float* proj_matrix) {
    m_proj = glm::make_mat4(proj_matrix);
}
glm::mat4 Camera::get_proj_matrix() const {
    return m_proj;
}

void Camera::set_viewport(glm::vec4 viewport) {
    m_viewport = viewport;
}
glm::vec4 Camera::get_viewport() const {
    return m_viewport;
}

glm::vec3 Camera::project_point(glm::vec3 position) const {
    float half_y = (m_viewport[3] - m_viewport[1]) - position.y;
    glm::vec3 flipped_y = glm::vec3(position.x, half_y, position.z);
    glm::vec3 start = glm::unProject(flipped_y, m_view, m_proj, m_viewport);
    glm::vec3 end = glm::unProject(flipped_y + glm::vec3(0.0f, 0.0f, -1.0f), m_view, m_proj, m_viewport);
    glm::vec3 dir = end - start;

    // base plane
    glm::vec3 p_origin = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 p_normal = glm::vec3(0.f, 0.f, -1.f);

    float distance = 0.0f;

    // intersection of line an plane
    bool intersect = glm::intersectRayPlane(start, dir, p_origin, p_normal, distance);

    return start + distance * dir;
}

float Camera::get_fov() const {
    return m_fov;
}
void Camera::set_fov(float fov) {
    m_fov = fov;
}

float Camera::get_near() const {
    return m_near;
}
void Camera::set_near(float near) {
    m_near = near;
}

float Camera::get_far() const {
    return m_far;
}
void Camera::set_far(float far) {
    m_far = far;
}

}  // namespace drw