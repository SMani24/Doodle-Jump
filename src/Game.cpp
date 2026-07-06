/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Game.hpp"
#include "Player.hpp"
#include "NormalPlatform.hpp"

Game::Game() : 
    window(sf::VideoMode(GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT), GameConfig::WINDOW_TITLE, sf::Style::Default),
    gameView(sf::FloatRect(0, 0, GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT)) 
{
    window.setFramerateLimit(GameConfig::FRAME_RATE); 

    textureManager.loadResource("doodle_left", "assets/left_doodle.png");
    textureManager.loadResource("doodle_right", "assets/right_doodle.png");
    textureManager.loadResource("platform_normal", "assets/normal_platform.png");

    player = std::make_unique<Player>(
        textureManager.getResource("doodle_left"), 
        textureManager.getResource("doodle_right")
    );

    platforms.push_back(std::make_unique<NormalPlatform>(
        textureManager.getResource("platform_normal"), 
        160.0f, 500.0f
    ));
}

Game::~Game() = default;

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
        }
    }
}

void Game::adjustViewport(unsigned int newWidth, unsigned int newHeight) {
    float targetRatio = static_cast<float>(GameConfig::BASE_WIDTH) / GameConfig::BASE_HEIGHT;
    float windowRatio = static_cast<float>(newWidth) / newHeight;
    
    float sizeX = 1.0f;
    float sizeY = 1.0f;
    float posX = 0.0f;
    float posY = 0.0f;

    bool isWindowWiderThanGame = windowRatio > targetRatio;

    if (isWindowWiderThanGame) {
        sizeX = targetRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    } else {
        sizeY = windowRatio / targetRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }

    gameView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void Game::update(sf::Time deltaTime) {
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
}

void Game::checkCollisions() {
    if (player->getVelocityY() > 0.0f) {
        sf::FloatRect playerBounds = player->getBounds();
        
        for (const auto& platform : platforms) {
            sf::FloatRect platBounds = platform->getBounds();
            
            if (playerBounds.intersects(platBounds)) {
                float playerBottom = playerBounds.top + playerBounds.height;
                
                if (playerBottom < platBounds.top + GameConfig::COLLISION_TOLERANCE) {
                    player->jump();
                    break;
                }
            }
        }
    }
}

void Game::render() {
    window.clear(sf::Color(240, 248, 255));
    window.setView(gameView);
    
    for (const auto& platform : platforms) {
        platform->draw(window);
    }
    
    player->draw(window);
    
    window.display();
}