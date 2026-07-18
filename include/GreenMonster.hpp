/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef GREEN_MONSTER_HPP
#define GREEN_MONSTER_HPP

#include "Monster.hpp"
#include <memory>

class GreenMonster : public Monster {
private:
    std::shared_ptr<sf::Texture> texture;
public:
    GreenMonster(std::shared_ptr<sf::Texture> tex, float startX, float startY, Difficulty diff);
};

#endif // GREEN_MONSTER_HPP