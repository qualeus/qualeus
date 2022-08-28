#ifndef Camera_HPP
#define Camera_HPP
#include <GLFW/glfw3.h>

#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/transform.hpp>

namespace drw {

class Camera {
   private:
    glm::mat4 m_view;
    glm::mat4 m_proj;

    glm::vec4 m_viewport;
    glm::vec3 m_position;
    glm::vec3 m_towards;

    float m_fov = 45.0f;
    float m_near = 1.0f;
    float m_far = 300.0f;

   public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 towards = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4 viewport = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

    void set_position(glm::vec3 position);
    glm::vec3 get_position() const;

    void set_towards(glm::vec3 towards);
    glm::vec3 get_towards() const;

    void set_view_matrix(float* view_matrix);
    glm::mat4 get_view_matrix() const;

    void set_proj_matrix(float* proj_matrix);
    glm::mat4 get_proj_matrix() const;

    void set_viewport(glm::vec4 point);
    glm::vec4 get_viewport() const;

    glm::vec3 project_point(glm::vec3 position) const;

    float get_fov() const;
    void set_fov(float fov);

    float get_near() const;
    void set_near(float near);

    float get_far() const;
    void set_far(float far);
};

}  // namespace drw
#endif