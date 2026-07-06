/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class Platform {
protected:
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    float posX;
    float posY;

public:
    Platform(std::shared_ptr<sf::Texture> tex, float x, float y);
    virtual ~Platform() = default;

    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    float getX() const;
    float getY() const;

    void setY(float newY);
};

#endif // PLATFORM_HPP