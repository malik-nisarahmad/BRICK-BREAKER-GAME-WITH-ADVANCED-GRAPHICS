#pragma once
#include <SFML/Graphics.hpp>

class PowerUp {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f size;
    int type;
    bool isActive;
    float animationTime;

public:
    enum PowerUpType { PADDLE_EXTEND, MULTI_BALL, FIRE_BALL, EXTRA_LIFE, SCORE_MULTIPLIER };
    PowerUp(sf::Vector2f pos, PowerUpType t);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool getIsActive() const;
    void setInactive();
    PowerUpType getType() const;
};