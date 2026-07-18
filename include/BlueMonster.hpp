/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef BLUE_MONSTER_HPP
#define BLUE_MONSTER_HPP

#include "Monster.hpp"
#include <memory>

class BlueMonster : public Monster {
private:
    std::shared_ptr<sf::Texture> texture;
    int frameWidth;
    int frameHeight;

public:
    BlueMonster(std::shared_ptr<sf::Texture> tex, float startX, float startY, Difficulty diff);
    void update(sf::Time deltaTime) override;
};

#endif // BLUE_MONSTER_HPP