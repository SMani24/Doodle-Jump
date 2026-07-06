/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "BreakablePlatform.hpp"

BreakablePlatform::BreakablePlatform(std::shared_ptr<sf::Texture> tex, std::shared_ptr<sf::Texture> brokenTex, float x, float y)
    : Platform(tex, x, y), isBroken(false), brokenTexture(brokenTex) {}

void BreakablePlatform::update(sf::Time deltaTime) {
    if (isBroken) {
        posY += BreakablePlatformConfig::FALL_SPEED * deltaTime.asSeconds();
        sprite.setPosition(posX, posY);
    }
}

void BreakablePlatform::breakPlatform() {
    isBroken = true;
    sprite.setTexture(*brokenTexture);
}

bool BreakablePlatform::getIsBroken() const {
    return isBroken;
}