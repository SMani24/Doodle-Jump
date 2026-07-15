/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "SettingsManager.hpp"
#include <fstream>
#include <algorithm>

SettingsManager::SettingsManager() 
    : volume(SettingsConfig::DEFAULT_VOLUME), difficulty(SettingsConfig::DEFAULT_DIFFICULTY) 
{
    loadSettings();
}

void SettingsManager::loadSettings() {
    std::ifstream file(SettingsConfig::SAVE_FILE);
    if (file.is_open()) {
        int diffInt;
        file >> volume >> diffInt;
        
        volume = std::clamp(volume, 0, 100);
        
        if (diffInt >= 0 && diffInt <= 2) {
            difficulty = static_cast<Difficulty>(diffInt);
        }
        file.close();
    }
}

void SettingsManager::saveSettings() const {
    std::ofstream file(SettingsConfig::SAVE_FILE);
    if (file.is_open()) {
        file << volume << " " << static_cast<int>(difficulty);
        file.close();
    }
}

int SettingsManager::getVolume() const { return volume; }

void SettingsManager::setVolume(int v) { 
    volume = std::clamp(v, 0, 100); 
}

Difficulty SettingsManager::getDifficulty() const { return difficulty; }

void SettingsManager::setDifficulty(Difficulty d) { difficulty = d; }