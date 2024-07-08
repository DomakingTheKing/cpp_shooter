//
// Created by domak on 06/07/2024.
//

#ifndef CPP_SHOOTER_ENGINE_HPP
#define CPP_SHOOTER_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "player.hpp"
#include "crosshair.hpp"
#include "particleSystem.hpp"
#include "soundengine.hpp"

using namespace sf;

extern SoundEngine soundEngine;
extern ParticleSystem particleSystem;
extern RenderWindow window;
extern vector<FloatRect> collisionBounds;

class Engine {
private:
    // Window
    Vector2f resolution;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    Texture backgroundTexture;
    Sprite background;

    int currentLevel{};
    int maxLevels;
    vector<String> levels;

    void loadLevelBackground(String levelFile);
    void loadLevelCollisions(String levelFile);

    VertexArray collisionVertices;

    int currentGameState{};
    int lastGameState{};

    Player player;
    Crosshair crosshair;
public:
    enum Direction { UP, RIGHT, DOWN, LEFT };
    enum GameState { RUNNING, PAUSED, GAMEOVER };

    Engine();

    void togglePause();

    void newPlayer();

    void checkLevelFiles();
    void loadLevel(int levelNumber);

    void run();
    void input();
    void update();
    void draw();

    void drawRay();

    static double getRandomValue(float min, float max);
};


#endif //CPP_SHOOTER_ENGINE_HPP
