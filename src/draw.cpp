//
// Created by domak on 06/07/2024.
//

#include "engine.hpp"

void Engine::draw() {
    window.clear(Color::Black);

    window.draw(background);

    window.draw(player.getShape());
    window.draw(player.getOutline());
    window.draw(crosshair.getShape());

    for (const auto& particle : particleSystem.getParticles()) {
        window.draw(particle->getShape());
    }
}

void Engine::drawRay() {
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = playerPosition;
    line[0].color = sf::Color::Green;
    line[1].position = sf::Vector2f(mousePosition.x, mousePosition.y);
    line[1].color = sf::Color::Green;

    window.draw(line);
}