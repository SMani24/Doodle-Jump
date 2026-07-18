/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Monster.hpp"
#include "Game.hpp"
#include <random>
#include <cmath>

Monster::Monster(float startX, float startY, Difficulty diff)
    : posX(startX), posY(startY)
{
    if (diff == Difficulty::Easy) health = MonsterConfig::HP_EASY;
    else if (diff == Difficulty::Medium) health = MonsterConfig::HP_MEDIUM;
    else health = MonsterConfig::HP_HARD;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dirDist(0, 1);
    
    velocityX = (dirDist(gen) == 0) ? MonsterConfig::MOVEMENT_SPEED : -MonsterConfig::MOVEMENT_SPEED;
}

void Monster::update(sf::Time deltaTime) {
    posX += velocityX * deltaTime.asSeconds();

    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (posX - bounds.width / 2.0f <= 0.0f) {
        posX = bounds.width / 2.0f;
        velocityX = std::abs(velocityX);
    } else if (posX + bounds.width / 2.0f >= GameConfig::BASE_WIDTH) {
        posX = GameConfig::BASE_WIDTH - bounds.width / 2.0f;
        velocityX = -std::abs(velocityX);
    }

    sprite.setPosition(posX, posY);
}

void Monster::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Monster::setY(float newY) {
    posY = newY;
    sprite.setPosition(posX, posY);
}

float Monster::getY() const { return posY; }

sf::FloatRect Monster::getBounds() const { return sprite.getGlobalBounds(); }

void Monster::takeDamage() { health--; }

bool Monster::isAlive() const { return health > 0; }