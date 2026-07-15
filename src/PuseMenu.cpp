/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "PauseMenu.hpp"

PauseMenu::PauseMenu(std::shared_ptr<sf::Font> textFont, std::shared_ptr<sf::Texture> resumeTex, std::shared_ptr<sf::Texture> menuTex)
    : font(textFont)
{
    overlay.setSize(sf::Vector2f(GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT));
    overlay.setFillColor(PauseMenuConfig::OVERLAY_COLOR);

    titleText.setFont(*font);
    titleText.setString("PAUSED");
    titleText.setCharacterSize(PauseMenuConfig::TITLE_SIZE);
    titleText.setFillColor(PauseMenuConfig::TITLE_COLOR);
    titleText.setStyle(sf::Text::Bold);
    centerText(titleText, PauseMenuConfig::TITLE_Y);

    resumeButton = std::make_unique<Button>(resumeTex, GameConfig::BASE_WIDTH / 2.0f, PauseMenuConfig::RESUME_BTN_Y);
    resumeButton->setSize(PauseMenuConfig::BUTTON_WIDTH, PauseMenuConfig::BUTTON_HEIGHT);

    menuButton = std::make_unique<Button>(menuTex, GameConfig::BASE_WIDTH / 2.0f, PauseMenuConfig::MENU_BTN_Y);
    menuButton->setSize(PauseMenuConfig::BUTTON_WIDTH, PauseMenuConfig::BUTTON_HEIGHT);
}

void PauseMenu::centerText(sf::Text& text, float yPos) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(GameConfig::BASE_WIDTH / 2.0f, yPos);
}

void PauseMenu::update(const sf::RenderWindow& window, const sf::View& view) {
    resumeButton->update(window, view);
    menuButton->update(window, view);
}

void PauseMenu::draw(sf::RenderWindow& window) const {
    window.draw(overlay);
    window.draw(titleText);
    resumeButton->draw(window);
    menuButton->draw(window);
}

bool PauseMenu::isResumeClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const {
    return resumeButton->isClicked(window, view, event);
}

bool PauseMenu::isMenuClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const {
    return menuButton->isClicked(window, view, event);
}