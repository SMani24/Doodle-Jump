/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include "SettingsManager.hpp"

namespace MonsterConfig {
    constexpr float MOVEMENT_SPEED = 100.0f;
    constexpr int HP_EASY = 1;
    constexpr int HP_MEDIUM = 2;
    constexpr int HP_HARD = 3;
}

class Monster {
protected:
    sf::Sprite sprite;
    float posX;
    float posY;
    float velocityX;
    int health;

public:
    Monster(float startX, float startY, Difficulty diff);
    virtual ~Monster() = default;

    virtual void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;

    void setY(float newY);
    float getY() const;
    sf::FloatRect getBounds() const;

    void takeDamage();
    bool isAlive() const;
};

#endif // MONSTER_HPP