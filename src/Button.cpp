/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Button.hpp"

Button::Button(std::shared_ptr<sf::Texture> tex, float x, float y) : texture(tex) {
    sprite.setTexture(*texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
    sprite.setPosition(x, y);
}

void Button::update(const sf::RenderWindow& window, const sf::View& view) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    
    if (sprite.getGlobalBounds().contains(mousePos)) {
        sprite.setColor(sf::Color(200, 200, 200)); 
    } else {
        sprite.setColor(sf::Color::White);
    }
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Button::isClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
        return sprite.getGlobalBounds().contains(mousePos);
    }
    return false;
}

void Button::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}