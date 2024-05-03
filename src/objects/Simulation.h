#pragma once
#include <memory>

#include "Particle.h"

class Simulation {
public:
    Simulation(glm::vec2 gravity);
    ~Simulation();
    
    void AddParticle(std::shared_ptr<Particle> particle);
    void DestroyParticle(std::shared_ptr<Particle> particle);

    void Update(float deltaTime);
    void Draw();

    glm::vec2 Gravity;
    std::vector<std::shared_ptr<Particle>> Particles;

private:
};
