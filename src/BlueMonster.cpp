#include "BlueMonster.hpp"

BlueMonster::BlueMonster(std::shared_ptr<sf::Texture> tex, float startX, float startY, Difficulty diff)
    : Monster(startX, startY, diff), texture(tex)
{
    sprite.setTexture(*texture);
    frameWidth = texture->getSize().x / 2;
    frameHeight = texture->getSize().y;

    sprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);
}

void BlueMonster::update(sf::Time deltaTime) {
    Monster::update(deltaTime);
    
    int rectLeft = (velocityX > 0) ? 0 : frameWidth;
    sprite.setTextureRect(sf::IntRect(rectLeft, 0, frameWidth, frameHeight));
}