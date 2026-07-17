/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Bullet.hpp"

Bullet::Bullet(std::shared_ptr<sf::Texture> tex, float startX, float startY) 
    : posX(startX), posY(startY) 
{
    sprite.setTexture(*tex);
    sprite.setScale(BulletConfig::SPRITE_SCALE, BulletConfig::SPRITE_SCALE);
    
    sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
    sprite.setPosition(posX, posY);
}

void Bullet::update(sf::Time deltaTime) {
    posY -= BulletConfig::SPEED * deltaTime.asSeconds();
    sprite.setPosition(posX, posY);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

float Bullet::getY() const {
    return posY;
}

sf::FloatRect Bullet::getBounds() const {
    return sprite.getGlobalBounds();
}