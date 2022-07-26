#include "../../include/Drawing/Camera.hpp"

namespace drw {
Camera::Camera(glm::vec3 position, glm::vec3 towards, glm::vec4 viewport) {
    this->position = position;
    this->towards = towards;
    this->viewport = viewport;
}

glm::vec3 Camera::get_position() const { return this->position; }
void Camera::set_position(glm::vec3 position) { this->position = position; }

glm::vec3 Camera::get_towards() const { return this->towards; }
void Camera::set_towards(glm::vec3 towards) { this->towards = towards; }

void Camera::set_view_matrix(float* view_matrix) { this->view = glm::make_mat4(view_matrix); }
glm::mat4 Camera::get_view_matrix() const { return this->view; }

void Camera::set_proj_matrix(float* proj_matrix) { this->proj = glm::make_mat4(proj_matrix); }
glm::mat4 Camera::get_proj_matrix() const { return this->proj; }

void Camera::set_viewport(glm::vec4 viewport) { this->viewport = viewport; }
glm::vec4 Camera::get_viewport() const { return this->viewport; }

glm::vec3 Camera::projectPoint(glm::vec3 position) const {
    float half_y = (this->viewport[3] - this->viewport[1]) - position.y;
    glm::vec3 flipped_y = glm::vec3(position.x, half_y, position.z);
    glm::vec3 start = glm::unProject(flipped_y, this->view, this->proj, this->viewport);
    glm::vec3 end = glm::unProject(flipped_y + glm::vec3(0.0f, 0.0f, -1.0f), this->view, this->proj, this->viewport);
    glm::vec3 dir = end - start;

    // base plane
    glm::vec3 p_origin = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 p_normal = glm::vec3(0.f, 0.f, -1.f);

    float distance = 0.0f;

    // intersection of line an plane
    bool intersect = glm::intersectRayPlane(start, dir, p_origin, p_normal, distance);

    return start + distance * dir;
}

float Camera::get_fov() const { return this->fov; }
void Camera::set_fov(float fov) { this->fov = fov; }

float Camera::get_near() const { return this->near; }
void Camera::set_near(float near) { this->near = near; }

float Camera::get_far() const { return this->far; }
void Camera::set_far(float far) { this->far = far; }

}  // namespace drw