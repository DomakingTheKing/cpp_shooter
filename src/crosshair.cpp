//
// Created by domak on 07/07/2024.
//

#include <iostream>
#include "crosshair.hpp"

using namespace std;

Crosshair::Crosshair(){
    if (!texture.loadFromFile("assets/textures/crosshair.png")) {
        cerr << "Failed to load crosshair.png" << endl;
    } else {
        sprite.setTexture(texture);
        sprite.scale(4, 4);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    }
}

void Crosshair::updatePosition(sf::Vector2f newPosition) {
    sprite.setPosition(newPosition);
}

Vector2f Crosshair::getPosition() {
    return sprite.getPosition();
}

Sprite Crosshair::getShape() {
    return sprite;
}