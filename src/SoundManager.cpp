/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "SoundManager.hpp"
#include <iostream>
#include <algorithm>

SoundManager::SoundManager() : currentSoundIndex(0), masterVolume(50.0f) {
    soundPool.resize(SoundConfig::POOL_SIZE);
}

void SoundManager::playMusic(const std::string& filepath) {
    if (backgroundMusic.openFromFile(filepath)) {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(masterVolume);
        backgroundMusic.play();
    } else {
        std::cerr << "Error: Could not load music file " << filepath << std::endl;
    }
}

void SoundManager::pauseMusic() {
    if (backgroundMusic.getStatus() == sf::SoundSource::Playing) {
        backgroundMusic.pause();
    }
}

void SoundManager::resumeMusic() {
    if (backgroundMusic.getStatus() == sf::SoundSource::Paused || backgroundMusic.getStatus() == sf::SoundSource::Stopped) {
        backgroundMusic.play();
    }
}

void SoundManager::playSound(const sf::SoundBuffer& buffer) {
    soundPool[currentSoundIndex].setBuffer(buffer);
    soundPool[currentSoundIndex].setVolume(masterVolume);
    soundPool[currentSoundIndex].play();
    
    currentSoundIndex = (currentSoundIndex + 1) % SoundConfig::POOL_SIZE;
}

void SoundManager::setVolume(int volume) {
    masterVolume = static_cast<float>(std::clamp(volume, 0, 100));
    backgroundMusic.setVolume(masterVolume);
    
    for (auto& sound : soundPool) {
        sound.setVolume(masterVolume);
    }
}