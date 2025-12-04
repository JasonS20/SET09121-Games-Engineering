#include "physics.hpp"

#include <algorithm>
#include <cmath>

namespace Physics {

    void integratePlayer(float dt, float input, const MovementSettings& settings, sf::RectangleShape& player, sf::Vector2f& velocity) {
        float targetVel = input * settings.playerSpeed;
        velocity.x += (targetVel - velocity.x) * std::min(settings.playerAcceleration * dt, 1.f);

        if (std::abs(input) < 0.01f) {
            velocity.x -= velocity.x * std::min(settings.friction * dt, 1.f);
        }

        player.move(velocity * dt);

        sf::Vector2f playerPos = player.getPosition();
        playerPos.x = std::clamp(playerPos.x, 0.f, settings.sceneWidth - player.getSize().x);
        playerPos.y = settings.floorY - player.getSize().y;
        player.setPosition(playerPos);
    }

    void dampAndMoveStool(float dt, float friction, sf::RectangleShape& stool, sf::Vector2f& stoolVelocity) {
        stoolVelocity.x -= stoolVelocity.x * std::min(friction * dt, 1.f);
        stool.move(stoolVelocity * dt);
    }

    void resolvePlayerStoolCollision(sf::RectangleShape& player, sf::Vector2f& playerVelocity, sf::RectangleShape& stool, sf::Vector2f& stoolVelocity) {
        sf::FloatRect playerBounds = player.getGlobalBounds();
        sf::FloatRect stoolBounds = stool.getGlobalBounds();

        if (!playerBounds.intersects(stoolBounds)) {
            return;
        }

        if (playerVelocity.x > 0.f) {
            player.setPosition(stoolBounds.left - playerBounds.width - 1.f, player.getPosition().y);
            stoolVelocity.x = std::max(stoolVelocity.x, playerVelocity.x);
        }
        else if (playerVelocity.x < 0.f) {
            player.setPosition(stoolBounds.left + stoolBounds.width + 1.f, player.getPosition().y);
            stoolVelocity.x = std::min(stoolVelocity.x, playerVelocity.x);
        }
    }

    void clampStoolWithinScene(float sceneWidth, float floorY, sf::RectangleShape& stool, sf::Vector2f& stoolVelocity) {
        sf::Vector2f stoolPos = stool.getPosition();
        stoolPos.x = std::clamp(stoolPos.x, 0.f, sceneWidth - stool.getSize().x);
        stoolPos.y = floorY;
        stool.setPosition(stoolPos);
        if (stoolPos.x <= 0.f || stoolPos.x >= sceneWidth - stool.getSize().x) {
            stoolVelocity.x = 0.f;
        }
    }
}