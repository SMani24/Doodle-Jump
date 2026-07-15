/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#include "SettingsMenu.hpp"

SettingsMenu::SettingsMenu(std::shared_ptr<sf::Font> textFont, SettingsManager& settingsRef, 
                           std::shared_ptr<sf::Texture> easyTex, std::shared_ptr<sf::Texture> medTex, 
                           std::shared_ptr<sf::Texture> hardTex, std::shared_ptr<sf::Texture> backTex)
    : font(textFont), settings(settingsRef)
{
    auto setupText = [&](sf::Text& text, const std::string& str, float y, int size) {
        text.setFont(*font);
        text.setString(str);
        text.setCharacterSize(size);
        text.setFillColor(SettingsMenuConfig::TEXT_COLOR);
        text.setStyle(sf::Text::Bold);
        centerText(text, y);
    };

    setupText(titleText, "SETTINGS", SettingsMenuConfig::TITLE_Y, 36);
    setupText(volumeText, "VOLUME", SettingsMenuConfig::VOLUME_TEXT_Y, 24);
    setupText(diffText, "DIFFICULTY", SettingsMenuConfig::DIFF_TEXT_Y, 24);

    sliderTrack.setSize(sf::Vector2f(SettingsMenuConfig::SLIDER_WIDTH, SettingsMenuConfig::SLIDER_HEIGHT));
    sliderTrack.setOrigin(SettingsMenuConfig::SLIDER_WIDTH / 2.0f, SettingsMenuConfig::SLIDER_HEIGHT / 2.0f);
    sliderTrack.setPosition(GameConfig::BASE_WIDTH / 2.0f, SettingsMenuConfig::SLIDER_Y);
    sliderTrack.setFillColor(SettingsMenuConfig::TRACK_COLOR);

    sliderFill.setSize(sf::Vector2f(0, SettingsMenuConfig::SLIDER_HEIGHT));
    sliderFill.setOrigin(0, SettingsMenuConfig::SLIDER_HEIGHT / 2.0f);
    sliderFill.setPosition((GameConfig::BASE_WIDTH - SettingsMenuConfig::SLIDER_WIDTH) / 2.0f, SettingsMenuConfig::SLIDER_Y);
    sliderFill.setFillColor(SettingsMenuConfig::FILL_COLOR);

    easyButton = std::make_unique<Button>(easyTex, SettingsMenuConfig::EASY_X, SettingsMenuConfig::DIFF_BTN_Y);
    easyButton->setSize(SettingsMenuConfig::DIFF_BTN_WIDTH, SettingsMenuConfig::DIFF_BTN_HEIGHT);

    mediumButton = std::make_unique<Button>(medTex, SettingsMenuConfig::MEDIUM_X, SettingsMenuConfig::DIFF_BTN_Y);
    mediumButton->setSize(SettingsMenuConfig::DIFF_BTN_WIDTH, SettingsMenuConfig::DIFF_BTN_HEIGHT);

    hardButton = std::make_unique<Button>(hardTex, SettingsMenuConfig::HARD_X, SettingsMenuConfig::DIFF_BTN_Y);
    hardButton->setSize(SettingsMenuConfig::DIFF_BTN_WIDTH, SettingsMenuConfig::DIFF_BTN_HEIGHT);

    backButton = std::make_unique<Button>(backTex, GameConfig::BASE_WIDTH / 2.0f, SettingsMenuConfig::BACK_Y);
    backButton->setSize(SettingsMenuConfig::BACK_BTN_WIDTH, SettingsMenuConfig::BACK_BTN_HEIGHT);

    updateSliderVisuals();
}

void SettingsMenu::centerText(sf::Text& text, float yPos) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(GameConfig::BASE_WIDTH / 2.0f, yPos);
}

void SettingsMenu::updateSliderVisuals() {
    float fillWidth = SettingsMenuConfig::SLIDER_WIDTH * (settings.getVolume() / 100.0f);
    sliderFill.setSize(sf::Vector2f(fillWidth, SettingsMenuConfig::SLIDER_HEIGHT));
}

void SettingsMenu::update(const sf::RenderWindow& window, const sf::View& view) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
        sf::FloatRect trackBounds = sliderTrack.getGlobalBounds();
        
        trackBounds.top -= 10.0f;
        trackBounds.height += 20.0f;

        if (trackBounds.contains(mousePos)) {
            float percent = (mousePos.x - trackBounds.left) / SettingsMenuConfig::SLIDER_WIDTH;
            settings.setVolume(static_cast<int>(percent * 100.0f));
            updateSliderVisuals();
        }
    }

    Difficulty currentDiff = settings.getDifficulty();
    
    easyButton->setDimmed(currentDiff != Difficulty::Easy);
    mediumButton->setDimmed(currentDiff != Difficulty::Medium);
    hardButton->setDimmed(currentDiff != Difficulty::Hard);

    easyButton->update(window, view); 
    mediumButton->update(window, view);
    hardButton->update(window, view);
    backButton->update(window, view);
}

void SettingsMenu::processClick(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) {
    if (easyButton->isClicked(window, view, event)) {
        settings.setDifficulty(Difficulty::Easy);
    } else if (mediumButton->isClicked(window, view, event)) {
        settings.setDifficulty(Difficulty::Medium);
    } else if (hardButton->isClicked(window, view, event)) {
        settings.setDifficulty(Difficulty::Hard);
    }
}

bool SettingsMenu::isBackClicked(const sf::RenderWindow& window, const sf::View& view, const sf::Event& event) const {
    return backButton->isClicked(window, view, event);
}

void SettingsMenu::draw(sf::RenderWindow& window) const {
    window.draw(titleText);
    window.draw(volumeText);
    window.draw(sliderTrack);
    window.draw(sliderFill);
    window.draw(diffText);
    
    easyButton->draw(window);
    mediumButton->draw(window);
    hardButton->draw(window);
    backButton->draw(window);
}