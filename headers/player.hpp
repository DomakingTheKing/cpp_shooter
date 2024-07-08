//
// Created by domak on 07/07/2024.
//

#ifndef CPP_SHOOTER_PLAYER_HPP
#define CPP_SHOOTER_PLAYER_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
    Vector2f position;
    float rotation;

    float speed;

    Texture texture;
    Sprite sprite;

public:
    explicit Player();

    Vector2f getPosition();

    Sprite getShape();
    VertexArray getOutline();
    float getSpeed();

    void setPosition(Vector2f newPosition);
    void setRotation(float newRotation);
    void update();

    void shot();
};


#endif //CPP_SHOOTER_PLAYER_HPP
