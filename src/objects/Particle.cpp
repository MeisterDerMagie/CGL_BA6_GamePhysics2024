#include "Particle.h"

void Particle::ResetTotalForce() {
    TotalForce = glm::vec2(0, 0);
}

Particle::Particle(glm::vec2 position, float mass)
    : Position(position), Mass(mass), Velocity(0, 0), TotalForce(0, 0) {}

void Particle::AddForce(glm::vec2 force) {
    TotalForce += force * Mass;
}

void Particle::AddImpulse(glm::vec2 impulse) {
    // impulses modify velocity directly instead of adding a force
    Velocity += impulse / Mass;
}
