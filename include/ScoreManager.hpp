/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

namespace ScoreConfig {
    const std::string SAVE_FILE = "highscore.txt";
    constexpr int SCORE_MULTIPLIER = 10;
    constexpr float STARTING_Y = 400.0f; 
}

class ScoreManager {
private:
    int currentScore;
    int highScore;
    float highestReachedY;
    
    sf::Text scoreText;
    std::shared_ptr<sf::Font> font;

    void loadHighScore();
    void saveHighScore();

public:
    ScoreManager(std::shared_ptr<sf::Font> textFont);
    ~ScoreManager() = default;

    void update(float playerY);
    void resetCurrentScore();
    void draw(sf::RenderWindow& window, const sf::View& view) const;
    
    int getHighScore() const;
    int getCurrentScore() const;
};

#endif // SCORE_MANAGER_HPP