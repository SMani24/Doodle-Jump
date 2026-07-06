/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Game.hpp"
#include "Player.hpp"
#include "BreakablePlatform.hpp"
#include "MainMenu.hpp"
#include "ScoreManager.hpp"
#include "GameOverMenu.hpp"
#include <algorithm>

Game::Game() : 
    window(sf::VideoMode(GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT), GameConfig::WINDOW_TITLE, sf::Style::Default),
    gameView(sf::FloatRect(0, 0, GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT)),
    currentState(GameState::Menu),
    worldManager(textureManager) 
{
    window.setFramerateLimit(GameConfig::FRAME_RATE); 

    textureManager.loadResource("doodle_left", "assets/left_doodle.png");
    textureManager.loadResource("doodle_right", "assets/right_doodle.png");
    textureManager.loadResource("platform_normal", "assets/normal_platform.png");
    textureManager.loadResource("platform_moving", "assets/moving_platform.png");
    textureManager.loadResource("platform_broken", "assets/broken_platform.png");
    textureManager.loadResource("btn_start", "assets/start_button.png");
    textureManager.loadResource("btn_restart", "assets/restart_button.png");
    textureManager.loadResource("btn_menu", "assets/menu_button.png");
    textureManager.loadResource("bg", "assets/background.png");

    fontManager.loadResource("main_font", "fonts/ariblk.ttf");

    backgroundSprite.setTexture(*textureManager.getResource("bg"));
    backgroundFillSprite.setTexture(*textureManager.getResource("bg"));
    backgroundFillSprite.setColor(sf::Color(100, 100, 100)); 
    scaleBackgroundFill(GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT);

    scoreManager = std::make_unique<ScoreManager>(fontManager.getResource("main_font"));
    
    mainMenu = std::make_unique<MainMenu>(
        fontManager.getResource("main_font"), 
        textureManager.getResource("btn_start")
    );
    mainMenu->updateHighScore(scoreManager->getHighScore());

    gameOverMenu = std::make_unique<GameOverMenu>(
        fontManager.getResource("main_font"),
        textureManager.getResource("btn_restart"),
        textureManager.getResource("btn_menu")
    );

    resetGame();
}

Game::~Game() = default;

void Game::resetGame() {
    platforms.clear();
    
    player = std::make_unique<Player>(
        textureManager.getResource("doodle_left"), 
        textureManager.getResource("doodle_right")
    );
    
    worldManager.generateInitialWorld(platforms);
    scoreManager->resetCurrentScore();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart(); 
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::Resized) {
            adjustViewport(event.size.width, event.size.height);
            scaleBackgroundFill(event.size.width, event.size.height);
        }

        if (currentState == GameState::Menu) {
            if (mainMenu->isStartClicked(window, gameView, event)) {
                currentState = GameState::Playing;
                resetGame();
            }
        } 
        else if (currentState == GameState::GameOver) {
            if (gameOverMenu->isRestartClicked(window, gameView, event)) {
                currentState = GameState::Playing;
                resetGame();
            }
            else if (gameOverMenu->isMenuClicked(window, gameView, event)) {
                currentState = GameState::Menu;
                resetGame();
                mainMenu->updateHighScore(scoreManager->getHighScore());
            }
        }
    }
}

void Game::adjustViewport(unsigned int newWidth, unsigned int newHeight) {
    float targetRatio = static_cast<float>(GameConfig::BASE_WIDTH) / GameConfig::BASE_HEIGHT;
    float windowRatio = static_cast<float>(newWidth) / newHeight;
    float sizeX = 1.0f, sizeY = 1.0f, posX = 0.0f, posY = 0.0f;

    if (windowRatio > targetRatio) {
        sizeX = targetRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    } else {
        sizeY = windowRatio / targetRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }
    gameView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void Game::scaleBackgroundFill(unsigned int newWidth, unsigned int newHeight) {
    sf::FloatRect bounds = backgroundFillSprite.getLocalBounds();
    float scaleX = static_cast<float>(newWidth) / bounds.width;
    float scaleY = static_cast<float>(newHeight) / bounds.height;
    float finalScale = std::max(scaleX, scaleY);

    backgroundFillSprite.setScale(finalScale, finalScale);
    
    float scaledWidth = bounds.width * finalScale;
    float scaledHeight = bounds.height * finalScale;
    backgroundFillSprite.setPosition((newWidth - scaledWidth) / 2.0f, (newHeight - scaledHeight) / 2.0f);
}

void Game::update(sf::Time deltaTime) {
    if (currentState == GameState::Menu) {
        mainMenu->update(window, gameView);
    } 
    else if (currentState == GameState::GameOver) {
        gameOverMenu->update(window, gameView);
    }
    else if (currentState == GameState::Playing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player->moveLeft();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player->moveRight();
        } else {
            player->stopMoving();
        }

        player->update(deltaTime);
        
        for (auto& platform : platforms) {
            platform->update(deltaTime);
        }

        checkCollisions();
        
        float scrollOffset = worldManager.update(*player, platforms);
        scoreManager->addOffset(scrollOffset);
        scoreManager->update(player->getY());

        if (player->getY() > gameView.getCenter().y + GameConfig::DEATH_Y_OFFSET) {
            currentState = GameState::GameOver;
            gameOverMenu->updateScores(scoreManager->getCurrentScore(), scoreManager->getHighScore());
        }
    }
}

void Game::checkCollisions() {
    if (player->getVelocityY() > 0.0f) {
        sf::FloatRect playerBounds = player->getBounds();
        
        for (const auto& platform : platforms) {
            sf::FloatRect platBounds = platform->getBounds();
            
            if (playerBounds.intersects(platBounds)) {
                float playerBottom = playerBounds.top + playerBounds.height;
                
                if (playerBottom < platBounds.top + GameConfig::COLLISION_TOLERANCE) {
                    BreakablePlatform* breakable = dynamic_cast<BreakablePlatform*>(platform.get());
                    if (breakable != nullptr) {
                        if (!breakable->getIsBroken()) {
                            breakable->breakPlatform();
                        }
                    } else {
                        player->jump();
                        break;
                    }
                }
            }
        }
    }
}

void Game::render() {
    window.clear();
    
    window.setView(window.getDefaultView());
    window.draw(backgroundFillSprite);
    
    window.setView(gameView);
    window.draw(backgroundSprite);
    
    if (currentState == GameState::Menu) {
        mainMenu->draw(window);
    } 
    else if (currentState == GameState::Playing) {
        for (const auto& platform : platforms) {
            platform->draw(window);
        }
        player->draw(window);
        scoreManager->draw(window, gameView);
    }
    else if (currentState == GameState::GameOver) {
        for (const auto& platform : platforms) {
            platform->draw(window);
        }
        gameOverMenu->draw(window);
    }
    
    window.display();
}