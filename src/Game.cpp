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
#include "PauseMenu.hpp"
#include "SettingsManager.hpp"
#include "SettingsMenu.hpp"
#include "Bullet.hpp"
#include "Monster.hpp"
#include <algorithm>

Game::Game() : 
    window(sf::VideoMode(GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT), GameConfig::WINDOW_TITLE, sf::Style::Default),
    gameView(sf::FloatRect(0, 0, GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT)),
    backgroundView(sf::FloatRect(0, 0, GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT)),
    currentState(GameState::Menu),
    worldManager(textureManager),
    fireTimer(sf::seconds(10.0f))
{
    window.setFramerateLimit(GameConfig::FRAME_RATE); 

    textureManager.loadResource("doodle_left", "assets/left_doodle.png");
    textureManager.loadResource("doodle_right", "assets/right_doodle.png");
    textureManager.loadResource("doodle_shoot", "assets/doodle_shoot.png");
    textureManager.loadResource("platform_normal", "assets/normal_platform.png");
    textureManager.loadResource("platform_moving", "assets/moving_platform.png");
    textureManager.loadResource("platform_broken", "assets/broken_platform.png");
    textureManager.loadResource("spring", "assets/spring.png");
    textureManager.loadResource("bg", "assets/background.png");
    textureManager.loadResource("bullet", "assets/bullet.png");
    textureManager.loadResource("monster_blue", "assets/blue_monster.png");
    textureManager.loadResource("monster_green", "assets/green_monster.png");
    
    textureManager.loadResource("btn_start", "assets/start_button.png");
    textureManager.loadResource("btn_restart", "assets/restart_button.png");
    textureManager.loadResource("btn_menu", "assets/menu_button.png");
    textureManager.loadResource("btn_resume", "assets/resume_button.png");
    textureManager.loadResource("btn_settings", "assets/settings_button.png");
    textureManager.loadResource("btn_easy", "assets/easy_button.png");
    textureManager.loadResource("btn_medium", "assets/medium_button.png");
    textureManager.loadResource("btn_hard", "assets/hard_button.png");
    textureManager.loadResource("btn_back", "assets/back_button.png");

    fontManager.loadResource("main_font", "fonts/ariblk.ttf");

    audioManager.loadResource("sfx_jump", "sounds/Jumping_Sound.wav");
    audioManager.loadResource("sfx_lose", "sounds/Loosing_Sound.wav");
    audioManager.loadResource("sfx_shoot", "sounds/Shooting_Sound.wav");

    backgroundSprite.setTexture(*textureManager.getResource("bg"));
    backgroundFillSprite.setTexture(*textureManager.getResource("bg"));
    backgroundFillSprite.setColor(sf::Color(100, 100, 100)); 
    scaleBackgroundFill(GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT);

    settingsManager = std::make_unique<SettingsManager>();
    soundManager = std::make_unique<SoundManager>();
    soundManager->setVolume(settingsManager->getVolume());
    soundManager->playMusic("sounds/MainMenu_Song.flac");

    scoreManager = std::make_unique<ScoreManager>(fontManager.getResource("main_font"));
    
    mainMenu = std::make_unique<MainMenu>(
        fontManager.getResource("main_font"), 
        textureManager.getResource("btn_start"),
        textureManager.getResource("btn_settings")
    );
    mainMenu->updateHighScore(scoreManager->getHighScore(settingsManager->getDifficulty()));

    settingsMenu = std::make_unique<SettingsMenu>(
        fontManager.getResource("main_font"), *settingsManager,
        textureManager.getResource("btn_easy"), textureManager.getResource("btn_medium"),
        textureManager.getResource("btn_hard"), textureManager.getResource("btn_back")
    );

    gameOverMenu = std::make_unique<GameOverMenu>(
        fontManager.getResource("main_font"),
        textureManager.getResource("btn_restart"),
        textureManager.getResource("btn_menu")
    );

    pauseMenu = std::make_unique<PauseMenu>(
        fontManager.getResource("main_font"),
        textureManager.getResource("btn_resume"),
        textureManager.getResource("btn_menu")
    );

    resetGame();
}

Game::~Game() = default;

void Game::resetGame() {
    platforms.clear();
    monsters.clear();
    bullets.clear();
    
    player = std::make_unique<Player>(
        textureManager.getResource("doodle_left"), 
        textureManager.getResource("doodle_right"),
        textureManager.getResource("doodle_shoot")
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
            backgroundView.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            backgroundView.setCenter(event.size.width / 2.0f, event.size.height / 2.0f);
            adjustViewport(event.size.width, event.size.height);
            scaleBackgroundFill(event.size.width, event.size.height);
        }

        if (currentState == GameState::Menu) {
            if (mainMenu->isStartClicked(window, gameView, event)) {
                currentState = GameState::Playing;
                soundManager->pauseMusic();
                resetGame();
            }
            else if (mainMenu->isSettingsClicked(window, gameView, event)) {
                currentState = GameState::Settings;
            }
        } 
        else if (currentState == GameState::Settings) {
            settingsMenu->processClick(window, gameView, event);
            if (settingsMenu->isBackClicked(window, gameView, event)) {
                settingsManager->saveSettings(); 
                currentState = GameState::Menu;
                mainMenu->updateHighScore(scoreManager->getHighScore(settingsManager->getDifficulty()));
            }
        }
        else if (currentState == GameState::Playing) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentState = GameState::Paused;
            }
        }
        else if (currentState == GameState::Paused) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentState = GameState::Playing;
            }
            else if (pauseMenu->isResumeClicked(window, gameView, event)) {
                currentState = GameState::Playing;
            }
            else if (pauseMenu->isMenuClicked(window, gameView, event)) {
                currentState = GameState::Menu;
                soundManager->resumeMusic();
                resetGame();
                mainMenu->updateHighScore(scoreManager->getHighScore(settingsManager->getDifficulty()));
            }
        }
        else if (currentState == GameState::GameOver) {
            if (gameOverMenu->isRestartClicked(window, gameView, event)) {
                currentState = GameState::Playing;
                resetGame();
            }
            else if (gameOverMenu->isMenuClicked(window, gameView, event)) {
                currentState = GameState::Menu;
                soundManager->resumeMusic();
                resetGame();
                mainMenu->updateHighScore(scoreManager->getHighScore(settingsManager->getDifficulty()));
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
    else if (currentState == GameState::Settings) {
        settingsMenu->update(window, gameView);
        soundManager->setVolume(settingsManager->getVolume());
    }
    else if (currentState == GameState::Paused) {
        pauseMenu->update(window, gameView);
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player->setShooting(true);
            fireTimer += deltaTime;

            float fireDelay = 0.4f;
            if (settingsManager->getDifficulty() == Difficulty::Easy) fireDelay = 0.2f;
            else if (settingsManager->getDifficulty() == Difficulty::Hard) fireDelay = 0.6f;

            if (fireTimer.asSeconds() >= fireDelay) {
                sf::Vector2f spawnPos = player->getShootPosition();
                bullets.push_back(std::make_unique<Bullet>(
                    textureManager.getResource("bullet"), spawnPos.x, spawnPos.y
                ));
                soundManager->playSound(*audioManager.getResource("sfx_shoot"));
                fireTimer = sf::Time::Zero;
            }
        } else {
            player->setShooting(false);
            fireTimer = sf::seconds(10.0f);
        }

        for (auto& bullet : bullets) {
            bullet->update(deltaTime);
        }

        float topOfCamera = gameView.getCenter().y - (GameConfig::BASE_HEIGHT / 2.0f);
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [topOfCamera](const std::unique_ptr<Bullet>& b) {
                    return b->getY() < topOfCamera || !b->isActive();
                }),
            bullets.end()
        );

        player->update(deltaTime);
        
        for (auto& platform : platforms) {
            platform->update(deltaTime);
        }

        for (auto& monster : monsters) {
            monster->update(deltaTime);
        }

        monsters.erase(
            std::remove_if(monsters.begin(), monsters.end(),
                [](const std::unique_ptr<Monster>& m) {
                    return !m->isAlive();
                }),
            monsters.end()
        );

        checkCollisions();
        
        float scrollOffset = worldManager.update(*player, platforms, monsters, settingsManager->getDifficulty());
        scoreManager->addOffset(scrollOffset);
        
        scoreManager->update(player->getY(), settingsManager->getDifficulty());

        if (player->getY() > gameView.getCenter().y + GameConfig::DEATH_Y_OFFSET) {
            currentState = GameState::GameOver;
            soundManager->playSound(*audioManager.getResource("sfx_lose"));
            gameOverMenu->updateScores(scoreManager->getCurrentScore(), scoreManager->getHighScore(settingsManager->getDifficulty()));
        }
    }
}

void Game::checkCollisions() {
    for (auto& bullet : bullets) {
        if (!bullet->isActive()) continue;
        
        for (auto& monster : monsters) {
            if (!monster->isAlive()) continue;

            if (bullet->getBounds().intersects(monster->getBounds())) {
                monster->takeDamage();
                bullet->deactivate();
                break;
            }
        }
    }

    sf::FloatRect playerBounds = player->getBounds();
    float playerBottom = playerBounds.top + playerBounds.height;

    for (auto& monster : monsters) {
        if (!monster->isAlive()) continue;

        sf::FloatRect monsterBounds = monster->getBounds();
        
        if (playerBounds.intersects(monsterBounds)) {
            if (player->getVelocityY() > 0.0f && playerBottom < monsterBounds.top + (monsterBounds.height / 2.0f)) {
                player->superJump();
                soundManager->playSound(*audioManager.getResource("sfx_jump"));
                monster->takeDamage();
            } else {
                currentState = GameState::GameOver;
                soundManager->playSound(*audioManager.getResource("sfx_lose"));
                gameOverMenu->updateScores(scoreManager->getCurrentScore(), scoreManager->getHighScore(settingsManager->getDifficulty()));
                return; 
            }
        }
    }

    if (player->getVelocityY() > 0.0f) {
        for (const auto& platform : platforms) {
            if (platform->hasSpring()) {
                sf::FloatRect springBounds = platform->getSpringBounds();
                if (playerBounds.intersects(springBounds) && playerBottom < springBounds.top + GameConfig::COLLISION_TOLERANCE) {
                    platform->compressSpring();
                    player->superJump();
                    soundManager->playSound(*audioManager.getResource("sfx_jump"));
                    return; 
                }
            }

            sf::FloatRect platBounds = platform->getBounds();
            
            if (playerBounds.intersects(platBounds) && playerBottom < platBounds.top + GameConfig::COLLISION_TOLERANCE) {
                BreakablePlatform* breakable = dynamic_cast<BreakablePlatform*>(platform.get());
                
                if (breakable != nullptr) {
                    if (!breakable->getIsBroken()) {
                        breakable->breakPlatform();
                    }
                } else {
                    player->jump();
                    soundManager->playSound(*audioManager.getResource("sfx_jump"));
                    return; 
                }
            }
        }
    }
}

void Game::render() {
    window.clear();
    
    window.setView(backgroundView);
    window.draw(backgroundFillSprite);
    
    window.setView(gameView);
    window.draw(backgroundSprite);
    
    if (currentState == GameState::Menu) {
        mainMenu->draw(window);
    } 
    else if (currentState == GameState::Settings) {
        settingsMenu->draw(window);
    }
    else if (currentState == GameState::Playing) {
        for (const auto& platform : platforms) {
            platform->draw(window);
        }
        for (const auto& monster : monsters) {
            monster->draw(window);
        }
        for (const auto& bullet : bullets) {
            bullet->draw(window);
        }
        player->draw(window);
        scoreManager->draw(window, gameView);
    }
    else if (currentState == GameState::Paused) {
        for (const auto& platform : platforms) {
            platform->draw(window);
        }
        for (const auto& monster : monsters) {
            monster->draw(window);
        }
        for (const auto& bullet : bullets) {
            bullet->draw(window);
        }
        player->draw(window);
        scoreManager->draw(window, gameView);
        
        pauseMenu->draw(window);
    }
    else if (currentState == GameState::GameOver) {
        for (const auto& platform : platforms) {
            platform->draw(window);
        }
        gameOverMenu->draw(window);
    }
    
    window.display();
}