#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Ball {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    bool isActive;
    sf::Color color;
    std::vector<sf::Vector2f> trail;

public:
    Ball(float x = 1200 / 2, float y = 800 - 100, float r = 10.0f);
    void launch(float angle, float speed = 400.0f);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    float getRadius() const;
    bool getIsActive() const;
    void setPosition(sf::Vector2f pos);
    void setVelocity(sf::Vector2f vel);
    void setActive(bool active);
    void setColor(sf::Color col);
    bool isOutOfBounds() const;
    void reverse();
    sf::FloatRect getBounds() const;
};