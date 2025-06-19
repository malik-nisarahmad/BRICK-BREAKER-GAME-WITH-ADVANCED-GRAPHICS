/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */

#include "Ball.h"
#include <cmath>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const float PI = 3.14159265f;

Ball::Ball(float x, float y, float r)
    : position(x, y), radius(r), isActive(false), color(sf::Color::Cyan) {
    velocity = sf::Vector2f(0, 0);
}

void Ball::launch(float angle, float speed) {
    velocity.x = std::cos(angle) * speed;
    velocity.y = -std::sin(angle) * speed;
    isActive = true;
}

void Ball::update(float deltaTime) {
    if (!isActive) return;

    trail.push_back(position);
    if (trail.size() > 15) {
        trail.erase(trail.begin());
    }

    position += velocity * deltaTime;

    if (position.x - radius <= 0 || position.x + radius >= WINDOW_WIDTH) {
        velocity.x = -velocity.x;
        position.x = std::max(radius, std::min(WINDOW_WIDTH - radius, position.x));
    }
    if (position.y - radius <= 0) {
        velocity.y = -velocity.y;
        position.y = radius;
    }
}

void Ball::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < trail.size(); ++i) {
        float alpha = (float(i) / trail.size()) * 100;
        sf::CircleShape trailBall(radius * 0.7f);
        trailBall.setPosition(trail[i].x - radius * 0.7f, trail[i].y - radius * 0.7f);
        sf::Color trailColor = color;
        trailColor.a = static_cast<sf::Uint8>(alpha);
        trailBall.setFillColor(trailColor);
        window.draw(trailBall);
    }

    sf::CircleShape outerGlow(radius * 1.5f);
    outerGlow.setPosition(position.x - radius * 1.5f, position.y - radius * 1.5f);
    sf::Color glowColor = color;
    glowColor.a = 50;
    outerGlow.setFillColor(glowColor);
    window.draw(outerGlow);

    sf::CircleShape ball(radius);
    ball.setPosition(position.x - radius, position.y - radius);
    ball.setFillColor(color);
    window.draw(ball);
}

sf::Vector2f Ball::getPosition() const { return position; }
sf::Vector2f Ball::getVelocity() const { return velocity; }
float Ball::getRadius() const { return radius; }
bool Ball::getIsActive() const { return isActive; }
void Ball::setPosition(sf::Vector2f pos) { position = pos; trail.clear(); }
void Ball::setVelocity(sf::Vector2f vel) { velocity = vel; }
void Ball::setActive(bool active) { isActive = active; }
void Ball::setColor(sf::Color col) { color = col; }
bool Ball::isOutOfBounds() const { return position.y > WINDOW_HEIGHT + radius; }
void Ball::reverse() { velocity.y = -velocity.y; }
sf::FloatRect Ball::getBounds() const {
    return sf::FloatRect(position.x - radius, position.y - radius, radius * 2, radius * 2);
}