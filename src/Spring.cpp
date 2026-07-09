/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Spring.hpp"
#include <random>
#include <algorithm>

Spring::Spring(std::shared_ptr<sf::Texture> tex, float platformWidth)
    : isCompressed(false) 
{
    sprite.setTexture(*tex);
    
    frameWidth = tex->getSize().x;
    
    int baseFrameHeight = tex->getSize().y / 2;
    frameHeight = baseFrameHeight - SpringConfig::HEIGHT_REDUCTION;

    int uncompressedY = baseFrameHeight + SpringConfig::CROP_Y_OFFSET;
    sprite.setTextureRect(sf::IntRect(0, uncompressedY, frameWidth, frameHeight));
    
    sprite.setOrigin(frameWidth / 2.0f, frameHeight);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    float minX = (frameWidth / 2.0f) + SpringConfig::EDGE_PADDING;
    float maxX = platformWidth - (frameWidth / 2.0f) - SpringConfig::EDGE_PADDING;
    
    if (minX > maxX) {
        minX = maxX = platformWidth / 2.0f;
    }

    std::uniform_real_distribution<float> dis(minX, maxX);
    relativeOffsetX = dis(gen);
}

void Spring::updatePosition(float platX, float platY) {
    sprite.setPosition(platX + relativeOffsetX, platY + SpringConfig::VISUAL_Y_OFFSET);
}

void Spring::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Spring::getBounds() const {
    return sprite.getGlobalBounds();
}

void Spring::compress() {
    if (!isCompressed) {
        isCompressed = true;
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    }
}