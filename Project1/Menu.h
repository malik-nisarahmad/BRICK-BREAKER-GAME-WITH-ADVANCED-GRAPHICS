#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum GameMode { CLASSIC, ARCADE, CHALLENGE };
enum Theme { CLASSIC_THEME, NEON_THEME, SPACE_THEME };

class Menu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    std::vector<sf::Text> modeOptions;
    std::vector<sf::Text> themeOptions;
    sf::RectangleShape background;
    int selectedOption;
    bool showModeSubmenu;
    bool showThemeSubmenu;
    GameMode selectedMode;
    Theme selectedTheme;

public:
    Menu();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isExitSelected() const;
    std::string getSelectedMode() const;
    std::string getSelectedTheme() const;
    int getSelectedOption() const;
};