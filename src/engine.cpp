//
// Created by domak on 06/07/2024.
//

#include "engine.hpp"
#include "player.hpp"

const Time Engine::TimePerFrame = seconds(1.f / 60.f);

Engine::Engine() {
    resolution = Vector2f(1280, 720);
    window.create(VideoMode(resolution.x, resolution.y), "Shooter", Style::Default);
    window.setFramerateLimit(FPS);
    window.setMouseCursorVisible(false);

    newPlayer();
}

void Engine::togglePause() {
    if (currentGameState == GameState::RUNNING) {
        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    }
    else if (currentGameState == GameState::PAUSED) {
        currentGameState = lastGameState;
    }
}

void Engine::newPlayer() {
    player.setPosition(Vector2f(500, 400));
}

void Engine::run() {
    while (window.isOpen()) {
        if (currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER) {
            input();

            // Draw the gameover screen
            if (currentGameState == GameState::GAMEOVER) {
                draw();
            }

            sleep(milliseconds(2)); // For not overloading CPU
            continue;
        }

        input();
        update();
        draw();
        // drawRay();

        window.display();
    }
}