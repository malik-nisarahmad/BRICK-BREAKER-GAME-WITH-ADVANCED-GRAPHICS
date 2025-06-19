#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Brick {
private:
    sf::Vector2f position;
    sf::Vector2f size;
    int strength;
    int maxStrength;
    int brickType;
    bool isDestroyed;
    int pointValue;
    sf::Color baseColor;
    float animationTime;

public:
    enum BrickType { STANDARD, STRONG, UNBREAKABLE, POWERUP };
    Brick(float x, float y, BrickType type = STANDARD);
    bool takeDamage();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool getIsDestroyed() const;
    int getPointValue() const;
    BrickType getBrickType() const;
    bool checkCollision(const Ball& ball) const;
};