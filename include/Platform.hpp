/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics.hpp>
#include "Spring.hpp"
#include <memory>

class Platform {
protected:
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    std::unique_ptr<Spring> spring;
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

    virtual void setY(float newY);

    void attachSpring(std::shared_ptr<sf::Texture> springTex);
    bool hasSpring() const;
    sf::FloatRect getSpringBounds() const;

    void compressSpring();
};

#endif // PLATFORM_HPP