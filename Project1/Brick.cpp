
/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */

#include "Brick.h"
#include <cmath>

Brick::Brick(float x, float y, BrickType type)
    : position(x, y), size(80, 30), brickType(type), isDestroyed(false), animationTime(0) {
    switch (type) {
    case STANDARD:
        strength = maxStrength = 1;
        pointValue = 50;
        baseColor = sf::Color(100 + rand() % 100, 150 + rand() % 100, 200 + rand() % 55);
        break;
    case STRONG:
        strength = maxStrength = 3;
        pointValue = 150;
        baseColor = sf::Color(200, 100, 100);
        break;
    case UNBREAKABLE:
        strength = maxStrength = -1;
        pointValue = 0;
        baseColor = sf::Color(80, 80, 80);
        break;
    case POWERUP:
        strength = maxStrength = 1;
        pointValue = 100;
        baseColor = sf::Color::Yellow;
        break;
    }
}

bool Brick::takeDamage() {
    if (brickType == UNBREAKABLE) return false;
    strength--;
    animationTime = 0.5f;
    if (strength <= 0) {
        isDestroyed = true;
        return true;
    }
    return false;
}

void Brick::update(float deltaTime) {
    if (animationTime > 0) {
        animationTime -= deltaTime;
    }
}

void Brick::draw(sf::RenderWindow& window) const {
    if (isDestroyed) return;
    sf::RectangleShape brick(size);
    brick.setPosition(position);
    sf::Color currentColor = baseColor;
    if (brickType == STRONG) {
        float strengthRatio = float(strength) / maxStrength;
        currentColor.r = static_cast<sf::Uint8>(200 * strengthRatio + 55);
        currentColor.g = static_cast<sf::Uint8>(100 * strengthRatio + 50);
        currentColor.b = static_cast<sf::Uint8>(100 * strengthRatio + 50);
    }
    if (animationTime > 0) {
        float flash = std::sin(animationTime * 20) * 0.5f + 0.5f;
        currentColor.r = static_cast<sf::Uint8>(std::min(255.0f, currentColor.r + flash * 100));
        currentColor.g = static_cast<sf::Uint8>(std::min(255.0f, currentColor.g + flash * 100));
        currentColor.b = static_cast<sf::Uint8>(std::min(255.0f, currentColor.b + flash * 100));
    }
    brick.setFillColor(currentColor);
    sf::RectangleShape topHighlight(sf::Vector2f(size.x, 5));
    topHighlight.setPosition(position);
    sf::Color highlightColor = currentColor;
    highlightColor.r = std::min(255, int(highlightColor.r * 1.3f));
    highlightColor.g = std::min(255, int(highlightColor.g * 1.3f));
    highlightColor.b = std::min(255, int(highlightColor.b * 1.3f));
    topHighlight.setFillColor(highlightColor);
    window.draw(brick);
    window.draw(topHighlight);
    brick.setFillColor(sf::Color::Transparent);
    brick.setOutlineThickness(1);
    brick.setOutlineColor(sf::Color(0, 0, 0, 100));
    window.draw(brick);
    if (brickType == POWERUP) {
        sf::CircleShape indicator(3);
        indicator.setPosition(position.x + size.x / 2 - 3, position.y + size.y / 2 - 3);
        indicator.setFillColor(sf::Color::White);
        window.draw(indicator);
    }
}

sf::FloatRect Brick::getBounds() const { return sf::FloatRect(position, size); }
bool Brick::getIsDestroyed() const { return isDestroyed; }
int Brick::getPointValue() const { return pointValue; }
Brick::BrickType Brick::getBrickType() const { return static_cast<BrickType>(brickType); }
bool Brick::checkCollision(const Ball& ball) const {
    if (isDestroyed) return false;
    sf::Vector2f ballPos = ball.getPosition();
    float ballRadius = ball.getRadius();
    float closestX = std::max(position.x, std::min(ballPos.x, position.x + size.x));
    float closestY = std::max(position.y, std::min(ballPos.y, position.y + size.y));
    float distance = std::sqrt((ballPos.x - closestX) * (ballPos.x - closestX) +
        (ballPos.y - closestY) * (ballPos.y - closestY));
    return distance < ballRadius;
}