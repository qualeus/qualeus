#include "../../include/Context/Renderer.hpp"

namespace ctx {

Renderer::Renderer() : state(ctx::State()), overlay(ovl::GuiManager(&this->state)) {
    const std::string title = "Test";
    const std::string sim_title = "Qualeus v" + std::to_string(PROJECT_VERSION_MAJOR) + "."  //
                                  + std::to_string(PROJECT_VERSION_MINOR) + "."              //
                                  + std::to_string(PROJECT_VERSION_REVISION)                 //
                                  + " // " + title;                                          //

    this->window = Window(1000, 800, sim_title);
    this->state.camera = drw::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f));
}

void Renderer::Render() {
    this->window.Render();
    this->overlay.Setup();

#ifdef __EMSCRIPTEN__
    // EM_JS(int, canvas_get_width, (), { return Module.canvas.width; });
    // EM_JS(int, canvas_get_height, (), { return Module.canvas.height; });
    // EM_JS(void, resizeCanvas, (), { js_resizeCanvas(); });
#endif

    /* Loop until the user closes the window */
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&this->Loop, 0, 1);
#else

    this->LoadShaders();

    while (this->window.isOpen()) { this->Loop(); }
#endif

    this->window.Close();
}

void Renderer::Loop() {
    this->state.system.Step();

    this->window.PreDraw();

    drw::Shapes::Reset();

    this->Debug();

    this->overlay.DrawGui();

    this->UpdateCamera();

    this->DeclareMeshes();

    this->DrawSystem();

    this->DrawMeshes();

    this->Inputs();

    this->window.Draw();
}

void Renderer::DeclareMeshes() {
    this->base_mesh = this->DeclareColorMesh();
    this->circle_mesh = this->DeclareTextureMesh();
}

void Renderer::DrawMeshes() {
    // Circle Mesh => Texture vertex
    drw::Shapes::Draw(this->circle_mesh, this->circle_shader);

    // Base Mesh => Colors vertex
    drw::Shapes::Draw(this->base_mesh, this->base_shader);
}

drw::Mesh<drw::VertexCol> Renderer::DeclareColorMesh() {
    drw::Mesh<drw::VertexCol> mesh = drw::Mesh<drw::VertexCol>();

    mesh.declaration.begin();                                                      // init
    mesh.declaration.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);      // vertex
    mesh.declaration.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);  // color
    mesh.declaration.end();                                                        // stop

    return mesh;
}

drw::Mesh<drw::VertexTex> Renderer::DeclareTextureMesh() {
    drw::Mesh<drw::VertexTex> mesh = drw::Mesh<drw::VertexTex>();

    mesh.declaration.begin();                                                      // init
    mesh.declaration.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);      // vertex
    mesh.declaration.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);     // texture
    mesh.declaration.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);  // color
    mesh.declaration.end();                                                        // stop

    return mesh;
}

void Renderer::UpdateCamera() {
    const glm::vec3 cpos = this->state.camera.get_position();
    const glm::vec3 ctrd = this->state.camera.get_towards();

    const bx::Vec3 at = {cpos.x, cpos.y, cpos.z};
    const bx::Vec3 eye = {ctrd.x, ctrd.y, ctrd.z};

    // Set view and projection matrix for view 0.
    float view[16];
    bx::mtxLookAt(view, eye, at);
    this->state.camera.set_view_matrix(view);

    float proj[16];
    bx::mtxProj(proj, this->state.camera.get_fov(), (float)this->window.get_width() / (float)this->window.get_height(), this->state.camera.get_near(), this->state.camera.get_far(),
                bgfx::getCaps()->homogeneousDepth);
    this->state.camera.set_proj_matrix(proj);

    bgfx::setViewTransform(0, view, proj);
    this->state.camera.set_viewport(glm::vec4(0, 0, (float)this->window.get_width(), (float)this->window.get_height()));

    float mtx[16];
    bx::mtxRotateY(mtx, 0.0f);

    // position x,y,z
    mtx[12] = 0.0f;
    mtx[13] = 0.0f;
    mtx[14] = 0.0f;

    // Set model matrix for rendering.
    bgfx::setTransform(mtx);
}

void Renderer::Debug() {
    bgfx::dbgTextClear();
    const bgfx::Stats *stats = bgfx::getStats();

    const glm::vec3 cam_pos = this->state.camera.get_position();
    const glm::vec3 cam_tw = this->state.camera.get_towards();
    const glm::vec4 cam_vp = this->state.camera.get_viewport();
    const glm::mat4 cam_vw = this->state.camera.get_view_matrix();
    const glm::mat4 cam_pr = this->state.camera.get_proj_matrix();
    const glm::vec2 cur_pos = Inputs::MousePosition();
    const glm::vec3 cur_prj = this->state.camera.projectPoint(glm::vec3(cur_pos.x, cur_pos.y, 0.0f));

    bgfx::dbgTextPrintf(0, 0, 0x0f, "\x1b[15;8m QUALEUS v%i.%i.%i [%s ] \x1b[0m",                //
                        PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_REVISION,  //
                        std::string(com::type_name<QUALEUS_PRECISION>()).c_str());               //
    bgfx::dbgTextPrintf(0, 1, 0x0f, "\x1b[15;8m Camera: position (%f; %f; %f)\x1b[0m", cam_pos.x, cam_pos.y, cam_pos.z);
    bgfx::dbgTextPrintf(0, 2, 0x0f, "\x1b[15;8m         towards (%f; %f; %f)\x1b[0m", cam_tw.x, cam_tw.y, cam_tw.z);

    bgfx::dbgTextPrintf(0, 3, 0x0f, "\x1b[15;8m         viewport (%f; %f; %f; %f)\x1b[0m", cam_vp[0], cam_vp[1], cam_vp[2], cam_vp[3]);

    bgfx::dbgTextPrintf(0, 5, 0x0f, "\x1b[15;8m         view l1 [%f; %f; %f; %f]", cam_vw[0][0], cam_vw[0][1], cam_vw[0][2], cam_vw[0][3]);
    bgfx::dbgTextPrintf(0, 6, 0x0f, "\x1b[15;8m         view l2 [%f; %f; %f; %f]", cam_vw[1][0], cam_vw[1][1], cam_vw[1][2], cam_vw[1][3]);
    bgfx::dbgTextPrintf(0, 7, 0x0f, "\x1b[15;8m         view l3 [%f; %f; %f; %f]", cam_vw[2][0], cam_vw[2][1], cam_vw[2][2], cam_vw[2][3]);
    bgfx::dbgTextPrintf(0, 8, 0x0f, "\x1b[15;8m         view l4 [%f; %f; %f; %f]", cam_vw[3][0], cam_vw[3][1], cam_vw[3][2], cam_vw[3][3]);

    bgfx::dbgTextPrintf(0, 10, 0x0f, "\x1b[15;8m         proj l1 [%f; %f; %f; %f]", cam_pr[0][0], cam_pr[0][1], cam_pr[0][2], cam_pr[0][3]);
    bgfx::dbgTextPrintf(0, 11, 0x0f, "\x1b[15;8m         proj l2 [%f; %f; %f; %f]", cam_pr[1][0], cam_pr[1][1], cam_pr[1][2], cam_pr[1][3]);
    bgfx::dbgTextPrintf(0, 12, 0x0f, "\x1b[15;8m         proj l3 [%f; %f; %f; %f]", cam_pr[2][0], cam_pr[2][1], cam_pr[2][2], cam_pr[2][3]);
    bgfx::dbgTextPrintf(0, 13, 0x0f, "\x1b[15;8m         proj l4 [%f; %f; %f; %f]", cam_pr[3][0], cam_pr[3][1], cam_pr[3][2], cam_pr[3][3]);

    bgfx::dbgTextPrintf(0, 15, 0x0f, "\x1b[15;8m Cursor: position (%f; %f)\x1b[0m", cur_pos.x, cur_pos.y);
    bgfx::dbgTextPrintf(0, 16, 0x0f, "\x1b[15;8m         projection (%f; %f; %f)\x1b[0m", cur_prj.x, cur_prj.y, cur_prj.z);

    switch (debug) {
        case 0: bgfx::dbgTextClear(); break;
        case 1: bgfx::setDebug(BGFX_DEBUG_STATS); break;
        case 2: bgfx::setDebug(BGFX_DEBUG_TEXT); break;
        default: break;
    }
}

void Renderer::Inputs() {
    Inputs::HandleMousePosition();

    GlobalInputs();
    DebugInputs();
    CameraInputs();
}

void Renderer::GlobalInputs() {
    if (Inputs::KeyPressed(GLFW_KEY_ESCAPE)) { this->window.Close(); }
}

void Renderer::DebugInputs() {
    if (Inputs::KeyPressed(GLFW_KEY_F1)) { debug = (debug + 1) % 3; }
    if (Inputs::KeyPressed(GLFW_KEY_A)) {
        const glm::vec2 mouse_pos = Inputs::MousePosition();
        const glm::vec3 projected = this->state.camera.projectPoint(glm::vec3(mouse_pos.x, mouse_pos.y, 0.0));
        addCorpse(phy::Circle(projected.x, projected.y, 1.0), 0xffffffff);
    }
}

void Renderer::CameraInputs() {
    const float CAMERA_STEP = 0.05f;
    const float CAMERA_ZOOM = 0.25f;
    const glm::vec2 cursor = Inputs::MousePosition();

    if (Inputs::KeyDown(GLFW_KEY_LEFT)) {
        this->state.camera.set_position(this->state.camera.get_position() + glm::vec3(CAMERA_STEP, 0, 0));
        this->state.camera.set_towards(this->state.camera.get_towards() + glm::vec3(CAMERA_STEP, 0, 0));
    }

    if (Inputs::KeyDown(GLFW_KEY_RIGHT)) {
        this->state.camera.set_position(this->state.camera.get_position() - glm::vec3(CAMERA_STEP, 0, 0));
        this->state.camera.set_towards(this->state.camera.get_towards() - glm::vec3(CAMERA_STEP, 0, 0));
    }

    if (Inputs::KeyDown(GLFW_KEY_UP)) {
        this->state.camera.set_position(this->state.camera.get_position() + glm::vec3(0, CAMERA_STEP, 0));
        this->state.camera.set_towards(this->state.camera.get_towards() + glm::vec3(0, CAMERA_STEP, 0));
    }

    if (Inputs::KeyDown(GLFW_KEY_DOWN)) {
        this->state.camera.set_position(this->state.camera.get_position() - glm::vec3(0, CAMERA_STEP, 0));
        this->state.camera.set_towards(this->state.camera.get_towards() - glm::vec3(0, CAMERA_STEP, 0));
    }

    if (Inputs::KeyDown(GLFW_KEY_P)) {
        this->state.camera.set_position(this->state.camera.get_position() + glm::vec3(0, 0, CAMERA_ZOOM));
        this->state.camera.set_towards(this->state.camera.get_towards() + glm::vec3(0, 0, CAMERA_ZOOM));
    }

    if (Inputs::KeyDown(GLFW_KEY_O)) {
        this->state.camera.set_position(this->state.camera.get_position() - glm::vec3(0, 0, CAMERA_ZOOM));
        this->state.camera.set_towards(this->state.camera.get_towards() - glm::vec3(0, 0, CAMERA_ZOOM));
    }

    if (Inputs::MousePressed(GLFW_MOUSE_BUTTON_1)) {
        glm::vec3 curr_projected_mouse = this->state.camera.projectPoint(glm::vec3(cursor.x, cursor.y, 0.0f));
        this->drag_projected_mouse = curr_projected_mouse;

        bool background_pointed = true;
        this->state.corpses_selected = {};  // clear selection

        // Pointed corpse dragging
        for (int i = 0; i < this->state.system.get_corpses_size(); i++) {
            if (this->state.system.get_corpse(i)->Pointed({curr_projected_mouse.x, curr_projected_mouse.y})) {
                // Add the pointed corpse to the selection
                int pointed_id = this->state.system.get_corpse(i)->get_id();
                this->state.corpses_selected.push_back(pointed_id);
                background_pointed = false;
                break;
            }
        }

        // If no corpse is pointed, init the camera dragging
        if (background_pointed) {
            this->drag_initial_position = this->state.camera.get_position();
            this->drag_initial_towards = this->state.camera.get_towards();
        }
    }

    const double DRAG_TOGGLE_OFFSET = 1.0;
    if (Inputs::MouseDown(GLFW_MOUSE_BUTTON_1)) {
        glm::vec3 curr_projected_mouse = this->state.camera.projectPoint(glm::vec3(cursor.x, cursor.y, 0.0f));

        if (this->state.corpses_selected.size() > 0) {
            // Displace all selected corpses
            for (int i = 0; i < this->state.corpses_selected.size(); i++) {
                int id = this->state.corpses_selected[i];

                auto found = this->state.system.get_corpse_by_id(id);

                if (found != nullptr) {
                    found->Move({curr_projected_mouse.x, curr_projected_mouse.y});
                    found->Stop();
                }
            }
        } else {
            glm::vec2 mouse_diff = Inputs::pressed_mouse_diff[GLFW_MOUSE_BUTTON_1];
            const glm::vec3 diff_projected_mouse = curr_projected_mouse - this->drag_projected_mouse;

            if (std::abs(mouse_diff.x) > DRAG_TOGGLE_OFFSET || std::abs(mouse_diff.y) > DRAG_TOGGLE_OFFSET) {
                this->state.camera.set_position(this->drag_initial_position - diff_projected_mouse);
                this->state.camera.set_towards(this->drag_initial_towards - diff_projected_mouse);
                this->drag_initial_position = this->state.camera.get_position();
                this->drag_initial_towards = this->state.camera.get_towards();
            }
        }
    }

    const double SCROLL_TOGGLE_OFFSET = 0.1;
    if (std::abs(Inputs::MouseScroll()) > SCROLL_TOGGLE_OFFSET) {
        float scroll = Inputs::MouseScroll() * CAMERA_ZOOM;

        glm::vec3 diff_toward = this->state.camera.get_towards() - this->state.camera.get_position();
        glm::vec3 zoom_position = this->state.camera.get_position();

        zoom_position.z = std::clamp(zoom_position.z * (1.0f - scroll), this->state.camera.get_near(), this->state.camera.get_far() - diff_toward.z - 1.0f);

        this->state.camera.set_position(zoom_position);
        this->state.camera.set_towards(zoom_position + diff_toward);
    }
}

void Renderer::LoadShaders() {
    const bgfx::Memory *base_vs = drw::Shader::get_base_vs_shader();
    const bgfx::Memory *base_fs = drw::Shader::get_base_fs_shader();

    this->base_shader = drw::Shader::create_program("base", base_vs, base_fs);

    const bgfx::Memory *circle_vs = drw::Shader::get_circle_vs_shader();
    const bgfx::Memory *circle_fs = drw::Shader::get_circle_fs_shader();

    this->circle_shader = drw::Shader::create_program("circle", circle_vs, circle_fs);
}

void Renderer::addCorpse(phy::Polygon polygon, uint32_t color) {
    this->state.corpses_colors[polygon.get_id()] = color;
    this->state.system.addCorpse(polygon);
}

void Renderer::addCorpse(phy::Circle circle, uint32_t color) {
    this->state.corpses_colors[circle.get_id()] = color;
    this->state.system.addCorpse(circle);
}

std::shared_ptr<phy::Corpse> Renderer::getCorpse(int index) const { return this->state.system.get_corpse(index); }

void Renderer::addConstraint(phy::Link link, uint32_t color) {
    this->state.constraints_colors[link.get_id()] = color;
    this->state.system.addConstraint(link);
}

void Renderer::addConstraint(phy::Spring spring, uint32_t color) {
    this->state.constraints_colors[spring.get_id()] = color;
    this->state.system.addConstraint(spring);
}

void Renderer::addConstraint(phy::Slider slider, uint32_t color) {
    this->state.constraints_colors[slider.get_id()] = color;
    this->state.system.addConstraint(slider);
}

std::shared_ptr<phy::Constraint> Renderer::getConstraint(int index) const { return this->state.system.get_constraint(index); }

void Renderer::DrawSystem() {
    for (int i = 0; i < this->state.system.get_corpses_size(); i++) {
        int corpse_id = this->state.system.get_corpse(i)->get_id();
        DrawCorpse(this->state.system.get_corpse(i), this->state.corpses_colors[corpse_id]);
    }

    for (int i = 0; i < this->state.system.get_constraints_size(); i++) {
        int constraint_id = this->state.system.get_constraint(i)->get_id();
        DrawConstraint(this->state.system.get_constraint(i), this->state.constraints_colors[constraint_id]);
    }

    for (int i = 0; i < this->state.corpses_selected.size(); i++) {
        int id = this->state.corpses_selected[i];
        DrawCorpseSelected(this->state.system.get_corpse_by_id(id), 0xffffffff);
    }
}

void Renderer::DrawCorpse(std::shared_ptr<phy::Corpse> corpse, uint32_t color) {
    if (phy::Circle *circle = dynamic_cast<phy::Circle *>(corpse.get())) {
        DrawCorpseCircle(circle, color);

    } else if (phy::Polygon *polygon = dynamic_cast<phy::Polygon *>(corpse.get())) {
        DrawCorpsePolygon(polygon, color);
    }
}

void Renderer::DrawCorpseSelected(std::shared_ptr<phy::Corpse> corpse, uint32_t color) {
    if (phy::Circle *circle = dynamic_cast<phy::Circle *>(corpse.get())) {
        DrawCorpseCircleSelected(circle, color);

    } else if (phy::Polygon *polygon = dynamic_cast<phy::Polygon *>(corpse.get())) {
        DrawCorpsePolygonSelected(polygon, color);
    }
}

void Renderer::DrawConstraint(std::shared_ptr<phy::Constraint> constraint, uint32_t color) {
    if (phy::Link *link = dynamic_cast<phy::Link *>(constraint.get())) {
        DrawConstraintLink(link, color);
    } else if (phy::Spring *spring = dynamic_cast<phy::Spring *>(constraint.get())) {
        DrawConstraintSpring(spring, color);
    } else if (phy::Slider *slider = dynamic_cast<phy::Slider *>(constraint.get())) {
        DrawConstraintSlider(slider, color);
    }
}

void Renderer::DrawCorpseCircle(phy::Circle *circle, uint32_t color) {
    const glm::vec3 center = glm::vec3(circle->get_pos_x(), circle->get_pos_y(), 0);
    drw::Shapes::DrawQuad(this->circle_mesh, center, circle->get_size() / 2.0f, color);
}

void Renderer::DrawCorpsePolygon(phy::Polygon *polygon, uint32_t color) {
    std::vector<gmt::VerticesI> polygon_triangles = polygon->get_polygons();

    for (int i = 0; i < polygon_triangles.size(); i++) {
        gmt::VerticesI triangle_vertices = polygon_triangles[i];
        std::vector<glm::vec3> polygon_points = {};

        for (int j = 0; j < triangle_vertices.vertices.size(); j++) {
            const std::shared_ptr<gmt::VectorI> vertice = triangle_vertices.vertices[j];
            polygon_points.push_back(glm::vec3(vertice->x, vertice->y, 0));
        }

        drw::Shapes::DrawPolygon(this->base_mesh, polygon_points, color);
    }
}

void Renderer::DrawCorpseCircleSelected(phy::Circle *circle, uint32_t color) {
    const glm::vec3 center = glm::vec3(circle->get_pos_x(), circle->get_pos_y(), 0);
    drw::Shapes::DrawCircleFanOutlined(this->base_mesh, center, circle->get_size() / 2.0f, 0.1f, color);
}

void Renderer::DrawCorpsePolygonSelected(phy::Polygon *polygon, uint32_t color) {
    std::vector<gmt::VerticesI> polygon_triangles = polygon->get_polygons();

    for (int i = 0; i < polygon_triangles.size(); i++) {
        gmt::VerticesI triangle_vertices = polygon_triangles[i];
        std::vector<glm::vec3> polygon_points = {};

        for (int j = 0; j < triangle_vertices.vertices.size(); j++) {
            const std::shared_ptr<gmt::VectorI> vertice = triangle_vertices.vertices[j];
            polygon_points.push_back(glm::vec3(vertice->x, vertice->y, 0));
        }

        drw::Shapes::DrawPolygonOutlined(this->base_mesh, polygon_points, 0.1f, color);
    }
}

void Renderer::DrawConstraintLink(phy::Link *link, uint32_t color) {}
void Renderer::DrawConstraintSpring(phy::Spring *spring, uint32_t color) {}
void Renderer::DrawConstraintSlider(phy::Slider *slider, uint32_t color) {}

}  // namespace ctx