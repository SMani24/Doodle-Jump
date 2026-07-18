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
#include "Monster.hpp"
#include "BlackHole.hpp"
#include "ResourceManager.hpp"
#include "SettingsManager.hpp"

class Player;

namespace WorldConfig {
    constexpr float SCROLL_THRESHOLD = 300.0f; 
    constexpr float DESPAWN_Y = 650.0f;        
    constexpr float PLATFORM_X_MIN = 10.0f;
    constexpr float PLATFORM_X_MAX = 330.0f;   
    constexpr float PLATFORM_Y_MIN_GAP = 50.0f;
    constexpr float PLATFORM_Y_MAX_GAP = 140.0f;
    
    constexpr float START_X = 160.0f;
    constexpr float START_Y = 580.0f;
    
    constexpr float GRAVITY = 1200.0f;
    constexpr float JUMP_VELOCITY = 800.0f;
    constexpr float MOVEMENT_SPEED = 300.0f;

    constexpr int MONSTER_SCORE_THRESHOLD = 800;
    constexpr int HOLE_SCORE_THRESHOLD = 100;
}

class WorldManager {
private:
    ResourceManager<sf::Texture>& textureManager;
    float highestPlatformY;
    float lastSafePlatformY;
    float lastSafePlatformX;

    float getRandomX() const;
    float getRandomGap() const;
    int getRandomType() const;

    bool isSpaceClear(const sf::FloatRect& bounds, 
                      const std::vector<std::unique_ptr<Platform>>& platforms,
                      const std::vector<std::unique_ptr<Monster>>& monsters,
                      const std::vector<std::unique_ptr<BlackHole>>& blackHoles) const;

    bool isReachable(float startX, float startY, float targetX, float targetY) const;

public:
    WorldManager(ResourceManager<sf::Texture>& texManager);
    ~WorldManager() = default;

    void generateInitialWorld(std::vector<std::unique_ptr<Platform>>& platforms);
    
    float update(Player& player, int currentScore,
                 std::vector<std::unique_ptr<Platform>>& platforms, 
                 std::vector<std::unique_ptr<Monster>>& monsters, 
                 std::vector<std::unique_ptr<BlackHole>>& blackHoles,
                 Difficulty diff);
};

#endif