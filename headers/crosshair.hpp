//
// Created by domak on 07/07/2024.
//

#ifndef CPP_SHOOTER_CROSSHAIR_HPP
#define CPP_SHOOTER_CROSSHAIR_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Crosshair {
private:
    Texture texture;
    Sprite sprite;

public:
    explicit Crosshair();

    Vector2f getPosition();

    Sprite getShape();

    void updatePosition(Vector2f newPosition);
};


#endif //CPP_SHOOTER_CROSSHAIR_HPP
