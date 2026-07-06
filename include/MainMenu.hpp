/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.hpp"
#include "Game.hpp" 

namespace MainMenuConfig {
    const sf::Color TEXT_COLOR = sf::Color(0, 51, 102); 
    constexpr unsigned int TITLE_SIZE = 40;
    constexpr unsigned int SCORE_SIZE = 24;
    constexpr unsigned int INSTRUCTION_SIZE = 18;
    
    constexpr float TITLE_Y = 150.0f;
    constexpr float SCORE_Y = 250.0f;
    constexpr float BUTTON_Y = 350.0f;
    constexpr float INSTRUCTION_Y = 450.0f;
}

class MainMenu {
private:
    std::shared_ptr<sf::Font> font;
    sf::Text titleText;
    sf::Text highScoreText;
    sf::Text instructionText;
    std::unique_ptr<Button> startButton;

    void centerText(sf::Text& text, float yPos);

public:
    MainMenu(std::shared_ptr<sf::Font> textFont, std::shared_ptr<sf::Texture> buttonTex);
    ~MainMenu() = default;

    void updateHighScore(int highScore);
    void update(const sf::RenderWindow& window, const sf::View& view);
    void draw(sf::RenderWindow& window) const;
    bool isStartClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const;
};

#endif // MAIN_MENU_HPP