#ifndef Renderer_HPP
#define Renderer_HPP

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <bx/math.h>

#include <System/System.hpp>
#include <glm/glm.hpp>

#include "../Drawing/Shader.hpp"
#include "../Drawing/Shapes.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Mesh/Vertex.hpp"
#include "../Mesh/VertexCol.hpp"
#include "../Mesh/VertexRef.hpp"
#include "../Mesh/VertexTex.hpp"
#include "../Overlay/GuiManager.hpp"
#include "Inputs.hpp"
#include "State.hpp"
#include "Window.hpp"

namespace ctx {

class Renderer {
   private:
    Window m_window;
    State m_state;
    ovl::GuiManager m_overlay;

    bgfx::ProgramHandle m_base_shader;
    bgfx::ProgramHandle m_circle_shader;
    bgfx::ProgramHandle m_grid_shader;

    drw::Mesh<drw::VertexCol> m_base_mesh;
    drw::Mesh<drw::VertexTex> m_circle_mesh;
    drw::Mesh<drw::VertexRef> m_grid_mesh;

    int m_debug                       = 0;
    glm::vec3 m_drag_initial_position = glm::vec3();
    glm::vec3 m_drag_initial_towards  = glm::vec3();
    glm::vec3 m_drag_projected_mouse  = glm::vec3();

   public:
    Renderer();
    void render();
    void loop();
    void debug();

    void inputs();
    void global_inputs();
    void debug_inputs();
    void camera_inputs();

    drw::Mesh<drw::VertexCol> declare_color_mesh();
    drw::Mesh<drw::VertexTex> declare_texture_mesh();
    drw::Mesh<drw::VertexRef> declare_reference_mesh();

    void system_step();
    void spawners_step();

    void draw_system();
    void draw_background();

    void draw_corpse(std::shared_ptr<phy::Corpse> corpse, uint32_t color);
    void draw_corpse_selected(std::shared_ptr<phy::Corpse> corpse, uint32_t color);

    void draw_corpse_circle(std::shared_ptr<phy::Corpse> corpse, phy::Circle *circle, uint32_t color);
    void draw_corpse_circle_selected(std::shared_ptr<phy::Corpse> corpse, phy::Circle *circle, uint32_t color);

    void load_shaders();
    void update_camera();
    void declare_meshes();
    void draw_meshes();

    void add_corpse(phy::Corpse corpse, uint32_t color);
    std::shared_ptr<phy::Corpse> get_corpse(int index) const;
};

}  // namespace ctx
#endif