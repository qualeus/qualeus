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
#include <System/System.hpp>

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
CEREAL_REGISTER_TYPE(phy::Shape)
CEREAL_REGISTER_TYPE(phy::Circle)
CEREAL_REGISTER_TYPE(phy::Polygon)
CEREAL_REGISTER_TYPE(phy::Edge)
CEREAL_REGISTER_POLYMORPHIC_RELATION(phy::Shape, phy::Circle)
CEREAL_REGISTER_POLYMORPHIC_RELATION(phy::Shape, phy::Polygon)
CEREAL_REGISTER_POLYMORPHIC_RELATION(phy::Shape, phy::Edge)

/*
CEREAL_REGISTER_TYPE(phy::Constraint)
CEREAL_REGISTER_TYPE(phy::Link)
CEREAL_REGISTER_POLYMORPHIC_RELATION(phy::Constraint, phy::Link)
*/

CEREAL_REGISTER_TYPE(gmt::Integrator)
CEREAL_REGISTER_TYPE(gmt::Euler)
// CEREAL_REGISTER_TYPE(gmt::Verlet)
CEREAL_REGISTER_POLYMORPHIC_RELATION(gmt::Integrator, gmt::Euler)
// CEREAL_REGISTER_POLYMORPHIC_RELATION(gmt::Integrator, gmt::Verlet)

CEREAL_REGISTER_TYPE(gmt::Partitioner)
CEREAL_REGISTER_TYPE(gmt::BruteForce)
// CEREAL_REGISTER_TYPE(gmt::Bounding)
// CEREAL_REGISTER_TYPE(gmt::KDTree)
// CEREAL_REGISTER_TYPE(gmt::QuadTree)
// CEREAL_REGISTER_TYPE(gmt::SpatialGrid)

CEREAL_REGISTER_POLYMORPHIC_RELATION(gmt::BruteForce, gmt::Partitioner)
// CEREAL_REGISTER_POLYMORPHIC_RELATION(gmt::QuadTree, gmt::Partitioner)

CEREAL_REGISTER_TYPE(gmt::Solver)
CEREAL_REGISTER_TYPE(gmt::Sequential)
CEREAL_REGISTER_POLYMORPHIC_RELATION(gmt::Solver, gmt::Sequential)

namespace cereal {

/* ============================================================================================= */
/*                                             STATE                                             */
/* ============================================================================================= */

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

    state.system             = system;
    state.corpses_colors     = corpses_colors;
    state.constraints_colors = constraints_colors;
    state.paused             = paused;
    state.show_gui           = show_gui;
    state.show_debug         = show_debug;
    state.post_process       = post_process;
}

/* ============================================================================================= */
/*                                            SYSTEM                                             */
/* ============================================================================================= */

template <class Archive>
void save(Archive& archive, const phy::System& system) {
    com::vec<com::sptr<phy::Corpse>> corpses         = system.get_corpses();
    com::map<int, com::sptr<phy::Corpse>> references = system.get_references();

    archive(cereal::make_nvp<com::vec<com::sptr<phy::Corpse>>>("corpses", corpses),            // param corpses
            cereal::make_nvp<com::map<int, com::sptr<phy::Corpse>>>("references", references)  // param references
    );
}

template <class Archive>
void load(Archive& archive, phy::System& system) {
    // TODO
}

/* ============================================================================================= */
/*                                            CORPSES                                            */
/* ============================================================================================= */

template <class Archive>
void save(Archive& archive, const phy::Corpse& corpse) {
    int id                                 = corpse.get_id();
    gmt::VectorI pos                       = corpse.get_pos();
    gmt::VectorI vel                       = corpse.get_vel();
    gmt::VectorI acc                       = corpse.get_acc();
    gmt::UnitI rot                         = corpse.get_rot();
    gmt::UnitI spi                         = corpse.get_spi();
    gmt::UnitI tor                         = corpse.get_tor();
    bool fixed                             = corpse.get_fixed();
    bool etherial                          = corpse.get_etherial();
    bool tied                              = corpse.get_tied();
    com::vec<com::sptr<phy::Shape>> shapes = corpse.get_shapes();

    archive(cereal::make_nvp<int>("id", id),                                     // param id
            cereal::make_nvp<gmt::VectorI>("pos", pos),                          // param pos
            cereal::make_nvp<gmt::VectorI>("vel", vel),                          // param vel
            cereal::make_nvp<gmt::VectorI>("acc", acc),                          // param acc
            cereal::make_nvp<gmt::UnitI>("rot", rot),                            // param rot
            cereal::make_nvp<gmt::UnitI>("spi", spi),                            // param spi
            cereal::make_nvp<gmt::UnitI>("tor", tor),                            // param tor
            cereal::make_nvp<bool>("fixed", fixed),                              // param fixed
            cereal::make_nvp<bool>("etherial", etherial),                        // param etherial
            cereal::make_nvp<bool>("tied", tied),                                // param tied
            cereal::make_nvp<com::vec<com::sptr<phy::Shape>>>("shapes", shapes)  // param tied
    );
}

template <class Archive>
void load(Archive& archive, phy::Corpse& corpse) {
    gmt::VectorI pos;
    gmt::VectorI vel;
    gmt::VectorI acc;
    gmt::UnitI rot;
    gmt::UnitI spi;
    gmt::UnitI tor;
    bool fixed;
    bool etherial;
    bool tied;
    com::vec<com::sptr<phy::Shape>> shapes;

    archive(cereal::make_nvp<gmt::VectorI>("pos", pos),                          // param pos
            cereal::make_nvp<gmt::VectorI>("vel", vel),                          // param vel
            cereal::make_nvp<gmt::VectorI>("acc", acc),                          // param acc
            cereal::make_nvp<gmt::UnitI>("rot", rot),                            // param rot
            cereal::make_nvp<gmt::UnitI>("spi", spi),                            // param spi
            cereal::make_nvp<gmt::UnitI>("tor", tor),                            // param tor
            cereal::make_nvp<bool>("fixed", fixed),                              // param fixed
            cereal::make_nvp<bool>("etherial", etherial),                        // param etherial
            cereal::make_nvp<bool>("tied", tied),                                // param tied
            cereal::make_nvp<com::vec<com::sptr<phy::Shape>>>("shapes", shapes)  // param tied
    );

    corpse.set_pos(pos);
    corpse.set_vel(vel);
    corpse.set_acc(acc);
    corpse.set_rot(rot);
    corpse.set_spi(spi);
    corpse.set_tor(tor);
    corpse.set_fixed(fixed);
    corpse.set_etherial(etherial);
    corpse.set_tied(tied);
    corpse.set_shapes(shapes);
}

template <class Archive>
void save(Archive& archive, const phy::Circle& circle) {
    gmt::UnitI radius = circle.get_radius();

    archive(cereal::make_nvp<gmt::UnitI>("radius", radius));  // param radius
}

template <class Archive>
void load(Archive& archive, phy::Circle& circle) {
    gmt::UnitI radius;

    archive(cereal::make_nvp<gmt::UnitI>("radius", radius));  // param radius

    circle.set_radius(radius);
}

template <class Archive>
void save(Archive& archive, const phy::Polygon& polygon) {
    gmt::VerticesI vertices = polygon.get_vertices();

    archive(cereal::make_nvp<gmt::VerticesI>("vertices", vertices));  // param vertices
}

template <class Archive>
void load(Archive& archive, phy::Polygon& polygon) {
    gmt::VerticesI vertices;

    archive(cereal::make_nvp<gmt::VerticesI>("vertices", vertices));  // param vertices

    polygon.set_vertices(vertices);
}

template <class Archive>
void save(Archive& archive, const phy::Edge& edge) {
    gmt::VectorI point_a = edge.get_point_a();
    gmt::VectorI point_b = edge.get_point_b();

    archive(cereal::make_nvp<gmt::VectorI>("point_a", point_a),  // param point_a
            cereal::make_nvp<gmt::VectorI>("point_b", point_b)   // param point_b
    );
}

template <class Archive>
void load(Archive& archive, phy::Edge& edge) {
    gmt::VectorI point_a;
    gmt::VectorI point_b;

    archive(cereal::make_nvp<gmt::VectorI>("point_a", point_a),  // param point_a
            cereal::make_nvp<gmt::VectorI>("point_b", point_b)   // param point_b
    );

    edge.set_point_a(point_a);
    edge.set_point_b(point_b);
}

/* ============================================================================================= */
/*                                          CONSTRAINTS                                          */
/* ============================================================================================= */

/*
template <class Archive>
void save(Archive& archive, const phy::Constraint& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, phy::Constraint& constraint) {
    // TODO
}

template <class Archive>
void save(Archive& archive, const phy::Link& link) {
    // TODO
}

template <class Archive>
void load(Archive& archive, phy::Link& link) {
    // TODO
}
*/

/* ============================================================================================= */
/*                                          COLLISIONS                                           */
/* ============================================================================================= */

/*
template <class Archive>
void save(Archive& archive, const phy::Collision& collision) {
    // TODO
}

template <class Archive>
void load(Archive& archive, phy::Collision& collision) {
    // TODO
}
*/
/* ============================================================================================= */
/*                                          INTEGRATORS                                          */
/* ============================================================================================= */

template <class Archive>
void save(Archive& archive, const gmt::Integrator& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::Integrator& constraint) {
    // TODO
}

template <class Archive>
void save(Archive& archive, const gmt::Euler& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::Euler& constraint) {
    // TODO
}

/*
template <class Archive>
void save(Archive& archive, const gmt::Verlet& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::Verlet& constraint) {
    // TODO
}
*/

/* ============================================================================================= */
/*                                         PARTITIONNERS                                         */
/* ============================================================================================= */

template <class Archive>
void save(Archive& archive, const gmt::Partitioner& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::Partitioner& constraint) {
    // TODO
}

/*
template <class Archive>
void save(Archive& archive, const gmt::Bounding& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::Bounding& constraint) {
    // TODO
}
*/

template <class Archive>
void save(Archive& archive, const gmt::BruteForce& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::BruteForce& constraint) {
    // TODO
}

/*
template <class Archive>
void save(Archive& archive, const gmt::KDTree& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::KDTree& constraint) {
    // TODO
}

template <class Archive>
void save(Archive& archive, const gmt::QuadTree& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::QuadTree& constraint) {
    // TODO
}

template <class Archive>
void save(Archive& archive, const gmt::QuadNode& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::QuadNode& constraint) {
    // TODO
}

template <class Archive>
void save(Archive& archive, const gmt::SpatialGrid& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::SpatialGrid& constraint) {
    // TODO
}
*/

/* ============================================================================================= */
/*                                            SOLVERS                                            */
/* ============================================================================================= */

template <class Archive>
void save(Archive& archive, const gmt::Solver& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::Solver& constraint) {
    // TODO
}

template <class Archive>
void save(Archive& archive, const gmt::Sequential& constraint) {
    // TODO
}

template <class Archive>
void load(Archive& archive, gmt::Sequential& constraint) {
    // TODO
}

/* ============================================================================================= */
/*                                            GEOMETRY                                           */
/* ============================================================================================= */

template <class Archive, typename T>
void save(Archive& archive, const gmt::Vertices2<T>& vertices) {
    archive(cereal::make_nvp<std::vector<gmt::Vector2<T>>>("vertices", vertices.vertices));  // param vertices
}

template <class Archive, typename T>
void load(Archive& archive, gmt::Vertices2<T>& vertices) {
    archive(cereal::make_nvp<std::vector<gmt::Vector2<T>>>("vertices", vertices.vertices));  // param vertices
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
    archive(cereal::make_nvp<T>("p1", bounds.p1),  // param p1
            cereal::make_nvp<T>("p2", bounds.p2)   // param p2
    );
}

template <class Archive, typename T>
void load(Archive& archive, gmt::Bounds<T>& bounds) {
    archive(cereal::make_nvp<T>("p1", bounds.p1),  // param p1
            cereal::make_nvp<T>("p2", bounds.p2)   // param p2
    );
}

}  // namespace cereal

#endif