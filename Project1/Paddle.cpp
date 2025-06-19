/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */

#include "Paddle.h"
#include <cmath>

const int WINDOW_WIDTH = 1200;
const float PI = 3.14159265f;

Paddle::Paddle(float x, float y)
    : position(x, y), size(120, 20), speed(500.0f), color(sf::Color::White) {
}

void Paddle::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        position.x += speed * deltaTime;
    }
    position.x = std::max(0.0f, std::min(WINDOW_WIDTH - size.x, position.x));
}

void Paddle::draw(sf::RenderWindow& window) {
    sf::RectangleShape paddle(size);
    paddle.setPosition(position);

    for (int i = 0; i < 5; ++i) {
        sf::RectangleShape layer(sf::Vector2f(size.x, size.y / 5));
        layer.setPosition(position.x, position.y + i * (size.y / 5));
        sf::Uint8 brightness = 255 - i * 30;
        layer.setFillColor(sf::Color(brightness, brightness, brightness));
        window.draw(layer);
    }

    sf::RectangleShape border(size);
    border.setPosition(position);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2);
    border.setOutlineColor(sf::Color::Cyan);
    window.draw(border);
}

sf::FloatRect Paddle::getBounds() const {
    return sf::FloatRect(position, size);
}

sf::Vector2f Paddle::getPosition() const { return position; }
sf::Vector2f Paddle::getSize() const { return size; }
void Paddle::setSize(sf::Vector2f newSize) { size = newSize; }
float Paddle::getBounceAngle(float ballX) const {
    float paddleCenter = position.x + size.x / 2;
    float relativeIntersect = ballX - paddleCenter;
    float normalizedIntersect = relativeIntersect / (size.x / 2);
    return normalizedIntersect * (PI / 3);
}
void Paddle::setPosition(sf::Vector2f newPosition) {
    this->position = newPosition;
}