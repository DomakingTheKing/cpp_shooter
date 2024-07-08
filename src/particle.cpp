#include "Particle.hpp"
#include "engine.hpp"
#include <cmath>

Particle::Particle(Vector2f position, Vector2f direction, Color color, float speed, float angle, float maxDistance, float size, bool fade)
        : position(position), direction(direction), color(color), speed(speed), angle(angle), maxDistance(maxDistance), fade(fade), distanceTraveled(0) {

    // Calcola l'angolo in radianti
    float radianAngle = angle * (3.14159265 / 180.0);

    // Calcola la nuova direzione basata sull'angolo
    float newX = direction.x * cos(radianAngle) - direction.y * sin(radianAngle);
    float newY = direction.x * sin(radianAngle) + direction.y * cos(radianAngle);
    this->direction = Vector2f(newX, newY);

    shape.setSize(Vector2f(size, size));
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Particle::update() {
    position += direction * speed;
    distanceTraveled += speed;

    if (fade && maxDistance > 0) {
        float alpha = 255 * (1 - (distanceTraveled / maxDistance));
        color.a = static_cast<Uint8>(alpha);
        shape.setFillColor(color);
    }

    shape.setPosition(position);
}

bool Particle::isAlive() const {
    if (maxDistance > 0) {
        return distanceTraveled < maxDistance;
    } else {
        // Controlla se la particella interseca una delle collision shapes
        FloatRect particleBounds = shape.getGlobalBounds();
        for (const auto& bound : collisionBounds) {
            if (particleBounds.intersects(bound)) {
                return false;
            }
        }

        // Controlla se la particella è ancora all'interno della finestra
        return position.x >= 0 && position.x <= window.getSize().x && position.y >= 0 && position.y <= window.getSize().y;
    }
}


RectangleShape Particle::getShape() const {
    return shape;
}
