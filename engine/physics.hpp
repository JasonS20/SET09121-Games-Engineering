#pragma once

#include <SFML/Graphics.hpp>

namespace Physics {
    struct MovementSettings {
        float playerSpeed;
        float playerAcceleration;
        float friction;
        float floorY;
        float sceneWidth;
    };

    void integratePlayer(float dt, float input, const MovementSettings& settings, sf::RectangleShape& player, sf::Vector2f& velocity);
    void dampAndMoveStool(float dt, float friction, sf::RectangleShape& stool, sf::Vector2f& stoolVelocity);
    void resolvePlayerStoolCollision(sf::RectangleShape& player, sf::Vector2f& playerVelocity, sf::RectangleShape& stool, sf::Vector2f& stoolVelocity);
    void clampStoolWithinScene(float sceneWidth, float floorY, sf::RectangleShape& stool, sf::Vector2f& stoolVelocity);
}