#include "ParticleSystem.hpp"

void ParticleSystem::addParticle(const Particle& particle) {
    particles.push_back(make_shared<Particle>(particle));
}

vector<shared_ptr<Particle>> ParticleSystem::getParticles() {
    return particles;
}

void ParticleSystem::update() {
    for (auto it = particles.begin(); it != particles.end();) {
        (*it)->update();
        if (!(*it)->isAlive()) {
            it = particles.erase(it);
        } else {
            ++it;
        }
    }
}
