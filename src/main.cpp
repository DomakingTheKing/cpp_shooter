#include "engine.hpp"
#include "soundengine.hpp"

RenderWindow window;
Engine engine;
SoundEngine soundEngine;
ParticleSystem particleSystem;

int main() {
    engine.loadLevel(1);

    engine.run();

    return 0;
}
