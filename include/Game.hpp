#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>
#include "ResourceManager.hpp"
#include "WorldManager.hpp"
#include "Button.hpp"

class Player;
class MainMenu;
class ScoreManager;

enum class GameState {
    Menu,
    Playing,
    GameOver
};

namespace GameConfig {
    constexpr unsigned int BASE_WIDTH = 400;
    constexpr unsigned int BASE_HEIGHT = 600;
    const std::string WINDOW_TITLE = "Doodle Jump";
    constexpr unsigned int FRAME_RATE = 60;
    constexpr float COLLISION_TOLERANCE = 15.0f;
    constexpr float DEATH_Y_OFFSET = 600.0f;
}

class Game {
private:
    sf::RenderWindow window;
    sf::View gameView;
    GameState currentState;
    
    ResourceManager<sf::Texture> textureManager;
    ResourceManager<sf::Font> fontManager;
    WorldManager worldManager;
    
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Platform>> platforms;

    std::unique_ptr<ScoreManager> scoreManager;
    std::unique_ptr<MainMenu> mainMenu;

    sf::Sprite backgroundSprite;
    sf::Sprite backgroundFillSprite;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void adjustViewport(unsigned int newWidth, unsigned int newHeight);
    void scaleBackgroundFill(unsigned int newWidth, unsigned int newHeight);
    void checkCollisions();
    void resetGame();

public:
    Game();
    ~Game();
    
    void run();
};

#endif // GAME_HPP