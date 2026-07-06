/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef MOVING_PLATFORM_HPP
#define MOVING_PLATFORM_HPP

#include "Platform.hpp"
#include "Game.hpp" 

namespace MovingPlatformConfig {
    constexpr float SPEED = 100.0f;
}

class MovingPlatform : public Platform {
private:
    int direction; 

public:
    MovingPlatform(std::shared_ptr<sf::Texture> tex, float x, float y);
    ~MovingPlatform() override = default;

    void update(sf::Time deltaTime) override;
};

#endif // MOVING_PLATFORM_HPP