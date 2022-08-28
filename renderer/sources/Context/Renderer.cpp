#include "../../include/Context/Renderer.hpp"

namespace ctx {

Renderer::Renderer() : m_state(ctx::State()), m_overlay(ovl::GuiManager(&m_state)) {
    const std::string title = "Test";
    const std::string sim_title = "Qualeus v" + std::to_string(PROJECT_VERSION_MAJOR) + "." + std::to_string(PROJECT_VERSION_MINOR) + "." + std::to_string(PROJECT_VERSION_REVISION) + " // " + title;

    m_window = Window(1000, 800, sim_title);
    m_state.camera = drw::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f));
}

void Renderer::render() {
    m_window.render();
    m_overlay.setup();

#ifdef __EMSCRIPTEN__
    // EM_JS(int, canvas_get_width, (), { return Module.canvas.width; });
    // EM_JS(int, canvas_get_height, (), { return Module.canvas.height; });
    // EM_JS(void, resizeCanvas, (), { js_resizeCanvas(); });
#endif

    /* Loop until the user closes the window */
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&Loop, 0, 1);
#else

    load_shaders();

    while (m_window.is_open()) { loop(); }
#endif

    m_window.close();
}

void Renderer::loop() {
    m_state.system.step();

    m_window.pre_draw();

    drw::Shapes::reset();

    debug();

    m_overlay.draw_gui();

    update_camera();

    declare_meshes();

    draw_system();

    draw_meshes();

    inputs();

    m_window.draw();
}

void Renderer::declare_meshes() {
    m_base_mesh = declare_color_mesh();
    m_circle_mesh = declare_texture_mesh();
}

void Renderer::draw_meshes() {
    // Circle Mesh => Texture vertex
    drw::Shapes::draw(m_circle_mesh, m_circle_shader);

    // Base Mesh => Colors vertex
    drw::Shapes::draw(m_base_mesh, m_base_shader);
}

drw::Mesh<drw::VertexCol> Renderer::declare_color_mesh() {
    drw::Mesh<drw::VertexCol> mesh = drw::Mesh<drw::VertexCol>();

    mesh.declaration.begin();                                                      // init
    mesh.declaration.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);      // vertex
    mesh.declaration.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);  // color
    mesh.declaration.end();                                                        // stop

    return mesh;
}

drw::Mesh<drw::VertexTex> Renderer::declare_texture_mesh() {
    drw::Mesh<drw::VertexTex> mesh = drw::Mesh<drw::VertexTex>();

    mesh.declaration.begin();                                                      // init
    mesh.declaration.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);      // vertex
    mesh.declaration.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);     // texture
    mesh.declaration.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);  // color
    mesh.declaration.end();                                                        // stop

    return mesh;
}

void Renderer::update_camera() {
    const glm::vec3 cpos = m_state.camera.get_position();
    const glm::vec3 ctrd = m_state.camera.get_towards();

    const bx::Vec3 at = {cpos.x, cpos.y, cpos.z};
    const bx::Vec3 eye = {ctrd.x, ctrd.y, ctrd.z};

    // Set view and projection matrix for view 0.
    float view[16];
    bx::mtxLookAt(view, eye, at);
    m_state.camera.set_view_matrix(view);

    float proj[16];
    bx::mtxProj(proj, m_state.camera.get_fov(), (float)m_window.get_width() / (float)m_window.get_height(), m_state.camera.get_near(), m_state.camera.get_far(), bgfx::getCaps()->homogeneousDepth);
    m_state.camera.set_proj_matrix(proj);

    bgfx::setViewTransform(0, view, proj);
    m_state.camera.set_viewport(glm::vec4(0, 0, (float)m_window.get_width(), (float)m_window.get_height()));

    float mtx[16];
    bx::mtxRotateY(mtx, 0.0f);

    // position x,y,z
    mtx[12] = 0.0f;
    mtx[13] = 0.0f;
    mtx[14] = 0.0f;

    // Set model matrix for rendering.
    bgfx::setTransform(mtx);
}

void Renderer::debug() {
    bgfx::dbgTextClear();
    const bgfx::Stats *stats = bgfx::getStats();

    const glm::vec3 cam_pos = m_state.camera.get_position();
    const glm::vec3 cam_tw = m_state.camera.get_towards();
    const glm::vec4 cam_vp = m_state.camera.get_viewport();
    const glm::mat4 cam_vw = m_state.camera.get_view_matrix();
    const glm::mat4 cam_pr = m_state.camera.get_proj_matrix();
    const glm::vec2 cur_pos = Inputs::mouse_position();
    const glm::vec3 cur_prj = m_state.camera.project_point(glm::vec3(cur_pos.x, cur_pos.y, 0.0f));

    bgfx::dbgTextPrintf(0,
                        0,
                        0x0f,
                        "\x1b[15;8m QUALEUS v%i.%i.%i [%s ] \x1b[0m",  //
                        PROJECT_VERSION_MAJOR,
                        PROJECT_VERSION_MINOR,
                        PROJECT_VERSION_REVISION,                                   //
                        std::string(com::type_name<QUALEUS_PRECISION>()).c_str());  //
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

    switch (m_debug) {
        case 0: bgfx::dbgTextClear(); break;
        case 1: bgfx::setDebug(BGFX_DEBUG_STATS); break;
        case 2: bgfx::setDebug(BGFX_DEBUG_TEXT); break;
        default: break;
    }
}

void Renderer::inputs() {
    Inputs::handle_mouse_position();

    global_inputs();
    debug_inputs();
    camera_inputs();
}

void Renderer::global_inputs() {
    if (Inputs::key_pressed(GLFW_KEY_ESCAPE)) { m_window.close(); }
}

void Renderer::debug_inputs() {
    if (Inputs::key_pressed(GLFW_KEY_F1)) { m_debug = (m_debug + 1) % 3; }
    if (Inputs::key_pressed(GLFW_KEY_A)) {
        const glm::vec2 mouse_pos = Inputs::mouse_position();
        const glm::vec3 projected = m_state.camera.project_point(glm::vec3(mouse_pos.x, mouse_pos.y, 0.0));
        add_corpse(phy::Circle(projected.x, projected.y, 1.0), 0xffffffff);
    }
}

void Renderer::camera_inputs() {
    const float CAMERA_STEP = 0.05f;
    const float CAMERA_ZOOM = 0.25f;
    const glm::vec2 cursor = Inputs::mouse_position();

    if (Inputs::key_down(GLFW_KEY_LEFT)) {
        m_state.camera.set_position(m_state.camera.get_position() + glm::vec3(CAMERA_STEP, 0, 0));
        m_state.camera.set_towards(m_state.camera.get_towards() + glm::vec3(CAMERA_STEP, 0, 0));
    }

    if (Inputs::key_down(GLFW_KEY_RIGHT)) {
        m_state.camera.set_position(m_state.camera.get_position() - glm::vec3(CAMERA_STEP, 0, 0));
        m_state.camera.set_towards(m_state.camera.get_towards() - glm::vec3(CAMERA_STEP, 0, 0));
    }

    if (Inputs::key_down(GLFW_KEY_UP)) {
        m_state.camera.set_position(m_state.camera.get_position() + glm::vec3(0, CAMERA_STEP, 0));
        m_state.camera.set_towards(m_state.camera.get_towards() + glm::vec3(0, CAMERA_STEP, 0));
    }

    if (Inputs::key_down(GLFW_KEY_DOWN)) {
        m_state.camera.set_position(m_state.camera.get_position() - glm::vec3(0, CAMERA_STEP, 0));
        m_state.camera.set_towards(m_state.camera.get_towards() - glm::vec3(0, CAMERA_STEP, 0));
    }

    if (Inputs::key_down(GLFW_KEY_P)) {
        m_state.camera.set_position(m_state.camera.get_position() + glm::vec3(0, 0, CAMERA_ZOOM));
        m_state.camera.set_towards(m_state.camera.get_towards() + glm::vec3(0, 0, CAMERA_ZOOM));
    }

    if (Inputs::key_down(GLFW_KEY_O)) {
        m_state.camera.set_position(m_state.camera.get_position() - glm::vec3(0, 0, CAMERA_ZOOM));
        m_state.camera.set_towards(m_state.camera.get_towards() - glm::vec3(0, 0, CAMERA_ZOOM));
    }

    if (Inputs::mouse_pressed(GLFW_MOUSE_BUTTON_1)) {
        glm::vec3 curr_projected_mouse = m_state.camera.project_point(glm::vec3(cursor.x, cursor.y, 0.0f));
        m_drag_projected_mouse = curr_projected_mouse;

        bool background_pointed = true;
        m_state.corpses_selected = {};  // clear selection

        // Pointed corpse dragging
        for (int i = 0; i < m_state.system.get_corpses_size(); i++) {
            if (m_state.system.get_corpse(i)->pointed({curr_projected_mouse.x, curr_projected_mouse.y})) {
                // Add the pointed corpse to the selection
                int pointed_id = m_state.system.get_corpse(i)->get_id();
                m_state.corpses_selected.push_back(pointed_id);
                background_pointed = false;
                break;
            }
        }

        // If no corpse is pointed, init the camera dragging
        if (background_pointed) {
            m_drag_initial_position = m_state.camera.get_position();
            m_drag_initial_towards = m_state.camera.get_towards();
        }
    }

    const double DRAG_TOGGLE_OFFSET = 1.0;
    if (Inputs::mouse_down(GLFW_MOUSE_BUTTON_1)) {
        glm::vec3 curr_projected_mouse = m_state.camera.project_point(glm::vec3(cursor.x, cursor.y, 0.0f));

        if (m_state.corpses_selected.size() > 0) {
            // Displace all selected corpses
            for (int i = 0; i < m_state.corpses_selected.size(); i++) {
                int id = m_state.corpses_selected[i];

                auto found = m_state.system.get_corpse_by_id(id);

                if (found != nullptr) {
                    found->move({curr_projected_mouse.x, curr_projected_mouse.y});
                    found->stop();
                }
            }
        } else {
            glm::vec2 mouse_diff = Inputs::pressed_mouse_diff(GLFW_MOUSE_BUTTON_1);
            const glm::vec3 diff_projected_mouse = curr_projected_mouse - m_drag_projected_mouse;

            if (std::abs(mouse_diff.x) > DRAG_TOGGLE_OFFSET || std::abs(mouse_diff.y) > DRAG_TOGGLE_OFFSET) {
                m_state.camera.set_position(m_drag_initial_position - diff_projected_mouse);
                m_state.camera.set_towards(m_drag_initial_towards - diff_projected_mouse);
                m_drag_initial_position = m_state.camera.get_position();
                m_drag_initial_towards = m_state.camera.get_towards();
            }
        }
    }

    const double SCROLL_TOGGLE_OFFSET = 0.1;
    if (std::abs(Inputs::mouse_scroll()) > SCROLL_TOGGLE_OFFSET) {
        float scroll = Inputs::mouse_scroll() * CAMERA_ZOOM;

        glm::vec3 diff_toward = m_state.camera.get_towards() - m_state.camera.get_position();
        glm::vec3 zoom_position = m_state.camera.get_position();

        zoom_position.z = std::clamp(zoom_position.z * (1.0f - scroll), m_state.camera.get_near(), m_state.camera.get_far() - diff_toward.z - 1.0f);

        m_state.camera.set_position(zoom_position);
        m_state.camera.set_towards(zoom_position + diff_toward);
    }
}

void Renderer::load_shaders() {
    const bgfx::Memory *base_vs = drw::Shader::get_base_vs_shader();
    const bgfx::Memory *base_fs = drw::Shader::get_base_fs_shader();

    m_base_shader = drw::Shader::create_program("base", base_vs, base_fs);

    const bgfx::Memory *circle_vs = drw::Shader::get_circle_vs_shader();
    const bgfx::Memory *circle_fs = drw::Shader::get_circle_fs_shader();

    m_circle_shader = drw::Shader::create_program("circle", circle_vs, circle_fs);
}

void Renderer::add_corpse(phy::Polygon polygon, uint32_t color) {
    m_state.corpses_colors[polygon.get_id()] = color;
    m_state.system.add_corpse(polygon);
}

void Renderer::add_corpse(phy::Circle circle, uint32_t color) {
    m_state.corpses_colors[circle.get_id()] = color;
    m_state.system.add_corpse(circle);
}

std::shared_ptr<phy::Corpse> Renderer::get_corpse(int index) const {
    return m_state.system.get_corpse(index);
}

void Renderer::add_constraint(phy::Link link, uint32_t color) {
    m_state.constraints_colors[link.get_id()] = color;
    m_state.system.add_constraint(link);
}

std::shared_ptr<phy::Constraint> Renderer::get_constraint(int index) const {
    return m_state.system.get_constraint(index);
}

void Renderer::draw_system() {
    for (int i = 0; i < m_state.system.get_corpses_size(); i++) {
        int corpse_id = m_state.system.get_corpse(i)->get_id();
        draw_corpse(m_state.system.get_corpse(i), m_state.corpses_colors[corpse_id]);
    }

    for (int i = 0; i < m_state.system.get_constraints_size(); i++) {
        int constraint_id = m_state.system.get_constraint(i)->get_id();
        draw_constraint(m_state.system.get_constraint(i), m_state.constraints_colors[constraint_id]);
    }

    for (int i = 0; i < m_state.corpses_selected.size(); i++) {
        int id = m_state.corpses_selected[i];
        draw_corpse_selected(m_state.system.get_corpse_by_id(id), 0xffffffff);
    }
}

void Renderer::draw_corpse(std::shared_ptr<phy::Corpse> corpse, uint32_t color) {
    if (phy::Circle *circle = dynamic_cast<phy::Circle *>(corpse.get())) {
        draw_corpse_circle(circle, color);

    } else if (phy::Polygon *polygon = dynamic_cast<phy::Polygon *>(corpse.get())) {
        draw_corpse_polygon(polygon, color);
    }
}

void Renderer::draw_corpse_selected(std::shared_ptr<phy::Corpse> corpse, uint32_t color) {
    if (phy::Circle *circle = dynamic_cast<phy::Circle *>(corpse.get())) {
        draw_corpse_circle_selected(circle, color);

    } else if (phy::Polygon *polygon = dynamic_cast<phy::Polygon *>(corpse.get())) {
        draw_corpse_polygon_selected(polygon, color);
    }
}

void Renderer::draw_constraint(std::shared_ptr<phy::Constraint> constraint, uint32_t color) {
    if (phy::Link *link = dynamic_cast<phy::Link *>(constraint.get())) { draw_constraint_link(link, color); }
}

void Renderer::draw_corpse_circle(phy::Circle *circle, uint32_t color) {
    const glm::vec3 center = glm::vec3(circle->get_pos_x(), circle->get_pos_y(), 0);
    drw::Shapes::draw_quad(m_circle_mesh, center, circle->get_size() / 2.0f, color);
}

void Renderer::draw_corpse_polygon(phy::Polygon *polygon, uint32_t color) {
    std::vector<gmt::VerticesI> polygon_triangles = polygon->get_polygons();

    for (int i = 0; i < polygon_triangles.size(); i++) {
        gmt::VerticesI triangle_vertices = polygon_triangles[i];
        std::vector<glm::vec3> polygon_points = {};

        for (int j = 0; j < triangle_vertices.vertices.size(); j++) {
            const std::shared_ptr<gmt::VectorI> vertice = triangle_vertices.vertices[j];
            polygon_points.push_back(glm::vec3(vertice->x, vertice->y, 0));
        }

        drw::Shapes::draw_polygon(m_base_mesh, polygon_points, color);
    }
}

void Renderer::draw_corpse_circle_selected(phy::Circle *circle, uint32_t color) {
    const glm::vec3 center = glm::vec3(circle->get_pos_x(), circle->get_pos_y(), 0);
    drw::Shapes::draw_circle_fan_outlined(m_base_mesh, center, circle->get_size() / 2.0f, 0.1f, color);
}

void Renderer::draw_corpse_polygon_selected(phy::Polygon *polygon, uint32_t color) {
    std::vector<gmt::VerticesI> polygon_triangles = polygon->get_polygons();

    for (int i = 0; i < polygon_triangles.size(); i++) {
        gmt::VerticesI triangle_vertices = polygon_triangles[i];
        std::vector<glm::vec3> polygon_points = {};

        for (int j = 0; j < triangle_vertices.vertices.size(); j++) {
            const std::shared_ptr<gmt::VectorI> vertice = triangle_vertices.vertices[j];
            polygon_points.push_back(glm::vec3(vertice->x, vertice->y, 0));
        }

        drw::Shapes::draw_polygon_outlined(m_base_mesh, polygon_points, 0.1f, color);
    }
}

void Renderer::draw_constraint_link(phy::Link *link, uint32_t color) { }

}  // namespace ctx