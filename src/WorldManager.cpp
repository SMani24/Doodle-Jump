/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "WorldManager.hpp"
#include "NormalPlatform.hpp"
#include "MovingPlatform.hpp"
#include "BreakablePlatform.hpp"
#include "Game.hpp" 
#include "Player.hpp"
#include <algorithm>
#include <random>

WorldManager::WorldManager(ResourceManager<sf::Texture>& texManager) 
    : textureManager(texManager), highestPlatformY(GameConfig::BASE_HEIGHT), lastSafePlatformY(0.0f) {}

float WorldManager::getRandomX() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(WorldConfig::PLATFORM_X_MIN, WorldConfig::PLATFORM_X_MAX);
    return dis(gen);
}

float WorldManager::getRandomGap() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(WorldConfig::PLATFORM_Y_MIN_GAP, WorldConfig::PLATFORM_Y_MAX_GAP);
    return dis(gen);
}

int WorldManager::getRandomType() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 10);
    return dis(gen);
}

void WorldManager::spawnPlatform(std::vector<std::unique_ptr<Platform>>& platforms, float yPos) {
    float xPos = getRandomX();
    int type = getRandomType();

    if (type > 8) { 
        if ((lastSafePlatformY - yPos) + WorldConfig::PLATFORM_Y_MAX_GAP > WorldConfig::MAX_SAFE_JUMP_DISTANCE) {
            type = 1; 
        }
    }

    if (type <= 6) { 
        platforms.push_back(std::make_unique<NormalPlatform>(
            textureManager.getResource("platform_normal"), xPos, yPos));
        lastSafePlatformY = yPos;
    } 
    else if (type <= 8) { 
        platforms.push_back(std::make_unique<MovingPlatform>(
            textureManager.getResource("platform_moving"), xPos, yPos));
        lastSafePlatformY = yPos;
    } 
    else { 
        platforms.push_back(std::make_unique<BreakablePlatform>(
            textureManager.getResource("platform_broken"), xPos, yPos));
    }
}

void WorldManager::generateInitialWorld(std::vector<std::unique_ptr<Platform>>& platforms) {
    highestPlatformY = GameConfig::BASE_HEIGHT;
    lastSafePlatformY = WorldConfig::START_Y;
    
    platforms.push_back(std::make_unique<NormalPlatform>(
        textureManager.getResource("platform_normal"), 
        WorldConfig::START_X, WorldConfig::START_Y 
    ));

    while (highestPlatformY > 0.0f) {
        highestPlatformY -= getRandomGap();
        spawnPlatform(platforms, highestPlatformY);
    }
}

void WorldManager::update(Player& player, std::vector<std::unique_ptr<Platform>>& platforms) {
    if (player.getY() < WorldConfig::SCROLL_THRESHOLD) {
        float offset = WorldConfig::SCROLL_THRESHOLD - player.getY();
        
        player.setY(WorldConfig::SCROLL_THRESHOLD);
        highestPlatformY += offset;
        lastSafePlatformY += offset; 

        for (auto& platform : platforms) {
            platform->setY(platform->getY() + offset);
        }
    }

    while (highestPlatformY > 0.0f) {
        highestPlatformY -= getRandomGap();
        spawnPlatform(platforms, highestPlatformY);
    }

    platforms.erase(
        std::remove_if(platforms.begin(), platforms.end(),
            [](const std::unique_ptr<Platform>& p) {
                return p->getY() > WorldConfig::DESPAWN_Y;
            }),
        platforms.end()
    );
}