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

namespace SpringConfig {
    constexpr float VISUAL_Y_OFFSET = 4.0f;
    constexpr float EDGE_PADDING = 2.0f;
    
    constexpr int CROP_Y_OFFSET = -2;
    constexpr int HEIGHT_REDUCTION = 4;
}

class Spring {
private:
    sf::Sprite sprite;
    float relativeOffsetX;
    int frameWidth;
    int frameHeight;
    bool isCompressed;

public:
    Spring(std::shared_ptr<sf::Texture> tex, float platformWidth);
    ~Spring() = default;

    void updatePosition(float platX, float platY);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    
    void compress();
};

#endif // SPRING_HPP