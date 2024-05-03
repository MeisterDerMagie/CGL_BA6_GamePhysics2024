#include "Particle.h"

void Particle::ResetTotalForce() {
    TotalForce = glm::vec2(0, 0);
}

Particle::Particle(glm::vec2 position, float mass, float coefficientOfRestitution, ParticleType particleType, std::string tag)
    : Tag(std::move(tag)),
      Type(particleType),
      Position(position),
      Mass(mass), CoefficientOfResitution(coefficientOfRestitution),
      Velocity(0, 0),
      TotalForce(0, 0), Color(ImColor(255, 255, 255)) {
    if (mass == 0.0f)
        InverseMass = 0.0f;
    else
        InverseMass = 1.0f / mass;
}

void Particle::SemiImpliciteEulerIntegration(float deltaTime) {
    glm::vec2 acceleration = TotalForce * InverseMass;
    Velocity = Velocity + acceleration * deltaTime;
    Position = Position + Velocity * deltaTime;
}

void Particle::AddGravity(glm::vec2 gravityForce) {
    Particle::AddForce(gravityForce * Mass);
}

void Particle::AddForce(glm::vec2 force) {
    TotalForce += force;
}

void Particle::AddImpulse(glm::vec2 impulse) {
    // impulses modify velocity directly instead of adding a force
    Velocity += impulse * InverseMass;
}
