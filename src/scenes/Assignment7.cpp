#include "Assignment7.h"

#include "imgui.h"
#include "objects/Circle.h"

void Assignment7::OnEnable() {
    
    //drag circles
    Material circle1Material = Material(1, 0.5f);
    Circle circle1 = Circle(glm::vec2(1, 4), 0.5f, 1, circle1Material, "Ball1");
    std::shared_ptr<Circle> circle1Ptr = std::make_shared<Circle>(circle1);
    simulation.SpawnParticle(circle1Ptr);

    Material circle2Material = Material(3, 0.5f);
    Circle circle2 = Circle(glm::vec2(3, 4), 0.5f, 1, circle2Material, "Ball2");
    std::shared_ptr<Circle> circle2Ptr = std::make_shared<Circle>(circle2);
    simulation.SpawnParticle(circle2Ptr);

    //elasticity circles
    //cor 1
    Material circle3Material = Material(2, 1.0f);
    Circle circle3 = Circle(glm::vec2(5, 4), 0.5f, 1, circle3Material, "Ball3");
    std::shared_ptr<Circle> circle3Ptr = std::make_shared<Circle>(circle3);
    simulation.SpawnParticle(circle3Ptr);

    Material circle4Material = Material(2, 1.0f);
    Circle circle4 = Circle(glm::vec2(5, 7), 0.5f, 1, circle4Material, "Ball4");
    std::shared_ptr<Circle> circle4Ptr = std::make_shared<Circle>(circle4);
    simulation.SpawnParticle(circle4Ptr);

    //cor 0.5
    Material circle5Material = Material(2, 0.5f);
    Circle circle5 = Circle(glm::vec2(7, 4), 0.5f, 1, circle5Material, "Ball5");
    std::shared_ptr<Circle> circle5Ptr = std::make_shared<Circle>(circle5);
    simulation.SpawnParticle(circle5Ptr);

    Material circle6Material = Material(2, 0.5f);
    Circle circle6 = Circle(glm::vec2(7, 7), 0.5f, 1, circle6Material, "Ball6");
    std::shared_ptr<Circle> circle6Ptr = std::make_shared<Circle>(circle6);
    simulation.SpawnParticle(circle6Ptr);

    //cor 0
    Material circle7Material = Material(2, 0.0f);
    Circle circle7 = Circle(glm::vec2(9, 4), 0.5f, 1, circle7Material, "Ball7");
    std::shared_ptr<Circle> circle7Ptr = std::make_shared<Circle>(circle7);
    simulation.SpawnParticle(circle7Ptr);

    Material circle8Material = Material(2, 0.0f);
    Circle circle8 = Circle(glm::vec2(9, 7), 0.5f, 1, circle8Material, "Ball8");
    std::shared_ptr<Circle> circle8Ptr = std::make_shared<Circle>(circle8);
    simulation.SpawnParticle(circle8Ptr);

    //different masses
    Material circle9Material = Material(2, 0.5f);
    Circle circle9 = Circle(glm::vec2(12, 4), 0.5f, 1, circle9Material, "Ball9");
    std::shared_ptr<Circle> circle9Ptr = std::make_shared<Circle>(circle9);
    simulation.SpawnParticle(circle9Ptr);

    Material circle10Material = Material(2, 0.5f);
    Circle circle10 = Circle(glm::vec2(12, 7), 1.0f, 10, circle10Material, "Ball10");
    std::shared_ptr<Circle> circle10Ptr = std::make_shared<Circle>(circle10);
    simulation.SpawnParticle(circle10Ptr);

    //aabb
    Material circle11Material = Material(2, 0.2f);
    Circle circle11 = Circle(glm::vec2(15, 4), 0.5f, 1, circle11Material, "Ball11");
    std::shared_ptr<Circle> circle11Ptr = std::make_shared<Circle>(circle11);
    simulation.SpawnParticle(circle11Ptr);

    AABB aabb = AABB(glm::vec2(14, 7), glm::vec2(16, 8), Material(0,0), true, false, "AABB");
    std::shared_ptr<AABB> aabbPointer = std::make_shared<AABB>(aabb);
    simulation.SpawnParticle(aabbPointer);

    
    //initial velocity
    circle1Ptr->Velocity = glm::vec2(0, 5);
    circle2Ptr->Velocity = glm::vec2(0, 5);
    
    circle3Ptr->Velocity = glm::vec2(0, 10);
    circle5Ptr->Velocity = glm::vec2(0, 10);
    circle7Ptr->Velocity = glm::vec2(0, 10);
    circle9Ptr->Velocity = glm::vec2(0, 10);
    circle11Ptr->Velocity = glm::vec2(0, 10);

    //set initial camera view
    cameraCenter = glm::vec2(8.4f, 6.0f);
    orthographicSize = 10.0f;
}

void Assignment7::OnDisable() {
    simulation.DestroyAllParticles();
}

void Assignment7::Update(float deltaTime) {
    simulation.Update(deltaTime);
}

void Assignment7::Draw() {
    simulation.Draw();
}

void Assignment7::DrawGUI() {
    ImGui::Begin("Inspector");
    bool restart = ImGui::SmallButton("Restart");
    if(restart) {
        OnDisable();
        OnEnable();
    }
    ImGui::End();
}
