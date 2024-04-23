#pragma once
#include <glm/vec2.hpp>

class Particle {
public:
    Particle(glm::vec2 position, float mass);

    glm::vec2 Position;
    float Mass;

    glm::vec2 Velocity;
    glm::vec2 TotalForce;

    virtual void AddForce(glm::vec2 force);
    virtual void AddImpulse(glm::vec2 impulse);
    virtual void ResetTotalForce();
};
