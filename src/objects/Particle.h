#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

class Particle {
public:
    virtual ~Particle() = default;

    enum ParticleType {Line, HalfSpace, Circle, AABB};
    
    Particle(glm::vec2 position, float mass, float coefficientOfRestitution, ParticleType particleType, std::string tag = "");

    std::string Tag;
    ParticleType Type;
    glm::vec2 Position;
    float Mass;
    float InverseMass;
    float CoefficientOfResitution; //bounciness / elasticity

    glm::vec2 Velocity;
    glm::vec2 TotalForce;

    virtual void SemiImpliciteEulerIntegration(float deltaTime);
    virtual void AddGravity(glm::vec2 gravityForce);
    virtual void AddForce(glm::vec2 force);
    virtual void AddImpulse(glm::vec2 impulse);
    virtual void ResetTotalForce();
    
    virtual void Draw() = 0;
};
