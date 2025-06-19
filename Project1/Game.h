#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Menu.h"

class Game {
private:
    sf::RenderWindow window;
    GameManager gameManager;
    Menu menu;
    bool inMenu;
    sf::Clock clock;

public:
    Game();
    void run();
    void handleEvents();
    void update();
    void render();
};