/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace GameConfig {
    constexpr unsigned int BASE_WIDTH = 400;
    constexpr unsigned int BASE_HEIGHT = 600;
    const std::string WINDOW_TITLE = "Doodle Jump";
    constexpr unsigned int FRAME_RATE = 60;
}

class Game {
private:
    sf::RenderWindow window;
    sf::View gameView;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    
    void adjustViewport(unsigned int newWidth, unsigned int newHeight);

public:
    Game();
    ~Game() = default;
    
    void run();
};

#endif // GAME_HPP