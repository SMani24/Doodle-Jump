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

namespace PlayerConfig {
    constexpr float GRAVITY = 1200.0f;
    constexpr float MOVEMENT_SPEED = 300.0f;
    constexpr float JUMP_VELOCITY = -800.0f;
    constexpr float SUPER_JUMP_VELOCITY = -1400.0f;
    constexpr float SPRITE_SCALE = 0.30f;

    constexpr float SUCTION_ANGLE_SPEED = 10.0f;
    constexpr float SUCTION_PULL_SPEED = 200.0f;
    constexpr float SUCTION_SHRINK_SPEED = 0.25f;
    constexpr float SUCTION_ROTATION_SPEED = 1000.0f;
}

class Player {
private:
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> leftTexture;
    std::shared_ptr<sf::Texture> rightTexture;
    std::shared_ptr<sf::Texture> shootTexture;

    float posX;
    float posY;
    float velocityX;
    float velocityY;
    bool facingLeft;
    bool isShooting;

    bool isBeingSucked;
    sf::Vector2f suctionTarget;
    float suctionRadius;
    float suctionAngle;
    float suctionScale;

public:
    Player(std::shared_ptr<sf::Texture> leftTex, std::shared_ptr<sf::Texture> rightTex, std::shared_ptr<sf::Texture> shootTex);
    ~Player() = default;

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;

    void moveLeft();
    void moveRight();
    void stopMoving();
    
    void jump();
    void superJump();

    float getY() const;
    void setY(float y);
    float getVelocityY() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getCenter() const;

    void setShooting(bool shooting);
    sf::Vector2f getShootPosition() const;

    void startSuction(sf::Vector2f targetCenter);
    bool isSuctionComplete() const;
};

#endif