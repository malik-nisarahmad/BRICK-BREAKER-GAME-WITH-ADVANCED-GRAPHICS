#pragma once
#pragma once
#include <SFML/Graphics.hpp>

class Particle {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float life;
    float maxLife;
    float size;

public:
    Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Color col, float l, float s);
    bool update(float deltaTime);
    void draw(sf::RenderWindow& window);
};