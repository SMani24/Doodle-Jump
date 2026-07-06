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
    constexpr float FALL_SPEED = 500.0f;
}

class BreakablePlatform : public Platform {
private:
    bool isBroken;
    std::shared_ptr<sf::Texture> brokenTexture;

public:
    BreakablePlatform(std::shared_ptr<sf::Texture> tex, std::shared_ptr<sf::Texture> brokenTex, float x, float y);
    ~BreakablePlatform() override = default;

    void update(sf::Time deltaTime) override;
    void breakPlatform();
    bool getIsBroken() const;
};

#endif // BREAKABLE_PLATFORM_HPP