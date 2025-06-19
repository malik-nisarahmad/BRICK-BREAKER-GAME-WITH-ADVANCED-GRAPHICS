/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */
#include "GameManager.h"
#include <algorithm>
#include <cmath>

GameManager::GameManager() : score(0), lives(3), level(1), gameOver(false), gameWon(false),
paused(false), ballLaunched(false), powerUpTimer(0), scoreMultiplier(1.0f), multiplierTimer(0),
gameMode("Arcade"), theme("Space"), targetScore(0), inGame(false) {
    if (!this->font.loadFromFile("arial.ttf")) {
        // Font loading failed, will use default
    }
    this->setupUI();
    this->swirlCursor.setTheme(this->theme);
}

void GameManager::setupUI() {
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(24);
    this->scoreText.setFillColor(sf::Color::White);
    this->livesText.setFont(this->font);
    this->livesText.setCharacterSize(24);
    this->livesText.setFillColor(sf::Color::White);
    this->levelText.setFont(this->font);
    this->levelText.setCharacterSize(24);
    this->levelText.setFillColor(sf::Color::White);
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(48);
    this->gameOverText.setFillColor(sf::Color::Red);
}

void GameManager::initializeLevel(sf::RenderWindow& window) {
    this->bricks.clear();
    this->powerUps.clear();
    this->particles.clear();
    int rows, cols;
    if (this->gameMode == "Challenge") {
        rows = 8;
        cols = 12;
        this->targetScore = 2000 * this->level;
        this->lives = 3;
    }
    else {
        rows = 5 + this->level;
        cols = 10 + this->level;
        rows = std::min(rows, 12);
        cols = std::min(cols, 15);
        this->targetScore = 0;
    }
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / 1200.0f;
    float scaleY = static_cast<float>(windowSize.y) / 800.0f;
    float brickWidth = 80 * scaleX;
    float brickHeight = 30 * scaleY;
    float startX = (windowSize.x - cols * brickWidth) / 2;
    float startY = 100 * scaleY;
    for (int row = 0; row < rows; ++row) {
        std::vector<Brick> brickRow;
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * brickWidth;
            float y = startY + row * brickHeight;
            Brick::BrickType type = Brick::STANDARD;
            if (this->gameMode != "Classic") {
                int random = rand() % 100;
                if (random < 60) type = Brick::STANDARD;
                else if (random < 85) type = Brick::STRONG;
                else if (random < 95 && this->gameMode == "Arcade") type = Brick::POWERUP;
                else type = Brick::UNBREAKABLE;
            }
            brickRow.push_back(Brick(x, y, type));
        }
        this->bricks.push_back(brickRow);
    }
    this->ballLaunched = false;
    this->balls.clear();
    this->balls.push_back(Ball());
    this->balls[0].setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 100 * scaleY));
    this->balls[0].setActive(true); // Start with ball active
    this->paddle.setSize(sf::Vector2f(120 * scaleX, 20 * scaleY));
    this->paddle.setPosition(sf::Vector2f(windowSize.x / 2 - 60 * scaleX, windowSize.y - 50 * scaleY));
}


void GameManager::update(float deltaTime, sf::RenderWindow& window) {
    if (!this->inGame || (this->gameOver && !this->paused)) return;

    this->powerUpTimer += deltaTime;
    if (this->multiplierTimer > 0) {
        this->multiplierTimer -= deltaTime;
        if (this->multiplierTimer <= 0) this->scoreMultiplier = 1.0f;
    }
    this->paddle.update(deltaTime);
    for (auto& ball : this->balls) ball.update(deltaTime);
    for (auto& row : this->bricks) {
        for (auto& brick : row) {
            brick.update(deltaTime);
        }
    }
    if (this->gameMode == "Arcade") {
        for (auto& powerUp : this->powerUps) powerUp.update(deltaTime);
    }
    this->particles.erase(std::remove_if(this->particles.begin(), this->particles.end(),
        [deltaTime](Particle& p) { return !p.update(deltaTime); }), this->particles.end());

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    this->swirlCursor.update(deltaTime, mousePos, window);

    this->handleCollisions(window);
    this->handleInput();
    this->checkWinLoseConditions(window);
    if (this->gameMode == "Arcade") {
        this->powerUps.erase(std::remove_if(this->powerUps.begin(), this->powerUps.end(),
            [](const PowerUp& p) { return !p.getIsActive(); }), this->powerUps.end());
    }

    // Auto-launch ball on first update if not launched
    if (!this->ballLaunched && !this->balls.empty() && deltaTime > 0) {
        this->balls[0].launch(3.14159265f / 4); // Launch at 45 degrees
        this->ballLaunched = true;
    }
}

void GameManager::handleInput() {
    static bool spacePressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed) {
        spacePressed = true;
        if (!this->ballLaunched && !this->balls.empty()) {
            float angle = 3.14159265f / 4;
            this->balls[0].launch(angle);
            this->ballLaunched = true;
        }
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        spacePressed = false;
    }
    static bool pPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !pPressed) {
        pPressed = true;
        this->paused = !this->paused;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        pPressed = false;
    }
}

void GameManager::handleCollisions(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    for (auto& ball : this->balls) {
        if (!ball.getIsActive()) continue;
        if (ball.getBounds().intersects(this->paddle.getBounds()) && ball.getVelocity().y > 0) {
            float bounceAngle = this->paddle.getBounceAngle(ball.getPosition().x);
            float speed = std::sqrt(ball.getVelocity().x * ball.getVelocity().x + ball.getVelocity().y * ball.getVelocity().y);
            ball.setVelocity(sf::Vector2f(std::sin(bounceAngle) * speed, -std::cos(bounceAngle) * speed));
            this->createParticles(ball.getPosition(), sf::Color::White, 5,window);
        }
        for (auto& row : this->bricks) {
            for (auto& brick : row) {
                if (brick.checkCollision(ball)) {
                    if (brick.takeDamage()) {
                        this->score += static_cast<int>(brick.getPointValue() * this->scoreMultiplier);
                        this->createParticles(ball.getPosition(), sf::Color::Yellow, 15,window);
                        if (brick.getBrickType() == Brick::POWERUP && this->gameMode == "Arcade") {
                            int powerType = rand() % 5;
                            this->powerUps.push_back(PowerUp(
                                sf::Vector2f(brick.getBounds().left + brick.getBounds().width / 2,
                                    brick.getBounds().top + brick.getBounds().height),
                                static_cast<PowerUp::PowerUpType>(powerType)
                            ));
                        }
                    }
                    sf::Vector2f ballPos = ball.getPosition();
                    sf::FloatRect brickBounds = brick.getBounds();
                    float overlapLeft = (ballPos.x + ball.getRadius()) - brickBounds.left;
                    float overlapRight = (brickBounds.left + brickBounds.width) - (ballPos.x - ball.getRadius());
                    float overlapTop = (ballPos.y + ball.getRadius()) - brickBounds.top;
                    float overlapBottom = (brickBounds.top + brickBounds.height) - (ballPos.y - ball.getRadius());
                    bool ballFromLeft = (overlapLeft < overlapRight);
                    bool ballFromTop = (overlapTop < overlapBottom);
                    float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
                    float minOverlapY = ballFromTop ? overlapTop : overlapBottom;
                    if (minOverlapX < minOverlapY) {
                        ball.setVelocity(sf::Vector2f(-ball.getVelocity().x, ball.getVelocity().y));
                    }
                    else {
                        ball.setVelocity(sf::Vector2f(ball.getVelocity().x, -ball.getVelocity().y));
                    }
                    break;
                }
            }
        }
        if (this->gameMode == "Arcade") {
            for (auto& powerUp : this->powerUps) {
                if (powerUp.getBounds().intersects(this->paddle.getBounds())) {
                    this->activatePowerUp(powerUp.getType(),window);
                    powerUp.setInactive();
                    this->createParticles(powerUp.getBounds().getPosition(), sf::Color::Green, 10,window);
                }
            }
        }
        // Only deactivate ball if launched and below screen
        if (this->ballLaunched && ball.getPosition().y > windowSize.y) ball.setActive(false);
    }
}

void GameManager::activatePowerUp(PowerUp::PowerUpType type, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / 1200.0f;
    switch (type) {
    case PowerUp::PADDLE_EXTEND:
        this->paddle.setSize(sf::Vector2f(180 * scaleX, 20 * scaleX));
        break;
    case PowerUp::MULTI_BALL:
        if (this->balls.size() < 5) {
            Ball newBall = this->balls[0];
            newBall.setVelocity(sf::Vector2f(-this->balls[0].getVelocity().x, this->balls[0].getVelocity().y));
            this->balls.push_back(newBall);
        }
        break;
    case PowerUp::FIRE_BALL:
        for (auto& ball : this->balls) ball.setColor(sf::Color::Red);
        break;
    case PowerUp::EXTRA_LIFE:
        this->lives++;
        break;
    case PowerUp::SCORE_MULTIPLIER:
        this->scoreMultiplier = 2.0f;
        this->multiplierTimer = 10.0f;
        break;
    }
}

void GameManager::createParticles(sf::Vector2f position, sf::Color color, int count, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    for (int i = 0; i < count; ++i) {
        float angle = (rand() % 360) * 3.14159265f / 180.0f;
        float speed = 50 + rand() % 100;
        sf::Vector2f velocity(std::cos(angle) * speed, std::sin(angle) * speed);
        this->particles.push_back(Particle(position, velocity, color, 1.0f + (rand() % 100) / 100.0f, 2 + rand() % 4));
    }
}

void GameManager::checkWinLoseConditions(sf::RenderWindow& window) {
    this->balls.erase(std::remove_if(this->balls.begin(), this->balls.end(),
        [this](const Ball& ball) {
            if (!ball.getIsActive() && this->ballLaunched) {
                this->lives--;
                return true;
            }
            return false;
        }), this->balls.end());
    if (this->balls.empty() && this->lives > 0) {
        this->balls.push_back(Ball());
        this->ballLaunched = false;
        sf::Vector2u windowSize = window.getSize();
        float scaleY = static_cast<float>(windowSize.y) / 800.0f;
        this->balls[0].setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 100 * scaleY));
        this->balls[0].setActive(true); // New ball starts active
        this->paddle.setSize(sf::Vector2f(120 * scaleY, 20 * scaleY));
    }
    if (this->lives <= 0) {
        this->gameOver = true;
        this->gameOverText.setString("GAME OVER\nPress R to Restart or ESC to Menu");
    }
    bool allBricksDestroyed = true;
    for (const auto& row : this->bricks) {
        for (const auto& brick : row) {
            if (!brick.getIsDestroyed() && brick.getBrickType() != Brick::UNBREAKABLE) {
                allBricksDestroyed = false;
                break;
            }
        }
        if (!allBricksDestroyed) break;
    }
    if (allBricksDestroyed || (this->gameMode == "Challenge" && this->score >= this->targetScore)) {
        this->level++;
        this->initializeLevel(window);
        this->balls.clear();
        this->balls.push_back(Ball());
    }
}

void GameManager::draw(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::RectangleShape background(sf::Vector2f(windowSize.x, windowSize.y));
    if (this->theme == "Classic") {
        background.setFillColor(sf::Color(50, 100, 150));
    }
    else if (this->theme == "Neon") {
        background.setFillColor(sf::Color(10, 10, 50));
    }
    else { // Space
        background.setFillColor(sf::Color(10, 10, 30));
    }
    window.draw(background);

    if (this->theme == "Space") {
        for (int i = 0; i < 100; ++i) {
            sf::CircleShape star(1);
            star.setPosition(rand() % static_cast<int>(windowSize.x), rand() % static_cast<int>(windowSize.y));
            star.setFillColor(sf::Color(255, 255, 255, 100));
            window.draw(star);
        }
    }
    else if (this->theme == "Neon") {
        for (int i = 0; i < 50; ++i) {
            sf::CircleShape glow(3);
            glow.setPosition(rand() % static_cast<int>(windowSize.x), rand() % static_cast<int>(windowSize.y));
            glow.setFillColor(sf::Color(0, 255, 255, 50));
            window.draw(glow);
        }
    }

    for (auto& particle : this->particles) particle.draw(window);
    this->paddle.draw(window);
    for (auto& ball : this->balls) ball.draw(window);
    for (const auto& row : this->bricks) for (const auto& brick : row) brick.draw(window);
    if (this->gameMode == "Arcade") {
        for (auto& powerUp : this->powerUps) powerUp.draw(window);
    }
    this->scoreText.setString("Score: " + std::to_string(this->score));
    this->livesText.setString("Lives: " + std::to_string(this->lives));
    this->levelText.setString("Level: " + std::to_string(this->level));
    this->scoreText.setPosition(10, 10);
    this->livesText.setPosition(10, 40);
    this->levelText.setPosition(10, 70);
    window.draw(this->scoreText);
    window.draw(this->livesText);
    window.draw(this->levelText);
    if (this->multiplierTimer > 0 && this->gameMode == "Arcade") {
        sf::Text multiplierText;
        multiplierText.setFont(this->font);
        multiplierText.setCharacterSize(20);
        multiplierText.setFillColor(sf::Color::Yellow);
        multiplierText.setPosition(windowSize.x - 200, 10);
        multiplierText.setString("2x MULTIPLIER: " + std::to_string(static_cast<int>(this->multiplierTimer)));
        window.draw(multiplierText);
    }
    if (!this->ballLaunched && !this->balls.empty()) {
        sf::Text instructionText;
        instructionText.setFont(this->font);
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(sf::Color::White);
        instructionText.setPosition(windowSize.x / 2 - 150, windowSize.y / 2);
        instructionText.setString("Press SPACE to launch ball\nUse A/D or Arrow Keys to move");
        window.draw(instructionText);
    }
    if (this->paused) {
        sf::RectangleShape pauseOverlay(sf::Vector2f(windowSize.x, windowSize.y));
        pauseOverlay.setFillColor(sf::Color(0, 0, 0, 128));
        window.draw(pauseOverlay);
        sf::Text pauseText;
        pauseText.setFont(this->font);
        pauseText.setCharacterSize(48);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setPosition(windowSize.x / 2 - 100, windowSize.y / 2);
        pauseText.setString("PAUSED\nPress P to continue or ESC to Menu");
        window.draw(pauseText);
    }
    if (this->gameOver) {
        sf::RectangleShape gameOverOverlay(sf::Vector2f(windowSize.x, windowSize.y));
        gameOverOverlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(gameOverOverlay);
        window.draw(this->gameOverText);
    }
    this->swirlCursor.draw(window);
}

void GameManager::restart(sf::RenderWindow& window) {
    this->score = 0;
    this->lives = 3;
    this->level = 1;
    this->gameOver = false;
    this->gameWon = false;
    this->paused = false;
    this->ballLaunched = false;
    this->scoreMultiplier = 1.0f;
    this->multiplierTimer = 0;
    this->balls.clear();
    this->balls.push_back(Ball());
    this->initializeLevel(window);
}

bool GameManager::isGameOver() const { return this->gameOver; }
bool GameManager::isPaused() const { return this->paused; }
int GameManager::getScore() const { return this->score; }
int GameManager::getLevel() const { return this->level; }
std::string GameManager::getGameMode() const { return this->gameMode; }
std::string GameManager::getTheme() const { return this->theme; }
void GameManager::setGameMode(const std::string& mode, sf::RenderWindow& window) {
    this->gameMode = mode;
    this->restart(window);
}
void GameManager::setTheme(const std::string& theme) {
    this->theme = theme;
    this->swirlCursor.setTheme(this->theme);
}
bool GameManager::isInGame() const { return this->inGame; }
void GameManager::startGame(sf::RenderWindow& window) {
    this->inGame = true;
    this->restart(window);
}
void GameManager::returnToMenu(sf::RenderWindow& window) {
    this->inGame = false;
    this->restart(window);
}