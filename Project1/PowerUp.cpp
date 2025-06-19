
/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */

#include "PowerUp.h"
#include <cmath>

const int WINDOW_HEIGHT = 800;

PowerUp::PowerUp(sf::Vector2f pos, PowerUpType t)
    : position(pos), velocity(0, 100), size(30, 30), type(t), isActive(true), animationTime(0) {
}

void PowerUp::update(float deltaTime) {
    if (!isActive) return;
    position += velocity * deltaTime;
    animationTime += deltaTime;
    if (position.y > WINDOW_HEIGHT) {
        isActive = false;
    }
}

void PowerUp::draw(sf::RenderWindow& window) {
    if (!isActive) return;
    sf::RectangleShape powerup(size);
    powerup.setPosition(position);
    powerup.setOrigin(size.x / 2, size.y / 2);
    powerup.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    powerup.setRotation(animationTime * 90);
    sf::Color colors[] = {
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Red,
        sf::Color::Magenta,
        sf::Color::Yellow
    };
    powerup.setFillColor(colors[type]);
    sf::RectangleShape glow(sf::Vector2f(size.x * 1.5f, size.y * 1.5f));
    glow.setOrigin(size.x * 0.75f, size.y * 0.75f);
    glow.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    sf::Color glowColor = colors[type];
    glowColor.a = 50;
    glow.setFillColor(glowColor);
    glow.setRotation(animationTime * 90);
    window.draw(glow);
    window.draw(powerup);
}

sf::FloatRect PowerUp::getBounds() const { return sf::FloatRect(position, size); }
bool PowerUp::getIsActive() const { return isActive; }
void PowerUp::setInactive() { isActive = false; }
PowerUp::PowerUpType PowerUp::getType() const { return static_cast<PowerUpType>(type); }