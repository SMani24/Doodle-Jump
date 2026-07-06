/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "GameOverMenu.hpp"

GameOverMenu::GameOverMenu(std::shared_ptr<sf::Font> textFont, std::shared_ptr<sf::Texture> restartTex, std::shared_ptr<sf::Texture> menuTex)
    : font(textFont)
{
    titleText.setFont(*font);
    titleText.setString("YOU LOST");
    titleText.setCharacterSize(GameOverConfig::TITLE_SIZE);
    titleText.setFillColor(GameOverConfig::TITLE_COLOR);
    titleText.setStyle(sf::Text::Bold);
    centerText(titleText, GameOverConfig::TITLE_Y);

    scoreText.setFont(*font);
    scoreText.setCharacterSize(GameOverConfig::SCORE_SIZE);
    scoreText.setFillColor(GameOverConfig::TEXT_COLOR);
    scoreText.setStyle(sf::Text::Bold);

    highScoreText.setFont(*font);
    highScoreText.setCharacterSize(GameOverConfig::SCORE_SIZE);
    highScoreText.setFillColor(GameOverConfig::TEXT_COLOR);
    highScoreText.setStyle(sf::Text::Bold);

    restartButton = std::make_unique<Button>(restartTex, GameConfig::BASE_WIDTH / 2.0f, GameOverConfig::RESTART_BTN_Y);
    menuButton = std::make_unique<Button>(menuTex, GameConfig::BASE_WIDTH / 2.0f, GameOverConfig::MENU_BTN_Y);
}

void GameOverMenu::centerText(sf::Text& text, float yPos) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(GameConfig::BASE_WIDTH / 2.0f, yPos);
}

void GameOverMenu::updateScores(int score, int highScore) {
    scoreText.setString("SCORE: " + std::to_string(score));
    centerText(scoreText, GameOverConfig::SCORE_Y);

    highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
    centerText(highScoreText, GameOverConfig::HIGH_SCORE_Y);
}

void GameOverMenu::update(const sf::RenderWindow& window, const sf::View& view) {
    restartButton->update(window, view);
    menuButton->update(window, view);
}

void GameOverMenu::draw(sf::RenderWindow& window) const {
    window.draw(titleText);
    window.draw(scoreText);
    window.draw(highScoreText);
    restartButton->draw(window);
    menuButton->draw(window);
}

bool GameOverMenu::isRestartClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const {
    return restartButton->isClicked(window, view, event);
}

bool GameOverMenu::isMenuClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const {
    return menuButton->isClicked(window, view, event);
}