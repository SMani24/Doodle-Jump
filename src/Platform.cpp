/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Platform.hpp"

Platform::Platform(std::shared_ptr<sf::Texture> tex, float x, float y)
    : texture(tex), spring(nullptr), posX(x), posY(y) 
{
    sprite.setTexture(*texture);
    sprite.setPosition(posX, posY);
}

void Platform::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
    if (spring) {
        spring->draw(window);
    }
}

sf::FloatRect Platform::getBounds() const {
    return sprite.getGlobalBounds();
}

float Platform::getX() const { return posX; }
float Platform::getY() const { return posY; }

void Platform::setY(float newY) {
    posY = newY;
    sprite.setPosition(posX, posY);
    if (spring) {
        spring->updatePosition(posX, posY);
    }
}

void Platform::attachSpring(std::shared_ptr<sf::Texture> springTex) {
    float platWidth = sprite.getLocalBounds().width;
    spring = std::make_unique<Spring>(springTex, platWidth);
    spring->updatePosition(posX, posY);
}

bool Platform::hasSpring() const {
    return spring != nullptr;
}

sf::FloatRect Platform::getSpringBounds() const {
    if (spring) return spring->getBounds();
    return sf::FloatRect();
}

void Platform::compressSpring() {
    if (spring) {
        spring->compress();
    }
}