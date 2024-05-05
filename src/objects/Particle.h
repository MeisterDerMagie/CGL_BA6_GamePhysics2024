#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "Event.hpp"
#include "Material.h"
#include "core/Colors.h"

class Particle {
public:
    virtual ~Particle() = default;

    enum ParticleType {Line, HalfSpace, Circle, AABB};
    
    Particle(glm::vec2 position, float mass, const Material& materialRef, ParticleType particleType, std::string tag = "", bool isTrigger = false);

    Event<void(std::shared_ptr<Particle>/*self*/, std::shared_ptr<Particle>/*other*/)> OnCollision;
    
    std::string Tag;
    ParticleType Type;
    glm::vec2 Position;
    float Mass;
    float InverseMass;
    std::shared_ptr<Material> material;
    bool IsTrigger;

    glm::vec2 Velocity;
    glm::vec2 TotalForce;

    virtual void SemiImpliciteEulerIntegration(float deltaTime);
    virtual void AddGravity(glm::vec2 gravityForce);
    virtual void AddForce(glm::vec2 force);
    virtual void AddImpulse(glm::vec2 impulse);
    virtual void ResetTotalForce();
    virtual void SetMass(float newMass);
    ImColor Color;
    bool DrawFilled = false;
    
    virtual void Draw() = 0;

private:
};
