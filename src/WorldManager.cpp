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
#include "BlueMonster.hpp"
#include "GreenMonster.hpp"
#include "Game.hpp" 
#include "Player.hpp"
#include <algorithm>
#include <random>
#include <cmath>

WorldManager::WorldManager(ResourceManager<sf::Texture>& texManager) 
    : textureManager(texManager), highestPlatformY(GameConfig::BASE_HEIGHT), 
      lastSafePlatformY(0.0f), lastSafePlatformX(0.0f) {}

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

bool WorldManager::isSpaceClear(const sf::FloatRect& bounds, 
                                const std::vector<std::unique_ptr<Platform>>& platforms,
                                const std::vector<std::unique_ptr<Monster>>& monsters,
                                const std::vector<std::unique_ptr<BlackHole>>& blackHoles) const {
    for (const auto& p : platforms) {
        if (p->getBounds().intersects(bounds)) return false;
    }
    for (const auto& m : monsters) {
        if (m->getBounds().intersects(bounds)) return false;
    }
    for (const auto& b : blackHoles) {
        if (b->getBounds().intersects(bounds)) return false;
    }
    return true;
}

bool WorldManager::isReachable(float startX, float startY, float targetX, float targetY) const {
    float dy = startY - targetY;
    if (dy < 0.0f) return true; 

    float dx = std::abs(targetX - startX);
    if (dx > GameConfig::BASE_WIDTH / 2.0f) {
        dx = GameConfig::BASE_WIDTH - dx;
    }

    float maxJumpY = (WorldConfig::JUMP_VELOCITY * WorldConfig::JUMP_VELOCITY) / (2.0f * WorldConfig::GRAVITY);
    
    if (dy > maxJumpY) return false;

    float timeToApex = WorldConfig::JUMP_VELOCITY / WorldConfig::GRAVITY;
    float fallDistance = maxJumpY - dy;
    float timeToFall = std::sqrt((2.0f * fallDistance) / WorldConfig::GRAVITY);
    
    float maxDx = (timeToApex + timeToFall) * WorldConfig::MOVEMENT_SPEED;

    return dx <= maxDx;
}

void WorldManager::generateInitialWorld(std::vector<std::unique_ptr<Platform>>& platforms) {
    highestPlatformY = GameConfig::BASE_HEIGHT;
    lastSafePlatformY = WorldConfig::START_Y;
    lastSafePlatformX = WorldConfig::START_X;
    
    platforms.push_back(std::make_unique<NormalPlatform>(
        textureManager.getResource("platform_normal"), 
        WorldConfig::START_X, WorldConfig::START_Y 
    ));

    while (highestPlatformY > 0.0f) {
        highestPlatformY -= getRandomGap();
        
        platforms.push_back(std::make_unique<NormalPlatform>(
            textureManager.getResource("platform_normal"), 
            getRandomX(), highestPlatformY 
        ));
        
        lastSafePlatformY = highestPlatformY;
        lastSafePlatformX = platforms.back()->getBounds().left;
    }
}

float WorldManager::update(Player& player, int currentScore,
                           std::vector<std::unique_ptr<Platform>>& platforms, 
                           std::vector<std::unique_ptr<Monster>>& monsters, 
                           std::vector<std::unique_ptr<BlackHole>>& blackHoles,
                           Difficulty diff) {
    float appliedOffset = 0.0f;
    
    if (player.getY() < WorldConfig::SCROLL_THRESHOLD && !player.isSuctionComplete()) {
        appliedOffset = WorldConfig::SCROLL_THRESHOLD - player.getY();
        
        player.setY(WorldConfig::SCROLL_THRESHOLD);
        highestPlatformY += appliedOffset;
        lastSafePlatformY += appliedOffset; 

        for (auto& platform : platforms) platform->setY(platform->getY() + appliedOffset);
        for (auto& monster : monsters) monster->setY(monster->getY() + appliedOffset);
        for (auto& hole : blackHoles) hole->setY(hole->getY() + appliedOffset);
    }

    while (highestPlatformY > 0.0f) {
        float newY = highestPlatformY - getRandomGap();
        float newX = getRandomX();
        int type = getRandomType();

        int attempts = 0;
        bool valid = false;
        
        float platHeight = static_cast<float>(textureManager.getResource("platform_normal")->getSize().y);
        sf::FloatRect proposedBounds(0.0f, newY - (platHeight / 2.0f), static_cast<float>(GameConfig::BASE_WIDTH), platHeight);

        while (attempts < 10 && !valid) {
            newY = highestPlatformY - getRandomGap();
            newX = getRandomX();
            proposedBounds.top = newY - (platHeight / 2.0f);

            if (isReachable(lastSafePlatformX, lastSafePlatformY, newX, newY) && 
                isSpaceClear(proposedBounds, platforms, monsters, blackHoles)) {
                valid = true;
            }
            attempts++;
        }

        if (!valid) {
            newX = lastSafePlatformX;
            newY = lastSafePlatformY - WorldConfig::PLATFORM_Y_MIN_GAP;
            type = 1; 
        }

        std::unique_ptr<Platform> newPlatform;

        if (type <= 6) { 
            newPlatform = std::make_unique<NormalPlatform>(textureManager.getResource("platform_normal"), newX, newY);
            lastSafePlatformY = newY;
            lastSafePlatformX = newX;
        } 
        else if (type <= 8) { 
            newPlatform = std::make_unique<MovingPlatform>(textureManager.getResource("platform_moving"), newX, newY);
            lastSafePlatformY = newY;
            lastSafePlatformX = newX;
        } 
        else { 
            newPlatform = std::make_unique<BreakablePlatform>(textureManager.getResource("platform_broken"), newX, newY);
        }

        if (type <= 8) {
            if (getRandomType() > 8) {
                newPlatform->attachSpring(textureManager.getResource("spring"));
            }
        }

        platforms.push_back(std::move(newPlatform));
        highestPlatformY = newY;

        if (currentScore > WorldConfig::MONSTER_SCORE_THRESHOLD) {
            if (getRandomType() > 9) {
                float mX = getRandomX();
                float mY = highestPlatformY - (getRandomGap() / 2.0f);
                
                bool isBlue = getRandomType() > 5;
                float mHeight = static_cast<float>(isBlue ? textureManager.getResource("monster_blue")->getSize().y : textureManager.getResource("monster_green")->getSize().y);
                
                sf::FloatRect mBounds(0.0f, mY - (mHeight / 2.0f), static_cast<float>(GameConfig::BASE_WIDTH), mHeight);
                
                if (isSpaceClear(mBounds, platforms, monsters, blackHoles)) {
                    if (isBlue) {
                        monsters.push_back(std::make_unique<BlueMonster>(textureManager.getResource("monster_blue"), mX, mY, diff));
                    } else {
                        monsters.push_back(std::make_unique<GreenMonster>(textureManager.getResource("monster_green"), mX, mY, diff));
                    }
                }
            }
        }

        if (currentScore > WorldConfig::HOLE_SCORE_THRESHOLD && diff == Difficulty::Hard) {
            if (getRandomType() > 9) {
                float hX = getRandomX();
                float hY = highestPlatformY - (getRandomGap() / 2.0f);
                
                float hHeight = static_cast<float>(textureManager.getResource("hole_2x")->getSize().y);
                sf::FloatRect hBounds(0.0f, hY - (hHeight / 2.0f), static_cast<float>(GameConfig::BASE_WIDTH), hHeight);

                if (isSpaceClear(hBounds, platforms, monsters, blackHoles)) {
                    blackHoles.push_back(std::make_unique<BlackHole>(
                        textureManager.getResource("hole"),
                        textureManager.getResource("hole_2x"),
                        hX, hY
                    ));
                }
            }
        }
    }

    platforms.erase(std::remove_if(platforms.begin(), platforms.end(),
        [](const std::unique_ptr<Platform>& p) { return p->getY() > WorldConfig::DESPAWN_Y; }), platforms.end());

    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](const std::unique_ptr<Monster>& m) { return m->getY() > WorldConfig::DESPAWN_Y; }), monsters.end());

    blackHoles.erase(std::remove_if(blackHoles.begin(), blackHoles.end(),
        [](const std::unique_ptr<BlackHole>& b) { return b->getY() > WorldConfig::DESPAWN_Y; }), blackHoles.end());
    
    return appliedOffset;
}