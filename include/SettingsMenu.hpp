/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.hpp"
#include "SettingsManager.hpp"
#include "Game.hpp"

namespace SettingsMenuConfig {
    const sf::Color TEXT_COLOR = sf::Color(0, 51, 102);
    const sf::Color TRACK_COLOR = sf::Color(200, 200, 200);
    const sf::Color FILL_COLOR = sf::Color(0, 150, 255);
    
    constexpr float TITLE_Y = 80.0f;
    constexpr float VOLUME_TEXT_Y = 160.0f;
    constexpr float SLIDER_Y = 200.0f;
    constexpr float DIFF_TEXT_Y = 280.0f;
    constexpr float EASY_Y = 340.0f;
    constexpr float MEDIUM_Y = 410.0f;
    constexpr float HARD_Y = 480.0f;
    constexpr float BACK_Y = 550.0f;
    
    constexpr float SLIDER_WIDTH = 250.0f;
    constexpr float SLIDER_HEIGHT = 15.0f;
    constexpr float BUTTON_WIDTH = 200.0f;
    constexpr float BUTTON_HEIGHT = 50.0f;
}

class SettingsMenu {
private:
    std::shared_ptr<sf::Font> font;
    SettingsManager& settings;

    sf::Text titleText;
    sf::Text volumeText;
    sf::Text diffText;

    sf::RectangleShape sliderTrack;
    sf::RectangleShape sliderFill;

    std::unique_ptr<Button> easyButton;
    std::unique_ptr<Button> mediumButton;
    std::unique_ptr<Button> hardButton;
    std::unique_ptr<Button> backButton;

    void centerText(sf::Text& text, float yPos);
    void updateSliderVisuals();

public:
    SettingsMenu(std::shared_ptr<sf::Font> textFont, SettingsManager& settingsRef, 
                 std::shared_ptr<sf::Texture> easyTex, std::shared_ptr<sf::Texture> medTex, 
                 std::shared_ptr<sf::Texture> hardTex, std::shared_ptr<sf::Texture> backTex);
    ~SettingsMenu() = default;

    void update(const sf::RenderWindow& window, const sf::View& view);
    void draw(sf::RenderWindow& window) const;

    void processClick(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event);
    bool isBackClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const;
};

#endif // SETTINGS_MENU_HPP