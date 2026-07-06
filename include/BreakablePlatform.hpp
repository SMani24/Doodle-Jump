/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef BREAKABLE_PLATFORM_HPP
#define BREAKABLE_PLATFORM_HPP

#include "Platform.hpp"

namespace BreakablePlatformConfig {
    constexpr float FALL_SPEED_Y = 500.0f;
    constexpr float FALL_SPEED_X = 40.0f;
    constexpr float ROTATION_SPEED = 150.0f; 
}

class BreakablePlatform : public Platform {
private:
    bool isBroken;
    
    sf::Sprite spriteLeft;
    sf::Sprite spriteRight;
    
    float leftPosX;
    float rightPosX;
    float leftPosY;
    float rightPosY;
    float leftRotation;
    float rightRotation;

public:
    BreakablePlatform(std::shared_ptr<sf::Texture> brokenTex, float x, float y);
    ~BreakablePlatform() override = default;

    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    
    void breakPlatform();
    bool getIsBroken() const;
};

#endif // BREAKABLE_PLATFORM_HPP