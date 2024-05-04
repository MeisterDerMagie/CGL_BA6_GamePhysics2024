#include "Simulation.h"

#include <iostream>

#include "CollisionResolver_Elastic.h"
#include "core/Draw.h"

Simulation::Simulation(glm::vec2 gravity, ICollisionResolver* collisionResolver)
    : Gravity(gravity),
      collision_resolver(collisionResolver) {
}

Simulation::~Simulation() = default;

void Simulation::SpawnParticle(std::shared_ptr<Particle> particle) {
    ParticlesToSpawn.push_back(particle);
}

void Simulation::DestroyParticle(std::shared_ptr<Particle> particle) {
    ParticlesToDestroy.push_back(particle);
}

void Simulation::DestroyAllParticles() {
    for (auto particle : Particles) {
        ParticlesToDestroy.push_back(particle);
    }
    for (auto particle : ParticlesToDestroy) {
        Particles.erase(std::remove(Particles.begin(), Particles.end(), particle), Particles.end());
    }
}

void Simulation::Update(float deltaTime) {
    int index = -1;
    for (auto particle : Particles) {
        index += 1;

        //std::cout << particle->Tag << ": Pos{ " << particle->Position.x << ", " << particle->Position.y << " }" << std::endl;
        
        //simulate physics for all particles
        particle->ResetTotalForce();
        particle->AddGravity(Gravity);
        particle->Velocity = particle->Velocity * (1.0f - particle->material->DampingFactor * deltaTime); //linear drag
        particle->SemiImpliciteEulerIntegration(deltaTime);

        //resolve collisions with other particles
        int otherIndex = -1;
        for (const auto& otherParticle : Particles) {

            //only check collision with particles that come later in the List
            otherIndex += 1;
            if(otherIndex <= index)
                continue;
            
            collision_resolver->Resolve(particle, otherParticle);
        }
    }

    //destroy particles
    for (auto particle : ParticlesToDestroy) {
        Particles.erase(std::remove(Particles.begin(), Particles.end(), particle), Particles.end());
    }
    ParticlesToDestroy.clear();

    //spawn particles
    for (auto particle : ParticlesToSpawn) {
        Particles.push_back(particle);
    }
    ParticlesToSpawn.clear();
}

void Simulation::Draw() {
    for (auto particle : Particles) {
        //std::cout << particle->Tag << " { " << particle->Color.Value.x << ", " << particle->Color.Value.y << ", " << particle->Color.Value.z << " }" << std::endl;

        Draw::SetColor(particle->Color);
        particle->Draw();
    }
}
