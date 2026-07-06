/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "BreakablePlatform.hpp"

BreakablePlatform::BreakablePlatform(std::shared_ptr<sf::Texture> brokenTex, float x, float y)
    : Platform(brokenTex, x, y), isBroken(false), 
      leftPosX(0.0f), rightPosX(0.0f), leftPosY(0.0f), rightPosY(0.0f),
      leftRotation(0.0f), rightRotation(0.0f) 
{
    sprite.setTexture(*texture);
    sf::Vector2u texSize = texture->getSize();
    
    int halfWidth = texSize.x / 2;
    int height = texSize.y;

    spriteLeft.setTexture(*texture);
    spriteLeft.setTextureRect(sf::IntRect(0, 0, halfWidth, height));
    spriteLeft.setOrigin(halfWidth / 2.0f, height / 2.0f);

    spriteRight.setTexture(*texture);
    spriteRight.setTextureRect(sf::IntRect(halfWidth, 0, halfWidth, height));
    spriteRight.setOrigin(halfWidth / 2.0f, height / 2.0f);
    
    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    sprite.setPosition(posX, posY);
}

void BreakablePlatform::update(sf::Time deltaTime) {
    if (isBroken) {
        float dt = deltaTime.asSeconds();
        
        leftPosY += BreakablePlatformConfig::FALL_SPEED_Y * dt;
        leftPosX -= BreakablePlatformConfig::FALL_SPEED_X * dt;
        
        leftRotation += BreakablePlatformConfig::ROTATION_SPEED * dt; 

        rightPosY += BreakablePlatformConfig::FALL_SPEED_Y * dt;
        rightPosX += BreakablePlatformConfig::FALL_SPEED_X * dt;
        
        rightRotation -= BreakablePlatformConfig::ROTATION_SPEED * dt; 

        spriteLeft.setPosition(leftPosX, leftPosY);
        spriteLeft.setRotation(leftRotation);
        
        spriteRight.setPosition(rightPosX, rightPosY);
        spriteRight.setRotation(rightRotation);
    }
}

void BreakablePlatform::draw(sf::RenderWindow& window) const {
    if (isBroken) {
        window.draw(spriteLeft);
        window.draw(spriteRight);
    } else {
        window.draw(sprite);
    }
}

void BreakablePlatform::breakPlatform() {
    isBroken = true;

    float halfWidth = spriteLeft.getLocalBounds().width;

    leftPosX = posX - (halfWidth / 2.0f);
    rightPosX = posX + (halfWidth / 2.0f);
    leftPosY = posY;
    rightPosY = posY;

    spriteLeft.setPosition(leftPosX, leftPosY);
    spriteRight.setPosition(rightPosX, rightPosY);
}

bool BreakablePlatform::getIsBroken() const {
    return isBroken;
}