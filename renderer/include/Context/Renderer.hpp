#ifndef Renderer_HPP
#define Renderer_HPP

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <bx/math.h>

#include <Common/Maths.hpp>
#include <Common/String.hpp>
#include <Geometry/Geometry.hpp>
#include <Geometry/Vector.hpp>
#include <glm/glm.hpp>

#include "../Drawing/Shader.hpp"
#include "../Drawing/Shapes.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Mesh/Vertex.hpp"
#include "../Mesh/VertexCol.hpp"
#include "../Mesh/VertexTex.hpp"
#include "../Overlay/Gui/GuiManager.hpp"
#include "Inputs.hpp"
#include "State.hpp"
#include "Window.hpp"

namespace ctx {

class Renderer {
   private:
    Window window;
    State state;
    ovl::GuiManager overlay;

    bgfx::ProgramHandle base_shader;
    bgfx::ProgramHandle circle_shader;

    drw::Mesh<drw::VertexCol> base_mesh;
    drw::Mesh<drw::VertexTex> circle_mesh;

    int debug = 0;
    glm::vec3 drag_initial_position = glm::vec3();
    glm::vec3 drag_initial_towards = glm::vec3();
    glm::vec3 drag_projected_mouse = glm::vec3();

   public:
    Renderer();
    void Render();
    void Loop();
    void Debug();

    void Inputs();
    void GlobalInputs();
    void DebugInputs();
    void CameraInputs();

    drw::Mesh<drw::VertexCol> DeclareColorMesh();
    drw::Mesh<drw::VertexTex> DeclareTextureMesh();

    void DrawSystem();

    void DrawCorpse(std::shared_ptr<phy::Corpse> corpse, uint32_t color);
    void DrawCorpseSelected(std::shared_ptr<phy::Corpse> corpse, uint32_t color);
    void DrawConstraint(std::shared_ptr<phy::Constraint> constraint, uint32_t color);

    void DrawCorpseCircle(phy::Circle *circle, uint32_t color);
    void DrawCorpsePolygon(phy::Polygon *polygon, uint32_t color);
    void DrawCorpseCircleSelected(phy::Circle *circle, uint32_t color);
    void DrawCorpsePolygonSelected(phy::Polygon *polygon, uint32_t color);

    void DrawConstraintLink(phy::Link *link, uint32_t color);
    void DrawConstraintSpring(phy::Spring *spring, uint32_t color);
    void DrawConstraintSlider(phy::Slider *slider, uint32_t color);

    void LoadShaders();
    void UpdateCamera();
    void DeclareMeshes();
    void DrawMeshes();

    void addCorpse(phy::Polygon polygon, uint32_t color);
    void addCorpse(phy::Circle circle, uint32_t color);
    std::shared_ptr<phy::Corpse> getCorpse(int index) const;

    void addConstraint(phy::Link link, uint32_t color);
    void addConstraint(phy::Spring spring, uint32_t color);
    void addConstraint(phy::Slider slider, uint32_t color);
    std::shared_ptr<phy::Constraint> getConstraint(int index) const;
};

}  // namespace ctx
#endif