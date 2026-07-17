#include "Player.hpp"
#include "Game.hpp"

Player::Player(std::shared_ptr<sf::Texture> leftTex, std::shared_ptr<sf::Texture> rightTex, std::shared_ptr<sf::Texture> shootTex)
    : leftTexture(leftTex), rightTexture(rightTex), shootTexture(shootTex),
      posX(GameConfig::BASE_WIDTH / 2.0f), posY(0.0f), 
      velocityX(0.0f), velocityY(0.0f), 
      facingLeft(true), isShooting(false)
{
    sprite.setTexture(*leftTexture);
    sprite.setScale(PlayerConfig::SPRITE_SCALE, PlayerConfig::SPRITE_SCALE);
    
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height);
}

void Player::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
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
    velocityX = -PlayerConfig::MOVEMENT_SPEED;
    facingLeft = true;
    if (!isShooting) {
        sprite.setTexture(*leftTexture, true);
        
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.0f, bounds.height);
    }
}

void Player::moveRight() {
    velocityX = PlayerConfig::MOVEMENT_SPEED;
    facingLeft = false;
    if (!isShooting) {
        sprite.setTexture(*rightTexture, true);
        
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.0f, bounds.height);
    }
}

void Player::stopMoving() {
    velocityX = 0.0f;
}

void Player::jump() {
    velocityY = PlayerConfig::JUMP_VELOCITY;
}

void Player::superJump() {
    velocityY = PlayerConfig::SUPER_JUMP_VELOCITY;
}

float Player::getY() const { return posY; }

void Player::setY(float y) { 
    posY = y; 
    sprite.setPosition(posX, posY);
}

float Player::getVelocityY() const { return velocityY; }

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::setShooting(bool shooting) {
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