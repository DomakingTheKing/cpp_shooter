#include "engine.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <thread>

using namespace sf;
bool isMouseButtonPressed = false;

void handleShooting(Player& player, SoundEngine& soundEngine) {
    while (isMouseButtonPressed) {
        player.shot();
        soundEngine.playSound(soundEngine.getShotSfx());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

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
                isMouseButtonPressed = true;
                std::thread shootingThread(handleShooting, std::ref(player), std::ref(soundEngine));
                shootingThread.detach();
            }
        }

        if (event.type == Event::MouseButtonReleased) {
            if (event.mouseButton.button == Mouse::Left) {
                isMouseButtonPressed = false;
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
