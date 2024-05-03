#include "Assignment4.h"

#include <iostream>

#include "imgui.h"
#include "objects/Circle.h"
#include "core/Draw.h"
#include <memory>

#include "objects/CollisionResolver.h"
#include "objects/Simulation.h"

Assignment4::Assignment4()
    : simulation(Simulation(glm::vec2(0, -9.81f))) {
}

Assignment4::~Assignment4() = default;

void HandleCollision(std::shared_ptr<Particle> self, std::shared_ptr<Particle> other) {
    //std::cout << self->Tag << " collided with " << other->Tag << std::endl;

    self->Color = Colors::red;
    other->Color = Colors::red;
}


void Assignment4::OnEnable() {
    
    Circle circle1 = Circle(glm::vec2(1, 2), 1, 1, 0.5f, "Circle 1");
    std::shared_ptr<Circle> circle1Pointer = std::make_shared<Circle>(circle1);
    circle1Pointer->OnCollision.Add(HandleCollision);
    simulation.AddParticle(circle1Pointer);
    
    auto circle2 = Circle(glm::vec2(1.5f, 8.0f), 2, 2, 0.5f, "Circle 2");
    std::shared_ptr<Circle> circle2Pointer = std::make_shared<Circle>(circle2);
    circle2Pointer->OnCollision.Add(HandleCollision);
    simulation.AddParticle(circle2Pointer);

    auto circle3 = Circle(glm::vec2(10.0f, 10.0f), 4, 10, 0.5f, "Circle 3");
    std::shared_ptr<Circle> circle3Pointer = std::make_shared<Circle>(circle3);
    circle3Pointer->OnCollision.Add(HandleCollision);
    simulation.AddParticle(circle3Pointer);

    auto circle4 = Circle(glm::vec2(-4.0f, 2.0f), 1, 0, 0.5f, "Circle 4 (static)");
    std::shared_ptr<Circle> circle4Pointer = std::make_shared<Circle>(circle4);
    circle4Pointer->OnCollision.Add(HandleCollision);
    simulation.AddParticle(circle4Pointer);
    
    auto halfSpace = HalfSpace(glm::vec2(1, 0.05f), "Half Space");
    std::shared_ptr<HalfSpace> halfSpacePointer = std::make_shared<HalfSpace>(halfSpace);
    halfSpacePointer->OnCollision.Add(HandleCollision);
    simulation.AddParticle(halfSpacePointer);
}

void Assignment4::OnDisable() {}

void Assignment4::Update(float deltaTime) {
    
    for (auto particle : simulation.Particles) {
        
        //reset IsColliding
        if(particle->Type == Particle::Circle) {
            std::shared_ptr<Circle> circle = std::dynamic_pointer_cast<Circle>(particle);
            circle->IsColliding = false;
        }
    }

    simulation.Update(deltaTime);
}

void Assignment4::Draw() {
    simulation.Draw();
}

void Assignment4::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}