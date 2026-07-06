/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<sf::Font> textFont, std::shared_ptr<sf::Texture> buttonTex)
    : font(textFont)
{
    titleText.setFont(*font);
    titleText.setString("DOODLE JUMP");
    titleText.setCharacterSize(MainMenuConfig::TITLE_SIZE);
    titleText.setFillColor(MainMenuConfig::TEXT_COLOR);
    titleText.setStyle(sf::Text::Bold);
    centerText(titleText, MainMenuConfig::TITLE_Y);

    highScoreText.setFont(*font);
    highScoreText.setCharacterSize(MainMenuConfig::SCORE_SIZE);
    highScoreText.setFillColor(MainMenuConfig::TEXT_COLOR);
    highScoreText.setStyle(sf::Text::Bold);

    instructionText.setFont(*font);
    instructionText.setString("Use Left / Right arrows to move");
    instructionText.setCharacterSize(MainMenuConfig::INSTRUCTION_SIZE);
    instructionText.setFillColor(MainMenuConfig::TEXT_COLOR);
    instructionText.setStyle(sf::Text::Bold);
    centerText(instructionText, MainMenuConfig::INSTRUCTION_Y);

    startButton = std::make_unique<Button>(buttonTex, GameConfig::BASE_WIDTH / 2.0f, MainMenuConfig::BUTTON_Y);
}

void MainMenu::centerText(sf::Text& text, float yPos) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(GameConfig::BASE_WIDTH / 2.0f, yPos);
}

void MainMenu::updateHighScore(int highScore) {
    highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
    centerText(highScoreText, MainMenuConfig::SCORE_Y);
}

void MainMenu::update(const sf::RenderWindow& window, const sf::View& view) {
    startButton->update(window, view);
}

void MainMenu::draw(sf::RenderWindow& window) const {
    window.draw(titleText);
    window.draw(highScoreText);
    window.draw(instructionText);
    startButton->draw(window);
}

bool MainMenu::isStartClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const {
    return startButton->isClicked(window, view, event);
}