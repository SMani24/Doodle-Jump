/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Player.hpp"

Player::Player(std::shared_ptr<sf::Texture> texLeft, std::shared_ptr<sf::Texture> texRight) 
    : textureLeft(texLeft), textureRight(texRight), posX(200.0f), posY(400.0f), velocityX(0.0f), velocityY(0.0f) 
{
    sprite.setTexture(*textureRight);
    
    sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
    sprite.setPosition(posX, posY);
}

void Player::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();

    velocityY += PlayerConfig::GRAVITY * dt;

    posX += velocityX * dt;
    posY += velocityY * dt;

    wrapAroundScreen();

    sprite.setPosition(posX, posY);
}

void Player::wrapAroundScreen() {
    float halfWidth = sprite.getLocalBounds().width / 2.0f;

    if (posX > GameConfig::BASE_WIDTH + halfWidth) {
        posX = -halfWidth;
    } 
    else if (posX < -halfWidth) {
        posX = GameConfig::BASE_WIDTH + halfWidth;
    }
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Player::moveLeft() {
    velocityX = -PlayerConfig::MOVEMENT_SPEED;
    sprite.setTexture(*textureLeft);
}

void Player::moveRight() {
    velocityX = PlayerConfig::MOVEMENT_SPEED;
    sprite.setTexture(*textureRight);
}

void Player::stopMoving() {
    velocityX = 0.0f;
}

void Player::jump() {
    velocityY = PlayerConfig::JUMP_VELOCITY;
}

float Player::getX() const { return posX; }
float Player::getY() const { return posY; }
float Player::getVelocityY() const { return velocityY; }