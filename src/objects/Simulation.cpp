#include "Simulation.h"

#include <iostream>

#include "CollisionResolver.h"
#include "core/Draw.h"

Simulation::Simulation(glm::vec2 gravity)
    : Gravity(gravity) {
}

Simulation::~Simulation() = default;

void Simulation::AddParticle(std::shared_ptr<Particle> particle) {
    Particles.push_back(particle);
}

void Simulation::DestroyParticle(std::shared_ptr<Particle> particle) {
    Particles.erase(std::remove(Particles.begin(), Particles.end(), particle), Particles.end());
}

void Simulation::Update(float deltaTime) {
    int index = -1;
    for (auto particle : Particles) {
        index += 1;
        
        //simulate physics for all particles
        particle->ResetTotalForce();
        particle->AddGravity(Gravity);
        particle->SemiImpliciteEulerIntegration(deltaTime);

        //resolve collisions with other particles
        int otherIndex = -1;
        for (const auto& otherParticle : Particles) {

            //only check collision with particles that come later in the List
            otherIndex += 1;
            if(otherIndex <= index)
                continue;
            
            CollisionResolver::Resolve(particle, otherParticle);
        }
    }
}

void Simulation::Draw() {
    for (auto particle : Particles) {
        //std::cout << particle->Tag << " { " << particle->Color.Value.x << ", " << particle->Color.Value.y << ", " << particle->Color.Value.z << " }" << std::endl;

        Draw::SetColor(particle->Color);
        particle->Draw();
    }
}
