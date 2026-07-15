/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "ScoreManager.hpp"
#include "SettingsManager.hpp"
#include <fstream>
#include <algorithm>

ScoreManager::ScoreManager(std::shared_ptr<sf::Font> textFont) 
    : currentScore(0), highestReachedY(ScoreConfig::STARTING_Y), totalScrollOffset(0.0f), font(textFont) 
{
    highScores[0] = 0;
    highScores[1] = 0;
    highScores[2] = 0;

    loadHighScore();

    scoreText.setFont(*font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
}

void ScoreManager::loadHighScore() {
    std::ifstream file(ScoreConfig::SAVE_FILE);
    if (file.is_open()) {
        file >> highScores[0] >> highScores[1] >> highScores[2];
        file.close();
    }
}

void ScoreManager::saveHighScore() {
    std::ofstream file(ScoreConfig::SAVE_FILE);
    if (file.is_open()) {
        file << highScores[0] << " " << highScores[1] << " " << highScores[2];
        file.close();
    }
}

void ScoreManager::addOffset(float offset) {
    totalScrollOffset += offset;
}

void ScoreManager::update(float playerScreenY, Difficulty currentDifficulty) {
    float realWorldY = playerScreenY - totalScrollOffset;
    int diffIndex = static_cast<int>(currentDifficulty);

    if (realWorldY < highestReachedY) {
        highestReachedY = realWorldY;
        
        float distanceTraveled = ScoreConfig::STARTING_Y - highestReachedY;
        currentScore = static_cast<int>(distanceTraveled) * ScoreConfig::SCORE_MULTIPLIER;
        
        if (currentScore > highScores[diffIndex]) {
            highScores[diffIndex] = currentScore;
            saveHighScore();
        }
    }
    
    scoreText.setString("Score: " + std::to_string(currentScore));
}

void ScoreManager::resetCurrentScore() {
    currentScore = 0;
    highestReachedY = ScoreConfig::STARTING_Y;
    totalScrollOffset = 0.0f;
    scoreText.setString("Score: 0");
}

void ScoreManager::draw(sf::RenderWindow& window, const sf::View& view) const {
    sf::Text renderText = scoreText;
    sf::Vector2f viewTopLeft(view.getCenter().x - view.getSize().x / 2.0f, view.getCenter().y - view.getSize().y / 2.0f);
    
    renderText.setPosition(viewTopLeft.x + 10.0f, viewTopLeft.y + 10.0f);
    window.draw(renderText);
}

int ScoreManager::getHighScore(Difficulty currentDifficulty) const { 
    return highScores[static_cast<int>(currentDifficulty)]; 
}

int ScoreManager::getCurrentScore() const { 
    return currentScore; 
}