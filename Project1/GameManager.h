#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "PowerUp.h"
#include "Particle.h"
#include "SwrilCursor.h"

class GameManager {
private:
    int score;
    int lives;
    int level;
    bool gameOver;
    bool gameWon;
    bool paused;
    bool ballLaunched;
    float powerUpTimer;
    float scoreMultiplier;
    float multiplierTimer;
    std::string gameMode;
    std::string theme;
    int targetScore;
    bool inGame;
    sf::Font font;
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<std::vector<Brick>> bricks;
    std::vector<PowerUp> powerUps;
    std::vector<Particle> particles;
    SwirlCursor swirlCursor;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text levelText;
    sf::Text gameOverText;

    void setupUI();
    void initializeLevel(sf::RenderWindow& window);

    void handleCollisions(sf::RenderWindow& window);
    void activatePowerUp(PowerUp::PowerUpType type, sf::RenderWindow& window);
    void createParticles(sf::Vector2f position, sf::Color color, int count, sf::RenderWindow& window);
    void checkWinLoseConditions(sf::RenderWindow& window);
    void handleInput();

public:
    GameManager();
    void update(float deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void restart(sf::RenderWindow& window);
    bool isGameOver() const;
    bool isPaused() const;
    int getScore() const;
    int getLevel() const;
    std::string getGameMode() const;
    std::string getTheme() const;
    void setGameMode(const std::string& mode, sf::RenderWindow& window);
    void setTheme(const std::string& theme);
    bool isInGame() const;
    void startGame(sf::RenderWindow& window);
    void returnToMenu(sf::RenderWindow& window);
};