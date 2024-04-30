#include "Assignment4.h"

#include <iostream>

#include "imgui.h"
#include "objects/Circle.h"
#include "core/Colors.h"
#include "core/Draw.h"
#include <memory>

Assignment4::Assignment4() : gravity(0, -9.81f)
{}

Assignment4::~Assignment4() = default;

void Assignment4::OnEnable() {
    
    Circle circle1 = Circle(glm::vec2(1, 1), 1, 1, 0.5f);
    std::shared_ptr<Circle> circle1Pointer = std::make_shared<Circle>(circle1);
    particles.push_back(circle1Pointer);
    
    auto circle2 = Circle(glm::vec2(3.0f, 3.0f), 2, 2, 0.5f);
    std::shared_ptr<Circle> circle2Pointer = std::make_shared<Circle>(circle2);
    particles.push_back(circle2Pointer);
}

void Assignment4::OnDisable() {}

void Assignment4::Update(float deltaTime) {
    for (auto particle : particles) {

        //simulate physics for all particles
        particle->ResetTotalForce();
        particle->AddGravity(gravity);
        particle->SemiImpliciteEulerIntegration(deltaTime);
        if(particle->Type == Particle::Circle) {
            std::shared_ptr<Circle> circle = std::dynamic_pointer_cast<Circle>(particle);
            //do circle-specific things here

            //check collision with other circles
            circle->IsColliding = false;

            for (auto otherParticle : particles) {
                std::shared_ptr<Circle> other = std::dynamic_pointer_cast<Circle>(otherParticle);
                
                //don't collide with yourself
                if(circle == other) {
                    continue;
                }
                
                float distanceBetweenCircles = glm::length(circle->Position - other->Position);//glm::distance(circle->Position, other->Position);
                if(distanceBetweenCircles < circle->Radius || distanceBetweenCircles < other->Radius) {
                    //collision is happening
                    std::cout << "collide with other";
                    circle->IsColliding = true;
                    other->IsColliding = true;
                }
            }
        }
    }
}

void Assignment4::Draw() {
    //draw all circles
    for (auto particle : particles) {
        particle->Draw();
    }
}

void Assignment4::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}