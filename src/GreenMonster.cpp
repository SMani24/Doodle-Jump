#include "GreenMonster.hpp"

GreenMonster::GreenMonster(std::shared_ptr<sf::Texture> tex, float startX, float startY, Difficulty diff)
    : Monster(startX, startY, diff), texture(tex)
{
    sprite.setTexture(*texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
}