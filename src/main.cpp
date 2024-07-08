#include "engine.hpp"

RenderWindow window;
Engine engine;
ParticleSystem particleSystem;

int main() {
    engine.loadLevel(1);

    engine.run();

    return 0;
}
