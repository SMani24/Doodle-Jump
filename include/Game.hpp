/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
#include <vector>
#include "ResourceManager.hpp"
#include "WorldManager.hpp"
#include "SoundManager.hpp"
#include "Button.hpp"
#include "BlackHole.hpp"

class Player;
class MainMenu;
class ScoreManager;
class GameOverMenu;
class PauseMenu;
class SettingsManager;
class SettingsMenu;
class Bullet;
class Monster;

enum class GameState {
    Menu,
    Settings,
    Playing,
    Paused,
    GameOver
};

namespace GameConfig {
    constexpr unsigned int BASE_WIDTH = 400;
    constexpr unsigned int BASE_HEIGHT = 600;
    const std::string WINDOW_TITLE = "Doodle Jump";
    constexpr unsigned int FRAME_RATE = 60;
    constexpr float COLLISION_TOLERANCE = 15.0f;
    constexpr float DEATH_Y_OFFSET = 300.0f;
    
    constexpr float FIRE_DELAY_EASY = 0.2f;
    constexpr float FIRE_DELAY_MEDIUM = 0.4f;
    constexpr float FIRE_DELAY_HARD = 0.6f;
}

class Game {
private:
    sf::RenderWindow window;
    sf::View gameView;
    sf::View backgroundView;
    GameState currentState;
    
    ResourceManager<sf::Texture> textureManager;
    ResourceManager<sf::Font> fontManager;
    ResourceManager<sf::SoundBuffer> audioManager;
    WorldManager worldManager;
    
    std::unique_ptr<SoundManager> soundManager;
    std::unique_ptr<SettingsManager> settingsManager;
    std::unique_ptr<ScoreManager> scoreManager;
    
    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<GameOverMenu> gameOverMenu;
    std::unique_ptr<PauseMenu> pauseMenu;
    std::unique_ptr<SettingsMenu> settingsMenu;

    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Platform>> platforms;
    std::vector<std::unique_ptr<Monster>> monsters;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<BlackHole>> blackHoles;

    sf::Time fireTimer;
    bool isSuckedIntoHole;

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

#endif