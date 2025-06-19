#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <deque>

class SwirlCursor {
private:
    struct Particle {
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float life;
        float maxLife;
        sf::Color color;
        float size;
        float rotation;
        float rotationSpeed;
        int trailIndex; // Position in the trail
    };

    struct TrailPoint {
        sf::Vector2f position;
        float timestamp;
        sf::Vector2f velocity;
    };

    std::vector<Particle> particles;
    std::deque<TrailPoint> mouseTrail;
    sf::Vector2f lastMousePos;
    sf::Vector2f mouseVelocity;
    sf::VertexArray vertexArray;

    // Timing and spawning
    float spawnTimer;
    float spawnInterval;
    float globalTime;

    // Physics parameters
    float dissipationRate;
    float swirlingForce;
    float magneticForce;
    float turbulenceStrength;
    float velocityInfluence;

    // Visual parameters
    int maxParticles;
    int maxTrailPoints;
    float baseParticleSize;

    // Theme colors
    sf::Color primaryColor;
    sf::Color secondaryColor;
    sf::Color accentColor;

public:
    SwirlCursor();
    void update(float deltaTime, const sf::Vector2f& mousePos, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setTheme(const std::string& theme);

private:
    void updateMouseTrail(const sf::Vector2f& mousePos, float deltaTime);
    void spawnParticles(const sf::Vector2f& mousePos, float deltaTime, sf::RenderWindow& window);
    void updateParticles(float deltaTime, sf::RenderWindow& window);
    void applySwirlingForces(Particle& particle, const sf::Vector2f& mousePos, float deltaTime);
    sf::Color interpolateColor(const sf::Color& color1, const sf::Color& color2, float factor);
    sf::Vector2f getNoise(float x, float y, float time);
    float getDistanceFromTrail(const sf::Vector2f& position);
};