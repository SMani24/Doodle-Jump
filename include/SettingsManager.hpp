/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef SETTINGS_MANAGER_HPP
#define SETTINGS_MANAGER_HPP

#include <string>

enum class Difficulty {
    Easy = 0,
    Medium = 1,
    Hard = 2
};

namespace SettingsConfig {
    const std::string SAVE_FILE = "settings.txt";
    constexpr int DEFAULT_VOLUME = 50;
    constexpr Difficulty DEFAULT_DIFFICULTY = Difficulty::Medium;
}

class SettingsManager {
private:
    int volume;
    Difficulty difficulty;

public:
    SettingsManager();
    ~SettingsManager() = default;

    void loadSettings();
    void saveSettings() const;

    int getVolume() const;
    void setVolume(int v);

    Difficulty getDifficulty() const;
    void setDifficulty(Difficulty d);
};

#endif // SETTINGS_MANAGER_HPP