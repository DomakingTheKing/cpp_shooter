//
// Created by domak on 07/07/2024.
//

#ifndef CPP_SHOOTER_PARTICLESYSTEM_HPP
#define CPP_SHOOTER_PARTICLESYSTEM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Particle.hpp"

using namespace std;

class ParticleSystem {
public:
    void addParticle(const Particle& particle);

    vector<shared_ptr<Particle>> getParticles();

    void update();

private:
    vector<shared_ptr<Particle>> particles;
};

#endif //CPP_SHOOTER_PARTICLESYSTEM_HPP
