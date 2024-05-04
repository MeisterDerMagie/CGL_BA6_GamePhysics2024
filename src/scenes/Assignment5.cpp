#include "Assignment5.h"

#include <iostream>

#include "imgui.h"
#include "objects/AABB.h"
#include "objects/Circle.h"
#include "objects/HalfSpace.h"

Assignment5::Assignment5()
    : simulation(Simulation(glm::vec2(0, -9.81f))) {
}

void Assignment5::OnEnable() {

    Material sharedMaterial = Material(0, 0);
    
    //add circle
    Circle circle = Circle(glm::vec2(1, 4), 1, 1, sharedMaterial, "Circle");
    std::shared_ptr<Circle> circlePointer = std::make_shared<Circle>(circle);
    simulation.SpawnParticle(circlePointer);

    //add AABB
    auto DestroyAABB = [this](const std::shared_ptr<Particle>& self, const std::shared_ptr<Particle>& other) 
    { 
        simulation.DestroyParticle(self); 
    };
    AABB aabb = AABB(glm::vec2(-0.5f, 0), glm::vec2(0.5f, 1.5f), sharedMaterial, true, false, "AABB");
    std::shared_ptr<AABB> aabbPointer = std::make_shared<AABB>(aabb);
    aabbPointer->OnCollision.Subscribe("DestroyAABB", DestroyAABB);
    simulation.SpawnParticle(aabbPointer);

    //add half space (floor)
    auto halfSpace = HalfSpace(glm::vec2(1, 0.3f), sharedMaterial, "Half Space");
    std::shared_ptr<HalfSpace> halfSpacePointer = std::make_shared<HalfSpace>(halfSpace);
    simulation.SpawnParticle(halfSpacePointer);
}

void Assignment5::OnDisable() {}

void Assignment5::Update(float deltaTime) {
    simulation.Update(deltaTime);
}

void Assignment5::Draw() {
    simulation.Draw();
}

void Assignment5::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}