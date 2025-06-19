/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */

#include "Particle.h"

Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Color col, float l, float s)
    : position(pos), velocity(vel), color(col), life(l), maxLife(l), size(s) {
}

bool Particle::update(float deltaTime) {
    position += velocity * deltaTime;
    life -= deltaTime;
    float alpha = (life / maxLife) * 255.0f;
    color.a = static_cast<sf::Uint8>(std::max(0.0f, alpha));
    return life > 0;
}

void Particle::draw(sf::RenderWindow& window) {
    sf::CircleShape particle(size);
    particle.setPosition(position.x - size, position.y - size);
    particle.setFillColor(color);
    window.draw(particle);
}