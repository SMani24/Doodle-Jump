/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "BlackHole.hpp"
#include <random>

BlackHole::BlackHole(std::shared_ptr<sf::Texture> texSmall, std::shared_ptr<sf::Texture> texLarge, float startX, float startY)
    : posX(startX), posY(startY)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    
    isLarge = (dist(gen) == 1);
    
    if (isLarge) {
        sprite.setTexture(*texLarge);
    } else {
        sprite.setTexture(*texSmall);
    }

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    sprite.setPosition(posX, posY);
}

void BlackHole::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void BlackHole::setY(float newY) {
    posY = newY;
    sprite.setPosition(posX, posY);
}

float BlackHole::getY() const {
    return posY;
}

sf::FloatRect BlackHole::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float offsetX = bounds.width * BlackHoleConfig::HITBOX_SHRINK_FACTOR;
    float offsetY = bounds.height * BlackHoleConfig::HITBOX_SHRINK_FACTOR;
    
    return sf::FloatRect(bounds.left + offsetX, bounds.top + offsetY, 
                         bounds.width - (2.0f * offsetX), bounds.height - (2.0f * offsetY));
}

sf::Vector2f BlackHole::getCenter() const {
    return sf::Vector2f(posX, posY);
}