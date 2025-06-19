#include "Game.h"

Game::Game() : window(sf::VideoMode(1200, 800), "Brick Breaker Championship"), inMenu(true) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    // Cursor remains visible by default
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                if (inMenu) {
                    window.close();
                }
                else {
                    this->gameManager.returnToMenu(window);
                    inMenu = true;
                }
            }
            if (event.key.code == sf::Keyboard::R && this->gameManager.isGameOver() && !inMenu) {
                this->gameManager.restart(window);
            }
            break;
        default:
            break;
        }
    }
}

void Game::update() {
    float deltaTime = this->clock.restart().asSeconds();
    deltaTime = std::min(deltaTime, 1.0f / 30.0f);

    if (inMenu) {
        this->menu.update(this->window);
        if (this->menu.isExitSelected()) {
            this->window.close();
        }
        else if (this->menu.getSelectedMode() != this->gameManager.getGameMode()) {
            this->gameManager.setGameMode(this->menu.getSelectedMode(),window);
        }
        else if (this->menu.getSelectedTheme() != this->gameManager.getTheme()) {
            this->gameManager.setTheme(this->menu.getSelectedTheme());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->menu.getSelectedOption() == 0) {
            inMenu = false;
            this->gameManager.startGame(window);
        }
    }
    else {
        this->gameManager.update(deltaTime, this->window);
    }
}

void Game::render() {
    this->window.clear(sf::Color::Black);
    if (inMenu) {
        this->menu.draw(this->window);
    }
    else {
        this->gameManager.draw(this->window);
    }
    this->window.display();
}