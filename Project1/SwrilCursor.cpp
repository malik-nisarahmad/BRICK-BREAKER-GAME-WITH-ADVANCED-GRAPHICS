#include "SwrilCursor.h"
#include <cmath>
#include <iostream>
#include <algorithm>

const int BASE_WIDTH = 1200;
const int BASE_HEIGHT = 800;
const float PI = 3.14159265f;

SwirlCursor::SwirlCursor()
    : spawnTimer(0.0f), spawnInterval(0.006f), globalTime(0.0f),
    dissipationRate(0.95f), swirlingForce(100.0f), magneticForce(40.0f),
    turbulenceStrength(20.0f), velocityInfluence(0.4f),
    maxParticles(1000), maxTrailPoints(60), baseParticleSize(40.0f) {

    this->vertexArray = sf::VertexArray(sf::Points, 0);
    this->lastMousePos = sf::Vector2f(BASE_WIDTH / 2, BASE_HEIGHT / 2);
    this->mouseVelocity = sf::Vector2f(0, 0);

    // Custom vibrant colors for visibility
    this->primaryColor = sf::Color(255, 105, 180, 255);   // Hot Pink
    this->secondaryColor = sf::Color(0, 255, 255, 200);   // Cyan
    this->accentColor = sf::Color(255, 165, 0, 180);      // Orange
}

void SwirlCursor::update(float deltaTime, const sf::Vector2f& mousePos, sf::RenderWindow& window) {
    this->globalTime += deltaTime;

    // Update mouse trail and velocity
    this->updateMouseTrail(mousePos, deltaTime);

    // Spawn new particles
    this->spawnParticles(mousePos, deltaTime, window);

    // Update existing particles
    this->updateParticles(deltaTime, window);

    this->lastMousePos = mousePos;
}

void SwirlCursor::updateMouseTrail(const sf::Vector2f& mousePos, float deltaTime) {
    // Calculate mouse velocity with smoothing
    sf::Vector2f rawVelocity = (mousePos - this->lastMousePos) / deltaTime;
    this->mouseVelocity = this->mouseVelocity * 0.8f + rawVelocity * 0.2f;

    // Add current position to trail
    TrailPoint newPoint;
    newPoint.position = mousePos;
    newPoint.timestamp = this->globalTime;
    newPoint.velocity = this->mouseVelocity;

    this->mouseTrail.push_front(newPoint);

    // Remove old trail points
    while (this->mouseTrail.size() > this->maxTrailPoints) {
        this->mouseTrail.pop_back();
    }

    // Remove trail points older than 2 seconds
    while (!this->mouseTrail.empty() &&
        this->globalTime - this->mouseTrail.back().timestamp > 2.0f) {
        this->mouseTrail.pop_back();
    }
}

void SwirlCursor::spawnParticles(const sf::Vector2f& mousePos, float deltaTime, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / BASE_WIDTH;
    float scaleY = static_cast<float>(windowSize.y) / BASE_HEIGHT;
    float avgScale = (scaleX + scaleY) * 0.5f;

    // Calculate mouse speed for dynamic spawning
    float mouseSpeed = std::sqrt(this->mouseVelocity.x * this->mouseVelocity.x +
        this->mouseVelocity.y * this->mouseVelocity.y);

    // Adjust spawn rate based on mouse speed
    float dynamicSpawnInterval = this->spawnInterval / (1.0f + mouseSpeed * 0.02f);

    this->spawnTimer += deltaTime;

    if (this->spawnTimer >= dynamicSpawnInterval &&
        this->particles.size() < this->maxParticles &&
        mouseSpeed > 5.0f) { // Lower threshold for spawning

        // Spawn more particles for larger effect
        int particlesToSpawn = std::min(5, static_cast<int>(mouseSpeed * 0.08f) + 1);

        for (int i = 0; i < particlesToSpawn; ++i) {
            Particle particle;

            // Larger spawn radius for bigger initial effect
            float spawnRadius = 15.0f * avgScale;
            float spawnAngle = (rand() % 360) * PI / 180.0f;
            particle.position = mousePos + sf::Vector2f(
                std::cos(spawnAngle) * spawnRadius * ((rand() % 100) / 100.0f),
                std::sin(spawnAngle) * spawnRadius * ((rand() % 100) / 100.0f)
            );

            // Initial velocity influenced by mouse velocity and randomness
            sf::Vector2f inheritedVelocity = this->mouseVelocity * this->velocityInfluence;
            sf::Vector2f randomVelocity = sf::Vector2f(
                (rand() % 300 - 150) * 0.5f,
                (rand() % 300 - 150) * 0.5f
            );
            particle.velocity = inheritedVelocity + randomVelocity;
            particle.acceleration = sf::Vector2f(0, 0);

            // Particle properties with larger initial size
            particle.life = particle.maxLife = 1.5f + (rand() % 100) / 200.0f; // 1.5-2.0 seconds
            particle.size = this->baseParticleSize * avgScale * (1.2f + (rand() % 60) / 100.0f); // Larger initial size
            particle.rotation = (rand() % 360) * PI / 180.0f;
            particle.rotationSpeed = ((rand() % 200 - 100) / 100.0f) * PI; // -PI to PI rad/s
            particle.trailIndex = 0;
            particle.color = this->primaryColor;

            this->particles.push_back(particle);
        }

        this->spawnTimer = 0.0f;
    }
}

void SwirlCursor::updateParticles(float deltaTime, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    this->vertexArray.clear();

    for (auto& particle : this->particles) {
        // Use deltaTime instead of undefined deltaSize
        this->applySwirlingForces(particle, this->lastMousePos, deltaTime);

        // Update position and rotation
        particle.velocity += particle.acceleration * deltaTime;
        particle.velocity *= this->dissipationRate; // Increased drag for smoky fade
        particle.position += particle.velocity * deltaTime;
        particle.rotation += particle.rotationSpeed * deltaTime;

        // Update size and life for smoky effect
        particle.life -= deltaTime;
        float lifeRatio = particle.life / particle.maxLife;
        particle.size *= (1.0f - (1.0f - lifeRatio) * 0.8f); // Shrink over time

        // Complex color interpolation with smoky fade
        float colorPhase1 = lifeRatio;
        float colorPhase2 = std::sin(this->globalTime * 2.0f + particle.position.x * 0.01f) * 0.5f + 0.5f;
        float colorPhase3 = std::sin(this->globalTime * 1.5f + particle.position.y * 0.01f) * 0.5f + 0.5f;

        sf::Color currentColor;
        if (lifeRatio > 0.7f) {
            // Birth phase: large, vibrant
            float factor = (lifeRatio - 0.7f) / 0.3f;
            currentColor = this->interpolateColor(this->secondaryColor, this->primaryColor, factor);
        }
        else if (lifeRatio > 0.3f) {
            // Middle phase: transition to smoky
            float factor = (lifeRatio - 0.3f) / 0.4f;
            sf::Color baseColor = this->interpolateColor(this->accentColor, this->secondaryColor, factor);
            currentColor = sf::Color(
                std::min(255, static_cast<int>(baseColor.r * (0.7f + colorPhase2 * 0.3f))),
                std::min(255, static_cast<int>(baseColor.g * (0.7f + colorPhase3 * 0.3f))),
                std::min(255, static_cast<int>(baseColor.b * (0.8f + colorPhase2 * 0.2f))),
                static_cast<sf::Uint8>(baseColor.a * lifeRatio * 0.8f) // Fade alpha
            );
        }
        else {
            // Death phase: small, smoky fade
            float factor = lifeRatio / 0.3f;
            currentColor = this->accentColor;
            currentColor.a = static_cast<sf::Uint8>(currentColor.a * factor * factor * 0.5f); // Stronger fade
        }

        particle.color = currentColor;

        // Create vertex with enhanced visual representation
        sf::Vertex vertex(particle.position, particle.color);
        this->vertexArray.append(vertex);

        // Add glow for larger initial effect, reduced as it fades
        if (particle.size > 2.0f && lifeRatio > 0.3f) {
            float glowRadius = particle.size * 0.6f * lifeRatio; // Shrink glow with life
            for (int i = 0; i < 4; ++i) {
                float angle = i * PI * 0.5f + particle.rotation;
                sf::Vector2f offset(std::cos(angle) * glowRadius, std::sin(angle) * glowRadius);
                sf::Color glowColor = particle.color;
                glowColor.a = static_cast<sf::Uint8>(glowColor.a * 0.25f * lifeRatio); // Fading glow
                this->vertexArray.append(sf::Vertex(particle.position + offset, glowColor));
            }
        }
    }

    // Remove dead particles
    this->particles.erase(std::remove_if(this->particles.begin(), this->particles.end(),
        [](const Particle& p) { return p.life <= 0; }), this->particles.end());
}


void SwirlCursor::applySwirlingForces(Particle& particle, const sf::Vector2f& mousePos, float deltaTime) {
    sf::Vector2f toMouse = mousePos - particle.position;
    float distanceToMouse = std::sqrt(toMouse.x * toMouse.x + toMouse.y * toMouse.y);

    if (distanceToMouse > 0.1f) {
        // Normalize direction to mouse
        toMouse /= distanceToMouse;

        // Magnetic attraction (weaker at distance)
        float magneticStrength = this->magneticForce / (1.0f + distanceToMouse * 0.01f);
        sf::Vector2f magneticForce = toMouse * magneticStrength * deltaTime;

        // Swirling force perpendicular to mouse direction
        sf::Vector2f perpendicular(-toMouse.y, toMouse.x);
        float swirlingStrength = this->swirlingForce / (1.0f + distanceToMouse * 0.005f);

        // Add time-based variation to swirl
        float swirlingVariation = std::sin(this->globalTime * 3.0f + distanceToMouse * 0.02f) * 0.5f + 1.0f;
        sf::Vector2f swirlingForceVec = perpendicular * swirlingStrength * swirlingVariation * deltaTime;

        // Turbulence based on noise
        sf::Vector2f turbulence = this->getNoise(particle.position.x * 0.02f,
            particle.position.y * 0.02f,
            this->globalTime * 2.0f);
        turbulence *= this->turbulenceStrength * deltaTime;

        // Trail following force
        float trailInfluence = 0.0f;
        sf::Vector2f trailForce(0, 0);
        if (!this->mouseTrail.empty()) {
            trailInfluence = this->getDistanceFromTrail(particle.position);
            if (trailInfluence > 0) {
                // Find closest trail point
                float minDistance = 999999.0f;
                sf::Vector2f closestTrailPoint;
                for (const auto& trailPoint : this->mouseTrail) {
                    float dist = std::sqrt(std::pow(particle.position.x - trailPoint.position.x, 2) +
                        std::pow(particle.position.y - trailPoint.position.y, 2));
                    if (dist < minDistance) {
                        minDistance = dist;
                        closestTrailPoint = trailPoint.position;
                    }
                }

                if (minDistance > 0.1f) {
                    sf::Vector2f toTrail = closestTrailPoint - particle.position;
                    toTrail /= minDistance;
                    trailForce = toTrail * 20.0f * trailInfluence * deltaTime;
                }
            }
        }

        // Combine all forces
        particle.acceleration = magneticForce + swirlingForceVec + turbulence + trailForce;
    }
}

sf::Color SwirlCursor::interpolateColor(const sf::Color& color1, const sf::Color& color2, float factor) {
    factor = std::max(0.0f, std::min(1.0f, factor)); // Clamp factor
    return sf::Color(
        static_cast<sf::Uint8>(color1.r + (color2.r - color1.r) * factor),
        static_cast<sf::Uint8>(color1.g + (color2.g - color1.g) * factor),
        static_cast<sf::Uint8>(color1.b + (color2.b - color1.b) * factor),
        static_cast<sf::Uint8>(color1.a + (color2.a - color1.a) * factor)
    );
}

sf::Vector2f SwirlCursor::getNoise(float x, float y, float time) {
    // Simple Perlin-like noise for turbulence
    float noiseX = std::sin(x + time) * std::cos(y + time * 0.7f);
    float noiseY = std::cos(x + time * 0.8f) * std::sin(y + time);
    return sf::Vector2f(noiseX, noiseY);
}

float SwirlCursor::getDistanceFromTrail(const sf::Vector2f& position) {
    if (this->mouseTrail.empty()) return 0.0f;

    float minDistance = 999999.0f;
    for (const auto& trailPoint : this->mouseTrail) {
        float distance = std::sqrt(std::pow(position.x - trailPoint.position.x, 2) +
            std::pow(position.y - trailPoint.position.y, 2));
        minDistance = std::min(minDistance, distance);
    }

    // Return influence factor (1.0 at trail, 0.0 at distance > 100)
    return std::max(0.0f, 1.0f - minDistance / 100.0f);
}

void SwirlCursor::draw(sf::RenderWindow& window) {
    // Draw the main particle system
    if (this->vertexArray.getVertexCount() > 0) {
        window.draw(this->vertexArray);
    }

    // Draw additional visual enhancements for particles
    for (const auto& particle : this->particles) {
        if (particle.size > 1.5f) {
            sf::CircleShape circle(particle.size * 0.5f);
            circle.setPosition(particle.position - sf::Vector2f(particle.size * 0.5f, particle.size * 0.5f));
            circle.setFillColor(sf::Color(particle.color.r, particle.color.g, particle.color.b,
                static_cast<sf::Uint8>(particle.color.a * 0.2f)));
            window.draw(circle);
        }
    }
}

void SwirlCursor::setTheme(const std::string& theme) {
    // Keep custom vibrant colors regardless of theme for visibility
    this->primaryColor = sf::Color(255, 105, 180, 255);   // Hot Pink
    this->secondaryColor = sf::Color(0, 255, 255, 200);   // Cyan
    this->accentColor = sf::Color(255, 165, 0, 180);      // Orange

    // Update existing particles with new colors
    for (auto& particle : this->particles) {
        float lifeRatio = particle.life / particle.maxLife;
        if (lifeRatio > 0.7f) {
            float factor = (lifeRatio - 0.7f) / 0.3f;
            particle.color = this->interpolateColor(this->secondaryColor, this->primaryColor, factor);
        }
        else if (lifeRatio > 0.3f) {
            float factor = (lifeRatio - 0.3f) / 0.4f;
            particle.color = this->interpolateColor(this->accentColor, this->secondaryColor, factor);
        }
        else {
            particle.color = this->accentColor;
            particle.color.a = static_cast<sf::Uint8>(this->accentColor.a * (lifeRatio / 0.3f));
        }
    }
}