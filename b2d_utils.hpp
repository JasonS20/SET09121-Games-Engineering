#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

namespace box2d_helpers {
	const sf::Vector2f bv2_to_sv2(const b2Vec2& in);
	const b2Vec2 sv2_to_bv2(const sf::Vector2f& in);
	const sf::Vector2f invert_height(const sf::Vector2f& in);

	b2BodyId create_physics_box(b2WorldId& world_id, bool dynamic, const sf::Vector2f& position, const sf::Vector2f& size);
	b2BodyId create_physics_box(b2WorldId& world_id, bool dynamic, const std::shared_ptr<sf::RectangleShape>& rs);
}