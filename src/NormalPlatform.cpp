/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "NormalPlatform.hpp"

NormalPlatform::NormalPlatform(std::shared_ptr<sf::Texture> tex, float x, float y)
    : Platform(tex, x, y) 
{
    sprite.setScale(PlatformConfig::SPRITE_SCALE, PlatformConfig::SPRITE_SCALE);
}

void NormalPlatform::update(sf::Time deltaTime) {
    (void)deltaTime; 
}