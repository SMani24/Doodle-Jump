/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class Button {
private:
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;

public:
    Button(std::shared_ptr<sf::Texture> tex, float x, float y);
    ~Button() = default;

    void update(const sf::RenderWindow& window, const sf::View& view);
    void draw(sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const;
};

#endif // BUTTON_HPP