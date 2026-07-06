/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "MovingPlatform.hpp"

MovingPlatform::MovingPlatform(std::shared_ptr<sf::Texture> tex, float x, float y)
    : Platform(tex, x, y), direction(1) {}

void MovingPlatform::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    
    posX += direction * MovingPlatformConfig::SPEED * dt;

    float halfWidth = sprite.getGlobalBounds().width / 2.0f;
    
    if (posX + halfWidth > GameConfig::BASE_WIDTH) {
        posX = GameConfig::BASE_WIDTH - halfWidth;
        direction = -1;
    } 
    else if (posX - halfWidth < 0.0f) {
        posX = halfWidth;
        direction = 1;
    }

    sprite.setPosition(posX, posY);
}