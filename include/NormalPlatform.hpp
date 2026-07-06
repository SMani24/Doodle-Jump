/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef NORMAL_PLATFORM_HPP
#define NORMAL_PLATFORM_HPP

#include "Platform.hpp"

namespace PlatformConfig {
    constexpr float SPRITE_SCALE = 1.0f;
}

class NormalPlatform : public Platform {
public:
    NormalPlatform(std::shared_ptr<sf::Texture> tex, float x, float y);
    ~NormalPlatform() override = default;

    void update(sf::Time deltaTime) override;
};

#endif // NORMAL_PLATFORM_HPP