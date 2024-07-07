//
// Created by domak on 06/07/2024.
//

#include <fstream>
#include <iostream>
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

/**
 * Check the levels manifest file and make sure that we can open each level file.
 * add good level file names to the 'levels' vector and increment the maxLevels var.
 */
void Engine::checkLevelFiles() {
    // Load the levels manifest file
    ifstream levelsManifest ("assets/levels/levels.txt");
    ifstream testFileBG;
    ifstream testFileCollisions;
    for (string manifestLine; getline(levelsManifest, manifestLine);) {
        // Check that we can open the level file
        testFileBG.open("assets/levels/backgrounds/" + manifestLine);
        testFileCollisions.open("assets/levels/collisions/" + manifestLine);
        if (testFileBG.is_open() && testFileCollisions.is_open()) {
            // The level file opens, add it to the list of available levels
            levels.emplace_back("assets/levels/backgrounds/" + manifestLine);
            testFileBG.close();
            testFileCollisions.close();
            maxLevels++;
        }
    }
}

/**
 * Load a level from a file and check for 'x' characters to add wall sections.
 * @param levelNumber int - the number of the level to load.
 */
void Engine::loadLevel(int levelNumber) {
    string levelFile = levels[levelNumber - 1];
    loadLevelBackground(levelFile);
}

void Engine::loadLevelBackground(String levelFile) {
    Texture background;
    if(!background.loadFromFile("assets/levels/backgrounds/" + levelFile)) {
        cerr << "Failed to load background" << endl;
    } else {
        Sprite backgroundSprite;
        backgroundSprite.setTexture(background);
    }
}

void Engine::loadLevelCollisions(String levelFile) {

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