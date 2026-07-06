/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.hpp"

namespace PlayerConfig {
    constexpr float GRAVITY = 1200.0f;
    constexpr float MOVEMENT_SPEED = 300.0f;
    constexpr float JUMP_VELOCITY = -800.0f;
    constexpr float SPRITE_SCALE = 0.5f;
}

class Player {
private:
    sf::Sprite sprite;
    
    std::shared_ptr<sf::Texture> textureLeft;
    std::shared_ptr<sf::Texture> textureRight;

    float posX;
    float posY;
    float velocityX;
    float velocityY;

    void wrapAroundScreen();

public:
    Player(std::shared_ptr<sf::Texture> texLeft, std::shared_ptr<sf::Texture> texRight);
    ~Player() = default;

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;
    
    void moveLeft();
    void moveRight();
    void stopMoving();
    
    void jump();

    float getX() const;
    float getY() const;
    float getVelocityY() const;
    sf::FloatRect getBounds() const;
    
    void setY(float newY);
};

#endif // PLAYER_HPP