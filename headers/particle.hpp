#ifndef CPP_SHOOTER_PARTICLE_HPP
#define CPP_SHOOTER_PARTICLE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Particle {
public:
    Particle(Vector2f position, Vector2f direction, Color color, float speed, float angle, float maxDistance, float size, bool fade);

    void update();
    bool isAlive() const;

    RectangleShape getShape() const;

private:
    Vector2f position;
    Vector2f direction;
    float speed;
    float angle;
    Color color;
    RectangleShape shape;
    float distanceTraveled;
    float maxDistance;
    bool fade;
};

#endif //CPP_SHOOTER_PARTICLE_HPP
