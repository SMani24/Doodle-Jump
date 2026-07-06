/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Platform.hpp"

Platform::Platform(std::shared_ptr<sf::Texture> tex, float x, float y)
    : texture(tex), posX(x), posY(y) 
{
    sprite.setTexture(*texture);
    sprite.setPosition(posX, posY);
}

void Platform::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Platform::getBounds() const {
    return sprite.getGlobalBounds();
}

float Platform::getX() const { return posX; }
float Platform::getY() const { return posY; }

void Platform::setY(float newY) {
    posY = newY;
    sprite.setPosition(posX, posY);
}