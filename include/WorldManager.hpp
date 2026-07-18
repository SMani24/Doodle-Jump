/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef WORLD_MANAGER_HPP
#define WORLD_MANAGER_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include "ResourceManager.hpp"
#include "Monster.hpp"
#include "SettingsManager.hpp"

class Player;

namespace WorldConfig {
    constexpr float SCROLL_THRESHOLD = 300.0f; 
    constexpr float DESPAWN_Y = 650.0f;        
    constexpr float PLATFORM_X_MIN = 0.0f;
    constexpr float PLATFORM_X_MAX = 330.0f;   
    constexpr float PLATFORM_Y_MIN_GAP = 50.0f;
    constexpr float PLATFORM_Y_MAX_GAP = 140.0f;
    
    constexpr float START_X = 160.0f;
    constexpr float START_Y = 580.0f;
    constexpr float MAX_SAFE_JUMP_DISTANCE = 250.0f;
}

class WorldManager {
private:
    ResourceManager<sf::Texture>& textureManager;
    float highestPlatformY;
    float lastSafePlatformY;

    void spawnPlatform(std::vector<std::unique_ptr<Platform>>& platforms, float yPos);
    float getRandomX() const;
    float getRandomGap() const;
    int getRandomType() const;

public:
    WorldManager(ResourceManager<sf::Texture>& texManager);
    ~WorldManager() = default;

    void generateInitialWorld(std::vector<std::unique_ptr<Platform>>& platforms);
    
    float update(Player& player, std::vector<std::unique_ptr<Platform>>& platforms, 
                 std::vector<std::unique_ptr<Monster>>& monsters, Difficulty diff);
};

#endif