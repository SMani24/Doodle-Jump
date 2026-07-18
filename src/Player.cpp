/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Player.hpp"
#include "Game.hpp" 
#include <cmath>

Player::Player(std::shared_ptr<sf::Texture> leftTex, std::shared_ptr<sf::Texture> rightTex, std::shared_ptr<sf::Texture> shootTex)
    : leftTexture(leftTex), rightTexture(rightTex), shootTexture(shootTex),
      posX(GameConfig::BASE_WIDTH / 2.0f), posY(0.0f), 
      velocityX(0.0f), velocityY(0.0f), 
      facingLeft(true), isShooting(false),
      isBeingSucked(false), suctionRadius(0.0f), suctionAngle(0.0f), suctionScale(PlayerConfig::SPRITE_SCALE)
{
    sprite.setTexture(*leftTexture);
    sprite.setScale(PlayerConfig::SPRITE_SCALE, PlayerConfig::SPRITE_SCALE);
    
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height);
}

void Player::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();

    if (isBeingSucked) {
        suctionRadius -= PlayerConfig::SUCTION_PULL_SPEED * dt;
        suctionAngle += PlayerConfig::SUCTION_ANGLE_SPEED * dt;
        suctionScale -= PlayerConfig::SUCTION_SHRINK_SPEED * dt;

        if (suctionRadius < 0.0f) suctionRadius = 0.0f;
        if (suctionScale < 0.0f) suctionScale = 0.0f;

        posX = suctionTarget.x + suctionRadius * std::cos(suctionAngle);
        posY = suctionTarget.y + suctionRadius * std::sin(suctionAngle);

        sprite.setPosition(posX, posY);
        sprite.setScale(suctionScale, suctionScale);
        sprite.rotate(PlayerConfig::SUCTION_ROTATION_SPEED * dt);
        
        return; 
    }

    velocityY += PlayerConfig::GRAVITY * dt;
    posY += velocityY * dt;
    posX += velocityX * dt;

    if (posX > GameConfig::BASE_WIDTH) {
        posX = 0.0f;
    } else if (posX < 0.0f) {
        posX = GameConfig::BASE_WIDTH;
    }

    sprite.setPosition(posX, posY);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Player::moveLeft() {
    if (isBeingSucked) return;
    velocityX = -PlayerConfig::MOVEMENT_SPEED;
    facingLeft = true;
    if (!isShooting) {
        sprite.setTexture(*leftTexture, true);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.0f, bounds.height);
    }
}

void Player::moveRight() {
    if (isBeingSucked) return;
    velocityX = PlayerConfig::MOVEMENT_SPEED;
    facingLeft = false;
    if (!isShooting) {
        sprite.setTexture(*rightTexture, true);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.0f, bounds.height);
    }
}

void Player::stopMoving() {
    if (isBeingSucked) return;
    velocityX = 0.0f;
}

void Player::jump() {
    if (isBeingSucked) return;
    velocityY = PlayerConfig::JUMP_VELOCITY;
}

void Player::superJump() {
    if (isBeingSucked) return;
    velocityY = PlayerConfig::SUPER_JUMP_VELOCITY;
}

float Player::getY() const { return posY; }

void Player::setY(float y) { 
    if (isBeingSucked) return;
    posY = y; 
    sprite.setPosition(posX, posY);
}

float Player::getVelocityY() const { return velocityY; }

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void Player::setShooting(bool shooting) {
    if (isBeingSucked) return;
    if (isShooting == shooting) return; 

    isShooting = shooting;
    
    if (isShooting) {
        sprite.setTexture(*shootTexture, true);
    } else {
        sprite.setTexture(facingLeft ? *leftTexture : *rightTexture, true);
    }

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height);
}

sf::Vector2f Player::getShootPosition() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top);
}

void Player::startSuction(sf::Vector2f targetCenter) {
    if (isBeingSucked) return;
    
    isBeingSucked = true;
    suctionTarget = targetCenter;
    
    float dx = posX - suctionTarget.x;
    float dy = posY - suctionTarget.y;
    suctionRadius = std::sqrt(dx * dx + dy * dy);
    suctionAngle = std::atan2(dy, dx);
}

bool Player::isSuctionComplete() const {
    return isBeingSucked && suctionScale <= 0.0f;
}