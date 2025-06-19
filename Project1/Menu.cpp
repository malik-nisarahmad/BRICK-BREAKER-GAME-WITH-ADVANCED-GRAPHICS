#include "Menu.h"
#include "SwrilCursor.h"
#include <iostream>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

Menu::Menu() : selectedOption(0), showModeSubmenu(false), showThemeSubmenu(false),
selectedMode(ARCADE), selectedTheme(SPACE_THEME) {
    if (!font.loadFromFile("arial.ttf")) {
        // Font loading failed, use default
    }

    // Initialize title
    title.setFont(font);
    title.setString("Brick Breaker Championship");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, 100);

    // Initialize main menu options
    std::vector<std::string> optionLabels = { "Start Game", "Select Mode", "Select Theme", "Exit" };
    for (size_t i = 0; i < optionLabels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(optionLabels[i]);
        text.setCharacterSize(32);
        text.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, 300 + i * 60);
        options.push_back(text);
    }

    // Initialize mode submenu
    std::vector<std::string> modeLabels = { "Classic", "Arcade", "Challenge" };
    for (size_t i = 0; i < modeLabels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(modeLabels[i]);
        text.setCharacterSize(28);
        text.setFillColor(i == selectedMode ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, 300 + i * 50);
        modeOptions.push_back(text);
    }

    // Initialize theme submenu
    std::vector<std::string> themeLabels = { "Classic", "Neon", "Space" };
    for (size_t i = 0; i < themeLabels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(themeLabels[i]);
        text.setCharacterSize(28);
        text.setFillColor(i == selectedTheme ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, 300 + i * 50);
        themeOptions.push_back(text);
    }

    // Initialize background
    background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(sf::Color(10, 10, 30));
}

void Menu::update(sf::RenderWindow& window) {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

    if (showModeSubmenu) {
        // Handle mode submenu navigation
        for (size_t i = 0; i < modeOptions.size(); ++i) {
            if (modeOptions[i].getGlobalBounds().contains(mousePos)) {
                modeOptions[selectedMode].setFillColor(sf::Color::White);
                selectedMode = static_cast<GameMode>(i);
                modeOptions[i].setFillColor(sf::Color::Yellow);
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            showModeSubmenu = false;
        }
    }
    else if (showThemeSubmenu) {
        // Handle theme submenu navigation
        for (size_t i = 0; i < themeOptions.size(); ++i) {
            if (themeOptions[i].getGlobalBounds().contains(mousePos)) {
                themeOptions[selectedTheme].setFillColor(sf::Color::White);
                selectedTheme = static_cast<Theme>(i);
                themeOptions[i].setFillColor(sf::Color::Yellow);
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            showThemeSubmenu = false;
        }
    }
    else {
        // Handle main menu navigation
        for (size_t i = 0; i < options.size(); ++i) {
            if (options[i].getGlobalBounds().contains(mousePos)) {
                options[selectedOption].setFillColor(sf::Color::White);
                selectedOption = i;
                options[i].setFillColor(sf::Color::Yellow);
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            switch (selectedOption) {
            case 0: // START_GAME
                // Game starts, handled by Game class
                break;
            case 1: // SELECT_MODE
                showModeSubmenu = true;
                break;
            case 2: // SELECT_THEME
                showThemeSubmenu = true;
                break;
            case 3: // EXIT
                // Exit handled by Game class
                break;
            }
        }
    }

    // Keyboard navigation
    static bool upPressed = false, downPressed = false, enterPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed) {
        upPressed = true;
        if (showModeSubmenu) {
            modeOptions[selectedMode].setFillColor(sf::Color::White);
            selectedMode = static_cast<GameMode>(selectedMode == 0 ? modeOptions.size() - 1 : selectedMode - 1);
            modeOptions[selectedMode].setFillColor(sf::Color::Yellow);
        }
        else if (showThemeSubmenu) {
            themeOptions[selectedTheme].setFillColor(sf::Color::White);
            selectedTheme = static_cast<Theme>(selectedTheme == 0 ? themeOptions.size() - 1 : selectedTheme - 1);
            themeOptions[selectedTheme].setFillColor(sf::Color::Yellow);
        }
        else {
            options[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption == 0 ? options.size() - 1 : selectedOption - 1);
            options[selectedOption].setFillColor(sf::Color::Yellow);
        }
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        upPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed) {
        downPressed = true;
        if (showModeSubmenu) {
            modeOptions[selectedMode].setFillColor(sf::Color::White);
            selectedMode = static_cast<GameMode>((selectedMode + 1) % modeOptions.size());
            modeOptions[selectedMode].setFillColor(sf::Color::Yellow);
        }
        else if (showThemeSubmenu) {
            themeOptions[selectedTheme].setFillColor(sf::Color::White);
            selectedTheme = static_cast<Theme>((selectedTheme + 1) % themeOptions.size());
            themeOptions[selectedTheme].setFillColor(sf::Color::Yellow);
        }
        else {
            options[selectedOption].setFillColor(sf::Color::White);
            selectedOption = (selectedOption + 1) % options.size();
            options[selectedOption].setFillColor(sf::Color::Yellow);
        }
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        downPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enterPressed) {
        enterPressed = true;
        if (showModeSubmenu) {
            showModeSubmenu = false;
        }
        else if (showThemeSubmenu) {
            showThemeSubmenu = false;
        }
        else {
            switch (selectedOption) {
            case 0: // START_GAME
                // Game starts, handled by Game class
                break;
            case 1: // SELECT_MODE
                showModeSubmenu = true;
                break;
            case 2: // SELECT_THEME
                showThemeSubmenu = true;
                break;
            case 3: // EXIT
                // Exit handled by Game class
                break;
            }
        }
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        enterPressed = false;
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(title);
    if (showModeSubmenu) {
        for (const auto& option : modeOptions) {
            window.draw(option);
        }
    }
    else if (showThemeSubmenu) {
        for (const auto& option : themeOptions) {
            window.draw(option);
        }
    }
    else {
        for (const auto& option : options) {
            window.draw(option);
        }
    }

    // Update and draw swirl cursor
    static SwirlCursor swirlCursor;
    swirlCursor.update(1.0f / 60.0f, window.mapPixelToCoords(sf::Mouse::getPosition(window)), window);
    swirlCursor.draw(window);
}

bool Menu::isExitSelected() const {
    return selectedOption == 3 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

std::string Menu::getSelectedMode() const {
    switch (selectedMode) {
    case CLASSIC: return "Classic";
    case ARCADE: return "Arcade";
    case CHALLENGE: return "Challenge";
    default: return "Arcade";
    }
}

std::string Menu::getSelectedTheme() const {
    switch (selectedTheme) {
    case CLASSIC_THEME: return "Classic";
    case NEON_THEME: return "Neon";
    case SPACE_THEME: return "Space";
    default: return "Space";
    }
}

int Menu::getSelectedOption() const {
    return selectedOption;
}