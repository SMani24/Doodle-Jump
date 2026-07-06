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
#include <memory>
#include <vector>
#include "ResourceManager.hpp"

class Player;
class Platform;

namespace GameConfig {
    constexpr unsigned int BASE_WIDTH = 400;
    constexpr unsigned int BASE_HEIGHT = 600;
    const std::string WINDOW_TITLE = "Doodle Jump";
    constexpr unsigned int FRAME_RATE = 60;
    constexpr float COLLISION_TOLERANCE = 15.0f;
}

class Game {
private:
    sf::RenderWindow window;
    sf::View gameView;
    ResourceManager<sf::Texture> textureManager;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Platform>> platforms;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void adjustViewport(unsigned int newWidth, unsigned int newHeight);
    void checkCollisions();

public:
    Game();
    ~Game();
    
    void run();
};

#endif // GAME_HPP