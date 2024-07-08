#include <cmath>
#include "engine.hpp"

void Engine::update() {
    // Player
    // Calcola l'angolo in radianti
    float angle = atan2(Mouse::getPosition(window).y - player.getPosition().y, Mouse::getPosition(window).x - player.getPosition().x);

    // Converti l'angolo in gradi
    float angleInDegrees = angle * 180 / M_PI;

    // Imposta la rotazione del giocatore
    player.setRotation(angleInDegrees);

    player.update();

    // Crosshair
    crosshair.updatePosition(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
    if (crosshair.getShape().getGlobalBounds().intersects(collisionVertices.getBounds())){
        crosshair.getShape().setColor(Color::Black);
    } else {
        crosshair.getShape().setColor(Color::White);
    }

    // Particles
    particleSystem.update();
}
