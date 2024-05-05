#include "Assignment4.h"

#include <iostream>

#include "imgui.h"
#include "objects/Circle.h"
#include "core/Draw.h"
#include <memory>

#include "objects/CollisionResolver_Elastic.h"
#include "objects/Simulation.h"

Assignment4::Assignment4()
    : simulation(Simulation(glm::vec2(0, -9.81f), new CollisionResolver_Elastic())) {
}

Assignment4::~Assignment4() = default;

void HandleCollision(std::shared_ptr<Particle> self, std::shared_ptr<Particle> other) {
    //std::cout << self->Tag << " collided with " << other->Tag << std::endl;

    self->Color = Colors::red;
    other->Color = Colors::red;
}


void Assignment4::OnEnable() {

    Material sharedMaterial = Material(0, 0);
    
    Circle circle1 = Circle(glm::vec2(1, 2), 1, 1, sharedMaterial, "Circle 1");
    std::shared_ptr<Circle> circle1Pointer = std::make_shared<Circle>(circle1);
    circle1Pointer->OnCollision.Subscribe("Circle1Collision", HandleCollision);
    simulation.SpawnParticle(circle1Pointer);
    
    auto circle2 = Circle(glm::vec2(1.5f, 8.0f), 2, 2, sharedMaterial, "Circle 2");
    std::shared_ptr<Circle> circle2Pointer = std::make_shared<Circle>(circle2);
    circle2Pointer->OnCollision.Subscribe("Circle2Collision", HandleCollision);
    simulation.SpawnParticle(circle2Pointer);

    auto circle3 = Circle(glm::vec2(10.0f, 10.0f), 4, 10, sharedMaterial, "Circle 3");
    std::shared_ptr<Circle> circle3Pointer = std::make_shared<Circle>(circle3);
    circle3Pointer->OnCollision.Subscribe("Circle3Collision", HandleCollision);
    simulation.SpawnParticle(circle3Pointer);

    auto circle4 = Circle(glm::vec2(-4.0f, 2.0f), 1, 0, sharedMaterial, "Circle 4 (static)");
    std::shared_ptr<Circle> circle4Pointer = std::make_shared<Circle>(circle4);
    circle4Pointer->OnCollision.Subscribe("Circle4Collision", HandleCollision);
    simulation.SpawnParticle(circle4Pointer);
    
    auto halfSpace = HalfSpace(glm::vec2(1, 0.05f), sharedMaterial, "Half Space");
    std::shared_ptr<HalfSpace> halfSpacePointer = std::make_shared<HalfSpace>(halfSpace);
    halfSpacePointer->OnCollision.Subscribe("HalfSpaceCollision", HandleCollision);
    simulation.SpawnParticle(halfSpacePointer);

    //set initial camera view
    cameraCenter = glm::vec2(0, 6.0f);
    orthographicSize = 16.0f;
}

void Assignment4::OnDisable() {
    simulation.DestroyAllParticles();
}

void Assignment4::Update(float deltaTime) {
    simulation.Update(deltaTime);
}

void Assignment4::Draw() {
    simulation.Draw();
}

void Assignment4::DrawGUI() {
    ImGui::Begin("Inspector");
    bool restart = ImGui::SmallButton("Restart");
    if(restart) {
        OnDisable();
        OnEnable();
    }
    ImGui::End();
}