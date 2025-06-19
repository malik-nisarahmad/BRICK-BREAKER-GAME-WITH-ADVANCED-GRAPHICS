#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::Vector2f position;
    sf::Vector2f size;
    float speed;
    sf::Color color;

public:
    Paddle(float x = 1200 / 2 - 60, float y = 800 - 50);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void setSize(sf::Vector2f newSize);
    void setPosition(sf::Vector2f newPosition); // Added method
    float getBounceAngle(float ballX) const;
};
