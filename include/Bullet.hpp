/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace BulletConfig {
    constexpr float SPEED = 800.0f; 
    constexpr float SPRITE_SCALE = 0.07f;
}

class Bullet {
private:
    sf::Sprite sprite;
    float posX;
    float posY;
    bool active;

public:
    Bullet(std::shared_ptr<sf::Texture> tex, float startX, float startY);
    ~Bullet() = default;

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;
    
    float getY() const;
    sf::FloatRect getBounds() const;

    bool isActive() const;
    void deactivate();
};

#endif