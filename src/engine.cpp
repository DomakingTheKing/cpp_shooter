//
// Created by domak on 06/07/2024.
//

#include <fstream>
#include <iostream>
#include <random>
#include "engine.hpp"
#include "player.hpp"

const Time Engine::TimePerFrame = seconds(1.f / 60.f);
vector<FloatRect> collisionBounds;

Engine::Engine() {
    resolution = Vector2f(1280, 720);
    window.create(VideoMode(resolution.x, resolution.y), "Shooter", Style::Default);
    window.setFramerateLimit(FPS);
    window.setMouseCursorVisible(false);

    checkLevelFiles();
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
            levels.emplace_back(manifestLine);
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
    loadLevelCollisions(levelFile);
}

void Engine::loadLevelBackground(String levelFile) {
    if(!backgroundTexture.loadFromFile("assets/levels/backgrounds/" + levelFile)) {
        cerr << "Failed to load background" << endl;
    } else {
        background.setTexture(backgroundTexture);
        background.scale(10,10);
    }
}


void Engine::loadLevelCollisions(String levelFile) {
    Texture collisionTexture;
    if (!collisionTexture.loadFromFile("assets/levels/collisions/" + levelFile)) {
        cerr << "Failed to load collision map" << endl;
        return;
    }

    Image collisionImage = collisionTexture.copyToImage();
    Vector2u imageSize = collisionImage.getSize();

    // Scale factor
    float scaleFactor = 10.0f;

    // Create a new image with scaled dimensions
    Image scaledImage;
    scaledImage.create(imageSize.x * scaleFactor, imageSize.y * scaleFactor);

    // Copy and scale pixels from the original image to the new image
    for (unsigned int y = 0; y < imageSize.y; ++y) {
        for (unsigned int x = 0; x < imageSize.x; ++x) {
            Color pixelColor = collisionImage.getPixel(x, y);
            for (unsigned int dy = 0; dy < scaleFactor; ++dy) {
                for (unsigned int dx = 0; dx < scaleFactor; ++dx) {
                    scaledImage.setPixel(x * scaleFactor + dx, y * scaleFactor + dy, pixelColor);
                }
            }
        }
    }

    // Use the scaled image to create collision shapes
    Vector2u scaledSize = scaledImage.getSize();
    collisionVertices.setPrimitiveType(Quads);
    for (unsigned int y = 0; y < scaledSize.y; ++y) {
        for (unsigned int x = 0; x < scaledSize.x; ++x) {
            Color pixelColor = scaledImage.getPixel(x, y);
            if (pixelColor == Color::Red) {
                // Create a quad for each red pixel
                Vertex v1(Vector2f(x, y), Color::Transparent);
                Vertex v2(Vector2f(x + 1, y), Color::Transparent);
                Vertex v3(Vector2f(x + 1, y + 1), Color::Transparent);
                Vertex v4(Vector2f(x, y + 1), Color::Transparent);

                collisionVertices.append(v1);
                collisionVertices.append(v2);
                collisionVertices.append(v3);
                collisionVertices.append(v4);

                // Add the bounds of this quad to collisionBounds
                FloatRect bounds(x, y, 1, 1);
                collisionBounds.push_back(bounds);
            }
        }
    }
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
        drawRay();

        window.display();
    }
}

double Engine::getRandomValue(float min, float max) {
    // Usa la libreria di numeri casuali di C++11
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}