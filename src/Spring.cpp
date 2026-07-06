/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Spring.hpp"

Spring::Spring(std::shared_ptr<sf::Texture> tex) {
    sprite.setTexture(*tex);
    
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height);
}

void Spring::updatePosition(float platX, float platY, float platWidth) {
    sprite.setPosition(platX + (platWidth / 2.0f), platY);
}

void Spring::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Spring::getBounds() const {
    return sprite.getGlobalBounds();
}