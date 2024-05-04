#pragma once
#include <memory>

#include "ICollisionResolver.h"
#include "Particle.h"

class Simulation {
public:
    Simulation(glm::vec2 gravity, ICollisionResolver* collisionResolver);
    ~Simulation();
    
    void SpawnParticle(std::shared_ptr<Particle> particle);
    void DestroyParticle(std::shared_ptr<Particle> particle);
    void DestroyAllParticles();

    void Update(float deltaTime);
    void Draw();

    glm::vec2 Gravity;
    std::vector<std::shared_ptr<Particle>> Particles;
    std::vector<std::shared_ptr<Particle>> ParticlesToSpawn;
    std::vector<std::shared_ptr<Particle>> ParticlesToDestroy;

    ICollisionResolver* collision_resolver;
    
private:
};
