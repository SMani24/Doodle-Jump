/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.hpp"
#include "Game.hpp"

namespace PauseMenuConfig {
    const sf::Color TITLE_COLOR = sf::Color(0, 51, 102);
    const sf::Color OVERLAY_COLOR = sf::Color(0, 0, 0, 150); 
    
    constexpr unsigned int TITLE_SIZE = 40;
    
    constexpr float TITLE_Y = 150.0f;
    constexpr float RESUME_BTN_Y = 300.0f;
    constexpr float MENU_BTN_Y = 400.0f;
    
    constexpr float BUTTON_WIDTH = 240.0f;
    constexpr float BUTTON_HEIGHT = 60.0f;
}

class PauseMenu {
private:
    std::shared_ptr<sf::Font> font;
    sf::RectangleShape overlay;
    sf::Text titleText;
    
    std::unique_ptr<Button> resumeButton;
    std::unique_ptr<Button> menuButton;

    void centerText(sf::Text& text, float yPos);

public:
    PauseMenu(std::shared_ptr<sf::Font> textFont, std::shared_ptr<sf::Texture> resumeTex, std::shared_ptr<sf::Texture> menuTex);
    ~PauseMenu() = default;

    void update(const sf::RenderWindow& window, const sf::View& view);
    void draw(sf::RenderWindow& window) const;

    bool isResumeClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const;
    bool isMenuClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const;
};

#endif // PAUSE_MENU_HPP