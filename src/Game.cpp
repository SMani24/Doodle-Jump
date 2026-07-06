/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "Game.hpp"

Game::Game() : 
    window(sf::VideoMode(GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT), GameConfig::WINDOW_TITLE, sf::Style::Default),
    gameView(sf::FloatRect(0, 0, GameConfig::BASE_WIDTH, GameConfig::BASE_HEIGHT)) 
{
    window.setFramerateLimit(GameConfig::FRAME_RATE); 
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
}

void Game::render() {
    window.clear(sf::Color(240, 248, 255));
    
    window.setView(gameView);
    
    window.display();
}