/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef BLACK_HOLE_HPP
#define BLACK_HOLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace BlackHoleConfig {
    constexpr float HITBOX_SHRINK_FACTOR = 0.25f;
}

class BlackHole {
private:
    sf::Sprite sprite;
    float posX;
    float posY;
    bool isLarge;

public:
    BlackHole(std::shared_ptr<sf::Texture> texSmall, std::shared_ptr<sf::Texture> texLarge, float startX, float startY);
    ~BlackHole() = default;

    void draw(sf::RenderWindow& window) const;
    void setY(float newY);
    
    float getY() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getCenter() const;
};

#endif