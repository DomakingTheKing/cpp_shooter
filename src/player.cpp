#include <iostream>
#include <SFML/Graphics.hpp>
#include <valarray>
#include "player.hpp"
#include "engine.hpp"

using namespace std;

Player::Player() {
    speed = 5.f;

    if (!texture.loadFromFile("assets/textures/player.png")) {
        cerr << "Failed to load player.png" << endl;
    } else {
        // Crea una RenderTexture per ruotare la texture originale
        sf::RenderTexture renderTexture;
        renderTexture.create(texture.getSize().y, texture.getSize().x-2); // Inverti le dimensioni per la rotazione

        sf::Sprite tempSprite(texture);
        tempSprite.setOrigin(renderTexture.getSize().x / 2, renderTexture.getSize().y / 2);
        tempSprite.setRotation(-90);
        tempSprite.setPosition(renderTexture.getSize().y / 2, renderTexture.getSize().x / 2);

        // Disegna lo sprite ruotato nella RenderTexture
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(tempSprite);
        renderTexture.display();

        // Ottieni la texture ruotata dalla RenderTexture
        texture = renderTexture.getTexture();

        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2); // Imposta l'origine al centro della texture
        sprite.setScale(6, 6); // Per ingrandire l'immagine
    }

    // Imposta l'origine dello sprite al centro della texture
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
    // Aggiorna la posizione dello sprite
    sprite.setPosition(position);
}

void Player::setPosition(sf::Vector2f newPosition) {
    position = newPosition;
    sprite.setPosition(position); // Aggiorna la posizione dello sprite
}

void Player::setRotation(float newRotation) {
    rotation = newRotation;
    sprite.setRotation(rotation); // Aggiorna la rotazione dello sprite
}

void Player::update() {
    sprite.setPosition(position);
    sprite.setRotation(rotation);
}

void Player::shot() {
    // Calcola il vettore direzionale
    sf::Vector2f direction = sf::Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y) - position;

    // Normalizza il vettore direzionale
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }

    particleSystem.addParticle(Particle(position, direction, Color::Red, 25.0f, 0.0f, 0, 8.0f, false));
    particleSystem.addParticle(Particle(position, direction, Color::Red, 25.0f, 15.0f, 0, 10.0f, false));
    particleSystem.addParticle(Particle(position, direction, Color::Red, 25.0f, -15.0f, 0, 10.0f, false));
}

sf::Vector2f Player::getPosition() {
    return position;
}

sf::Sprite Player::getShape() {
    return sprite;
}

sf::VertexArray Player::getOutline() {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::VertexArray outline(sf::LineStrip, 5);

    outline[0].position = sf::Vector2f(bounds.left, bounds.top);
    outline[1].position = sf::Vector2f(bounds.left + bounds.width, bounds.top);
    outline[2].position = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
    outline[3].position = sf::Vector2f(bounds.left, bounds.top + bounds.height);
    outline[4].position = sf::Vector2f(bounds.left, bounds.top);

    for (int i = 0; i < 5; ++i) {
        outline[i].color = sf::Color::White; // Puoi cambiare il colore a tuo piacimento
    }

    return outline;
}

float Player::getSpeed() {
    return speed;
}
