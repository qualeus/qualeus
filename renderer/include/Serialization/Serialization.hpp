#ifndef Serialization_HPP
#define Serialization_HPP

// objects
#include <Constraints/Constraint.hpp>
#include <Constraints/Link.hpp>
#include <Corpses/Circle.hpp>
#include <Corpses/Corpse.hpp>
#include <Corpses/Polygon.hpp>
#include <Geometry/Bounds.hpp>
#include <Geometry/Vector2.hpp>
#include <Geometry/Vertices2.hpp>
#include <Structures/System.hpp>

#include "../Context/State.hpp"

// serialization
#include <cereal/access.hpp>
#include <cereal/details/traits.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

// inheritances declarations
CEREAL_REGISTER_TYPE(phy::Corpse)
CEREAL_REGISTER_TYPE(phy::Circle)
CEREAL_REGISTER_TYPE(phy::Polygon)
CEREAL_REGISTER_POLYMORPHIC_RELATION(phy::Corpse, phy::Circle)
CEREAL_REGISTER_POLYMORPHIC_RELATION(phy::Corpse, phy::Polygon)

CEREAL_REGISTER_TYPE(phy::Constraint)
CEREAL_REGISTER_TYPE(phy::Link)
CEREAL_REGISTER_POLYMORPHIC_RELATION(phy::Constraint, phy::Link)

namespace cereal {

template <class Archive>
void save(Archive& archive, const ctx::State& state) {
    archive(cereal::make_nvp<phy::System>("system", state.system),                                                // param system
            cereal::make_nvp<std::unordered_map<int, uint32_t>>("corpses_colors", state.corpses_colors),          // param corpses_colors
            cereal::make_nvp<std::unordered_map<int, uint32_t>>("constraints_colors", state.constraints_colors),  // param constraints_colors
            cereal::make_nvp<bool>("paused", state.paused),                                                       // param paused
            cereal::make_nvp<std::unordered_map<std::string, bool>>("show_gui", state.show_gui),                  // param show_gui
            cereal::make_nvp<std::unordered_map<std::string, bool>>("show_debug", state.show_debug),              // param show_debug
            cereal::make_nvp<std::unordered_map<std::string, bool>>("post_process", state.post_process)           // param post_process
    );
}

template <class Archive>
void load(Archive& archive, ctx::State& state) {
    phy::System system;
    std::unordered_map<int, uint32_t> corpses_colors;
    std::unordered_map<int, uint32_t> constraints_colors;
    bool paused;
    std::unordered_map<std::string, bool> show_gui;
    std::unordered_map<std::string, bool> show_debug;
    std::unordered_map<std::string, bool> post_process;

    archive(cereal::make_nvp<phy::System>("system", system),                                                // param system
            cereal::make_nvp<std::unordered_map<int, uint32_t>>("corpses_colors", corpses_colors),          // param corpses_colors
            cereal::make_nvp<std::unordered_map<int, uint32_t>>("constraints_colors", constraints_colors),  // param constraints_colors
            cereal::make_nvp<bool>("paused", state.paused),                                                 // param paused
            cereal::make_nvp<std::unordered_map<std::string, bool>>("show_gui", state.show_gui),            // param show_gui
            cereal::make_nvp<std::unordered_map<std::string, bool>>("show_debug", state.show_debug),        // param show_debug
            cereal::make_nvp<std::unordered_map<std::string, bool>>("post_process", state.post_process)     // param post_process
    );

    state.system = system;
    state.corpses_colors = corpses_colors;
    state.constraints_colors = constraints_colors;
    state.paused = paused;
    state.show_gui = show_gui;
    state.show_debug = show_debug;
    state.post_process = post_process;
}

template <class Archive>
void save(Archive& archive, const phy::System& system) {
    std::vector<std::shared_ptr<phy::Corpse>> corpses = system.get_corpses();

    std::vector<std::shared_ptr<phy::Constraint>> constraints = system.get_constraints();
    gmt::BoundsI limits = system.get_limits();
    bool gravity = system.get_gravity();
    bool enable_limits = system.get_enable_limits();
    gmt::UnitI LS = system.get_ls();
    gmt::UnitI G = system.get_g();
    gmt::UnitI force_x = system.get_force_x();
    gmt::UnitI force_y = system.get_force_y();
    gmt::UnitI dt = system.get_dt();
    double t = system.get_t();
    int collision_accuracy = system.get_collision_accuracy();
    int constraint_accuracy = system.get_constraint_accuracy();

    archive(cereal::make_nvp<std::vector<std::shared_ptr<phy::Corpse>>>("corpses", corpses),              // param corpses
            cereal::make_nvp<std::vector<std::shared_ptr<phy::Constraint>>>("constraints", constraints),  // param constraints
            cereal::make_nvp<gmt::BoundsI>("limits", limits),                                             // param limits
            cereal::make_nvp<bool>("gravity", gravity),                                                   // param gravity
            cereal::make_nvp<bool>("enable_limits", enable_limits),                                       // param enable_limits
            cereal::make_nvp<gmt::UnitI>("LS", LS),                                                       // param LS
            cereal::make_nvp<gmt::UnitI>("G", G),                                                         // param G
            cereal::make_nvp<gmt::UnitI>("force_x", force_x),                                             // param force_x
            cereal::make_nvp<gmt::UnitI>("force_y", force_y),                                             // param force_y
            cereal::make_nvp<gmt::UnitI>("dt", dt),                                                       // param dt
            cereal::make_nvp<double>("t", t),                                                             // param t
            cereal::make_nvp<int>("collision_accuracy", collision_accuracy),                              // param collision_accuracy
            cereal::make_nvp<int>("constraint_accuracy", constraint_accuracy)                             // param constraint_accuracy
    );
}

template <class Archive>
void load(Archive& archive, phy::System& system) {
    std::vector<std::shared_ptr<phy::Corpse>> corpses;
    std::vector<std::shared_ptr<phy::Constraint>> constraints;
    gmt::BoundsI limits;
    bool gravity;
    bool enable_limits;
    gmt::UnitI LS;
    gmt::UnitI G;
    gmt::UnitI force_x;
    gmt::UnitI force_y;
    gmt::UnitI dt;
    double t;
    int collision_accuracy;
    int constraint_accuracy;

    archive(cereal::make_nvp<std::vector<std::shared_ptr<phy::Corpse>>>("corpses", corpses),              // param corpses
            cereal::make_nvp<std::vector<std::shared_ptr<phy::Constraint>>>("constraints", constraints),  // param constraints
            cereal::make_nvp<gmt::BoundsI>("limits", limits),                                             // param limits
            cereal::make_nvp<bool>("gravity", gravity),                                                   // param gravity
            cereal::make_nvp<bool>("enable_limits", enable_limits),                                       // param enable_limits
            cereal::make_nvp<gmt::UnitI>("LS", LS),                                                       // param LS
            cereal::make_nvp<gmt::UnitI>("G", G),                                                         // param G
            cereal::make_nvp<gmt::UnitI>("force_x", force_x),                                             // param force_x
            cereal::make_nvp<gmt::UnitI>("force_y", force_y),                                             // param force_y
            cereal::make_nvp<gmt::UnitI>("dt", dt),                                                       // param dt
            cereal::make_nvp<double>("t", t),                                                             // param t
            cereal::make_nvp<int>("collision_accuracy", collision_accuracy),                              // param collision_accuracy
            cereal::make_nvp<int>("constraint_accuracy", constraint_accuracy)                             // param constraint_accuracy
    );

    for (int i = 0; i < corpses.size(); i++) {
        system.add_corpse(corpses[i]);  // Check for shrd_ptr conversion type !
    }

    for (int i = 0; i < constraints.size(); i++) {
        system.add_constraint(constraints[i]);  // Check for shrd_ptr conversion type !
    }

    system.set_limits(limits);
    system.set_gravity(gravity);
    system.set_enable_limits(enable_limits);
    system.set_ls(LS);
    system.set_g(G);
    system.set_force_x(force_x);
    system.set_force_y(force_y);
    system.set_dt(dt);
    system.set_t(t);
    system.set_collision_accuracy(collision_accuracy);
    system.set_constraint_accuracy(constraint_accuracy);
}

template <class Archive>
void save(Archive& archive, const phy::Corpse& corpse) {
    bool fixed = corpse.get_fixed();
    bool tied = corpse.get_tied();
    bool etherial = corpse.get_etherial();
    gmt::UnitI friction = corpse.get_friction();
    gmt::UnitI mass = corpse.get_mass();
    gmt::UnitI damping = corpse.get_damping();
    gmt::VectorI current_pos = corpse.get_pos();
    gmt::VectorI last_pos = corpse.get_last_pos();
    gmt::VectorI propulsor = corpse.get_propulsor();
    gmt::UnitI current_rotation = corpse.get_rotation();
    gmt::UnitI last_rotation = corpse.get_last_rotation();
    gmt::UnitI motor = corpse.get_motor();

    archive(cereal::make_nvp<bool>("fixed", fixed),                              // param fixed
            cereal::make_nvp<bool>("tied", tied),                                // param tied
            cereal::make_nvp<bool>("etherial", etherial),                        // param etherial
            cereal::make_nvp<gmt::UnitI>("friction", friction),                  // param friction
            cereal::make_nvp<gmt::UnitI>("mass", mass),                          // param mass
            cereal::make_nvp<gmt::UnitI>("damping", damping),                    // param damping
            cereal::make_nvp<gmt::VectorI>("current_pos", current_pos),          // param current_pos
            cereal::make_nvp<gmt::VectorI>("last_pos", last_pos),                // param last_pos
            cereal::make_nvp<gmt::VectorI>("propulsor", propulsor),              // param propulsor
            cereal::make_nvp<gmt::UnitI>("current_rotation", current_rotation),  // param current_rotation
            cereal::make_nvp<gmt::UnitI>("last_rotation", last_rotation),        // param last_rotation
            cereal::make_nvp<gmt::UnitI>("motor", motor)                         // param motor
    );
}

template <class Archive>
void load(Archive& archive, phy::Corpse& corpse) {
    bool fixed;
    bool tied;
    bool etherial;
    gmt::UnitI friction;
    gmt::UnitI mass;
    gmt::UnitI damping;
    gmt::VectorI current_pos;
    gmt::VectorI last_pos;
    gmt::VectorI propulsor;
    gmt::UnitI current_rotation;
    gmt::UnitI last_rotation;
    gmt::UnitI motor;

    archive(cereal::make_nvp<bool>("fixed", fixed),                              // param fixed
            cereal::make_nvp<bool>("tied", tied),                                // param tied
            cereal::make_nvp<bool>("etherial", etherial),                        // param etherial
            cereal::make_nvp<gmt::UnitI>("friction", friction),                  // param friction
            cereal::make_nvp<gmt::UnitI>("mass", mass),                          // param mass
            cereal::make_nvp<gmt::UnitI>("damping", damping),                    // param damping
            cereal::make_nvp<gmt::VectorI>("current_pos", current_pos),          // param current_pos
            cereal::make_nvp<gmt::VectorI>("last_pos", last_pos),                // param last_pos
            cereal::make_nvp<gmt::VectorI>("propulsor", propulsor),              // param propulsor
            cereal::make_nvp<gmt::UnitI>("current_rotation", current_rotation),  // param current_rotation
            cereal::make_nvp<gmt::UnitI>("last_rotation", last_rotation),        // param last_rotation
            cereal::make_nvp<gmt::UnitI>("motor", motor)                         // param motor
    );

    corpse.set_fixed(fixed);
    corpse.set_tied(tied);
    corpse.set_etherial(etherial);
    corpse.set_friction(friction);
    corpse.set_mass(mass);
    corpse.set_damping(damping);
    corpse.set_pos(current_pos);
    corpse.set_last_pos(last_pos);
    corpse.set_propulsor(propulsor);
    corpse.set_rotation(current_rotation);
    corpse.set_last_rotation(last_rotation);
    corpse.set_motor(motor);
}

template <class Archive>
void save(Archive& archive, const phy::Circle& circle) {
    gmt::UnitI size = circle.get_size();
    archive(cereal::base_class<phy::Corpse>(&circle));
    archive(cereal::make_nvp<gmt::UnitI>("size", size));  // param size
}

template <class Archive>
void load(Archive& archive, phy::Circle& circle) {
    gmt::UnitI size;
    archive(cereal::base_class<phy::Corpse>(&circle));
    archive(cereal::make_nvp<gmt::UnitI>("size", size));  // param size
    circle.set_size(size);
}

template <class Archive>
void save(Archive& archive, const phy::Polygon& polygon) {
    gmt::VerticesI points = polygon.get_points();
    std::vector<gmt::VerticesI> polygons = polygon.get_polygons();

    archive(cereal::base_class<phy::Corpse>(&polygon));

    archive(cereal::make_nvp<gmt::VerticesI>("points", points),                  // param points
            cereal::make_nvp<std::vector<gmt::VerticesI>>("polygons", polygons)  // param polygons
    );
}

template <class Archive>
void load(Archive& archive, phy::Polygon& polygon) {
    gmt::VerticesI points;
    std::vector<gmt::VerticesI> polygons;

    archive(cereal::base_class<phy::Corpse>(&polygon));

    archive(cereal::make_nvp<gmt::VerticesI>("points", points),                  // param points
            cereal::make_nvp<std::vector<gmt::VerticesI>>("polygons", polygons)  // param polygons
    );

    polygon.set_points(points);
    polygon.set_polygons(polygons);
}

template <class Archive>
void save(Archive& archive, const phy::Constraint& constraint) {
    std::shared_ptr<phy::Corpse> corpse_a = constraint.get_corpse_a();
    std::shared_ptr<phy::Corpse> corpse_b = constraint.get_corpse_b();
    gmt::VectorI relative_pos_a = constraint.get_relative_pos_a();
    gmt::VectorI relative_pos_b = constraint.get_relative_pos_b();
    bool rotation_a = constraint.get_rotation_a();
    bool rotation_b = constraint.get_rotation_b();
    gmt::UnitI relative_angle_a = constraint.get_relative_angle_a();
    gmt::UnitI relative_angle_b = constraint.get_relative_angle_b();
    gmt::UnitI friction_a = constraint.get_friction_a();
    gmt::UnitI friction_b = constraint.get_friction_b();
    bool breaking = constraint.get_breaking();
    bool broken = constraint.get_broken();

    archive(cereal::make_nvp<std::shared_ptr<phy::Corpse>>("corpse_a", corpse_a),  // param corpse_a
            cereal::make_nvp<std::shared_ptr<phy::Corpse>>("corpse_b", corpse_b),  // param corpse_b
            cereal::make_nvp<gmt::VectorI>("relative_pos_a", relative_pos_a),      // param relative_pos_a
            cereal::make_nvp<gmt::VectorI>("relative_pos_b", relative_pos_b),      // param relative_pos_b
            cereal::make_nvp<bool>("rotation_a", rotation_a),                      // param rotation_a
            cereal::make_nvp<bool>("rotation_b", rotation_b),                      // param rotation_b
            cereal::make_nvp<gmt::UnitI>("relative_angle_a", relative_angle_a),    // param relative_angle_a
            cereal::make_nvp<gmt::UnitI>("relative_angle_b", relative_angle_b),    // param relative_angle_b
            cereal::make_nvp<gmt::UnitI>("friction_a", friction_a),                // param friction_a
            cereal::make_nvp<gmt::UnitI>("friction_b", friction_b),                // param friction_b
            cereal::make_nvp<bool>("breaking", breaking),                          // param breaking
            cereal::make_nvp<bool>("broken", broken)                               // param broken
    );
}

template <class Archive>
void load(Archive& archive, phy::Constraint& constraint) {
    std::shared_ptr<phy::Corpse> corpse_a;
    std::shared_ptr<phy::Corpse> corpse_b;
    gmt::VectorI relative_pos_a;
    gmt::VectorI relative_pos_b;
    bool rotation_a;
    bool rotation_b;
    gmt::UnitI relative_angle_a;
    gmt::UnitI relative_angle_b;
    gmt::UnitI friction_a;
    gmt::UnitI friction_b;
    bool breaking;
    bool broken;

    archive(cereal::make_nvp<std::shared_ptr<phy::Corpse>>("corpse_a", corpse_a),  // param corpse_a
            cereal::make_nvp<std::shared_ptr<phy::Corpse>>("corpse_b", corpse_b),  // param corpse_b
            cereal::make_nvp<gmt::VectorI>("relative_pos_a", relative_pos_a),      // param relative_pos_a
            cereal::make_nvp<gmt::VectorI>("relative_pos_b", relative_pos_b),      // param relative_pos_b
            cereal::make_nvp<bool>("rotation_a", rotation_a),                      // param rotation_a
            cereal::make_nvp<bool>("rotation_b", rotation_b),                      // param rotation_b
            cereal::make_nvp<gmt::UnitI>("relative_angle_a", relative_angle_a),    // param relative_angle_a
            cereal::make_nvp<gmt::UnitI>("relative_angle_b", relative_angle_b),    // param relative_angle_b
            cereal::make_nvp<gmt::UnitI>("friction_a", friction_a),                // param friction_a
            cereal::make_nvp<gmt::UnitI>("friction_b", friction_b),                // param friction_b
            cereal::make_nvp<bool>("breaking", breaking),                          // param breaking
            cereal::make_nvp<bool>("broken", broken)                               // param broken
    );

    constraint.set_corpse_a(corpse_a);
    constraint.set_corpse_b(corpse_b);
    constraint.set_relative_pos_a(relative_pos_a);
    constraint.set_relative_pos_b(relative_pos_b);
    constraint.set_rotation_a(rotation_a);
    constraint.set_rotation_b(rotation_b);
    constraint.set_relative_angle_a(relative_angle_a);
    constraint.set_relative_angle_b(relative_angle_b);
    constraint.set_friction_a(friction_a);
    constraint.set_friction_b(friction_b);
    constraint.set_breaking(breaking);
    constraint.set_broken(broken);
}

template <class Archive>
void save(Archive& archive, const phy::Link& link) {
    gmt::UnitI size = link.get_size();
    gmt::UnitI damping = link.get_damping();
    gmt::UnitI max_size = link.get_max_size();
    gmt::UnitI min_size = link.get_min_size();

    archive(cereal::base_class<phy::Constraint>(&link));
    archive(cereal::make_nvp<gmt::UnitI>("size", size),          // param size
            cereal::make_nvp<gmt::UnitI>("damping", damping),    // param damping
            cereal::make_nvp<gmt::UnitI>("max_size", max_size),  // param max_size
            cereal::make_nvp<gmt::UnitI>("min_size", min_size)   // param min_size
    );
}

template <class Archive>
void load(Archive& archive, phy::Link& link) {
    gmt::UnitI size;
    gmt::UnitI damping;
    gmt::UnitI max_size;
    gmt::UnitI min_size;

    archive(cereal::base_class<phy::Constraint>(&link));
    archive(cereal::make_nvp<gmt::UnitI>("size", size),          // param size
            cereal::make_nvp<gmt::UnitI>("damping", damping),    // param damping
            cereal::make_nvp<gmt::UnitI>("max_size", max_size),  // param max_size
            cereal::make_nvp<gmt::UnitI>("min_size", min_size)   // param min_size
    );

    link.set_size(size);
    link.set_damping(damping);
    link.set_max_size(max_size);
    link.set_min_size(min_size);
}

template <class Archive, typename T>
void save(Archive& archive, const gmt::Vertices2<T>& vertices) {
    archive(cereal::make_nvp<std::vector<std::shared_ptr<gmt::Vector2<T>>>>("vertices", vertices.vertices));  // param vertices
}

template <class Archive, typename T>
void load(Archive& archive, gmt::Vertices2<T>& vertices) {
    archive(cereal::make_nvp<std::vector<std::shared_ptr<gmt::Vector2<T>>>>("vertices", vertices.vertices));  // param vertices
}

template <class Archive, typename T>
void save(Archive& archive, const gmt::Vector2<T>& vector) {
    archive(cereal::make_nvp<T>("x", vector.x),  // param x
            cereal::make_nvp<T>("y", vector.y)   // param y
    );
}

template <class Archive, typename T>
void load(Archive& archive, gmt::Vector2<T>& vector) {
    archive(cereal::make_nvp<T>("x", vector.x),  // param x
            cereal::make_nvp<T>("y", vector.y)   // param y
    );
}

template <class Archive, typename T>
void save(Archive& archive, const gmt::Bounds<T>& bounds) {
    archive(cereal::make_nvp<T>("x1", bounds.x1),  // param x1
            cereal::make_nvp<T>("y1", bounds.y1),  // param y1
            cereal::make_nvp<T>("x2", bounds.x2),  // param x2
            cereal::make_nvp<T>("y2", bounds.y2)   // param y2
    );
}

template <class Archive, typename T>
void load(Archive& archive, gmt::Bounds<T>& bounds) {
    archive(cereal::make_nvp<T>("x1", bounds.x1),  // param x1
            cereal::make_nvp<T>("y1", bounds.y1),  // param y1
            cereal::make_nvp<T>("x2", bounds.x2),  // param x2
            cereal::make_nvp<T>("y2", bounds.y2)   // param y2
    );
}

}  // namespace cereal
#endif