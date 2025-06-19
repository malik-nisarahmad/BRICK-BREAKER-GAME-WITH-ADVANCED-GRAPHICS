/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "Game.h"
#include "HighScoreManager.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        return -1;
    }
    return 0;
}