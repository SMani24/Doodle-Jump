/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <vector>
#include <string>

namespace SoundConfig {
    constexpr int POOL_SIZE = 10;
}

class SoundManager {
private:
    sf::Music backgroundMusic;
    std::vector<sf::Sound> soundPool;
    int currentSoundIndex;
    float masterVolume;

public:
    SoundManager();
    ~SoundManager() = default;

    void playMusic(const std::string& filepath);
    void pauseMusic();
    void resumeMusic();
    
    void playSound(const sf::SoundBuffer& buffer);
    
    void setVolume(int volume);
};

#endif // SOUND_MANAGER_HPP