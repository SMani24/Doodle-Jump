/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef GAME_OVER_MENU_HPP
#define GAME_OVER_MENU_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.hpp"
#include "Game.hpp"

namespace GameOverConfig {
    const sf::Color TITLE_COLOR = sf::Color(255, 0, 0);
    const sf::Color TEXT_COLOR = sf::Color(0, 51, 102);
    const sf::Color OVERLAY_COLOR = sf::Color(255, 255, 255, 210); 
    
    constexpr unsigned int TITLE_SIZE = 40;
    constexpr unsigned int SCORE_SIZE = 24;
    
    constexpr float TITLE_Y = 150.0f;
    constexpr float SCORE_Y = 250.0f;
    constexpr float HIGH_SCORE_Y = 300.0f;
    constexpr float RESTART_BTN_Y = 400.0f;
    constexpr float MENU_BTN_Y = 480.0f;
    constexpr float BUTTON_SCALE = 0.6f;
}

class GameOverMenu {
private:
    std::shared_ptr<sf::Font> font;
    sf::RectangleShape overlay;
    sf::Text titleText;
    sf::Text scoreText;
    sf::Text highScoreText;
    std::unique_ptr<Button> restartButton;
    std::unique_ptr<Button> menuButton;

    void centerText(sf::Text& text, float yPos);

public:
    GameOverMenu(std::shared_ptr<sf::Font> textFont, std::shared_ptr<sf::Texture> restartTex, std::shared_ptr<sf::Texture> menuTex);
    ~GameOverMenu() = default;

    void updateScores(int score, int highScore);
    void update(const sf::RenderWindow& window, const sf::View& view);
    void draw(sf::RenderWindow& window) const;

    bool isRestartClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const;
    bool isMenuClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const;
};

#endif // GAME_OVER_MENU_HPP