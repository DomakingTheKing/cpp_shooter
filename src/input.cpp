#include "engine.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        // Window closed
        if (event.type == Event::Closed) {
            window.close();
        }

        // Handle keyboard input
        if (event.type == Event::KeyPressed) {
            // Quit
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }

            // Pause
            if (event.key.code == Keyboard::P) {
                togglePause();
            }
        }

        // Handle mouse input
        if (event.type == Event::MouseButtonPressed) {
            // Shot
            if (event.mouseButton.button == Mouse::Left) {
                player.shot();
                soundEngine.getShotSfx()->setPitch(getRandomValue(1.5, 2));
                soundEngine.playSound(soundEngine.getShotSfx());
            }
        }
    }


    // Player movement
    Vector2f movement(0.f, 0.f);

    if (Keyboard::isKeyPressed(Keyboard::W)) {
        movement.y -= 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        movement.y += 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        movement.x -= 1.f;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        movement.x += 1.f;
    }

    // Normalize the movement vector if necessary
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0) {
        movement /= length; // Normalize the vector
    }

    // Apply speed
    movement *= player.getSpeed();

    // Update player position
    player.setPosition(player.getPosition() + movement);
}
