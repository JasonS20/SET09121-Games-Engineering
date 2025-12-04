#include "b2d_utils.hpp"

#include "game_parameters.hpp"

using param = Parameters;

namespace box2d_helpers {

    const sf::Vector2f bv2_to_sv2(const b2Vec2& in) {
        return sf::Vector2f(in.x * param::physics_scale, in.y * param::physics_scale);
    }

    const b2Vec2 sv2_to_bv2(const sf::Vector2f& in) {
        return { in.x * param::physics_scale_inv, in.y * param::physics_scale_inv };
    }

    const sf::Vector2f invert_height(const sf::Vector2f& in) {
        return sf::Vector2f(in.x, param::game_height - in.y);
    }

    b2BodyId create_physics_box(b2WorldId& world_id, bool dynamic, const sf::Vector2f& position, const sf::Vector2f& size) {
        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.type = dynamic ? b2_dynamicBody : b2_staticBody;
        body_def.position = sv2_to_bv2(position);

        b2BodyId body_id = b2CreateBody(world_id, &body_def);

        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = dynamic ? 10.f : 0.f;
        shape_def.material.friction = dynamic ? 0.8f : 1.f;
        shape_def.material.restitution = 0.2f;
        b2Polygon polygon = b2MakeBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
        b2CreatePolygonShape(body_id, &shape_def, &polygon);

        return body_id;
    }

    b2BodyId create_physics_box(b2WorldId& world_id, bool dynamic, const std::shared_ptr<sf::RectangleShape>& rs) {
        return create_physics_box(world_id, dynamic, rs->getPosition(), rs->getSize());
    }

}