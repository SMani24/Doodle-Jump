/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef SPRING_HPP
#define SPRING_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class Spring {
private:
    sf::Sprite sprite;

public:
    Spring(std::shared_ptr<sf::Texture> tex);
    ~Spring() = default;

    void updatePosition(float platX, float platY, float platWidth);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
};

#endif // SPRING_HPP