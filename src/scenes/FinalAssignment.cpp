#include "FinalAssignment.h"

#include "core/Draw.h"
#include "core/Colors.h"
#include "imgui.h"
#include <iostream>

std::shared_ptr<Spring> springPointer;
std::shared_ptr<AABB> aabbPointer;
std::shared_ptr<Circle> ballPointer;
bool isDragging = false;
bool showDragMeHint = true;

void FinalAssignment::OnEnable() {
    
    auto staticMaterial = Material(0, 0);
    auto ballMaterial = Material(0.8f, 0.9f);
    float ballMass = 0.5f;
    
    //aabb
    auto aabb = AABB(glm::vec2(-0.25f, 3), glm::vec2(0.25f, 3.5f), staticMaterial, false, false, "AABB");
    ImColor aabbColor = ImColor(0.7f, 0.8f, 0.9f, 1.0f);
    aabb.Color = aabbColor;
    aabb.DrawFilled = true;
    aabbPointer = std::make_shared<AABB>(aabb);
    simulation.SpawnParticle(aabbPointer);

    //ball
    auto ball = Circle(glm::vec2(0, -2), 0.5f, ballMass, ballMaterial, "Ball");
    ImColor ballColor = ImColor(0.6f, 0.8f, 0.6f, 1.0f);
    ball.Color = ballColor;
    ball.DrawFilled = true;
    ballPointer = std::make_shared<Circle>(ball);
    simulation.SpawnParticle(ballPointer);
    
    //spring
    auto spring = Spring(1.0f, aabbPointer, ballPointer);
    springPointer = std::make_shared<Spring>(spring);
    
    //set initial camera view
    orthographicSize = 11.0f;
}

void FinalAssignment::OnDisable() {
    simulation.DestroyAllParticles();
}

void FinalAssignment::Update(float deltaTime){

    // get mouse position
    mousePosition = Input::GetMousePos();

    // check if mouse is clicked
    bool leftMouseButtonClick = Input::IsMouseClicked(0);
    bool leftMouseButtonDown = Input::IsMouseDown(0);
    // 0: left click, 1: right click

    glm::vec2 mouseDeltaPosition = mousePosition - lastMousePosition;
    bool mouseIsOverAABB = MouseIsOverAABB();

    if(leftMouseButtonClick && mouseIsOverAABB) {
        isDragging = true;
        showDragMeHint = false;
    }

    if(Input::IsMouseReleased(0)) {
        isDragging = false;
    }

    if (isDragging) {
        aabbPointer->SetPosition(aabbPointer->Position + mouseDeltaPosition);
    }

    lastMousePosition = mousePosition;

    
    //spring physics (F=-kx)
    //k is a coefficient and x is the distance between the objects
    //F will determine the acceleration speed between object A(attractor) and object B(attracted).
    springPointer->B->Velocity.x += (springPointer->A->Position.x - springPointer->B->Position.x) * coefficient * deltaTime / ballPointer->Mass;
    springPointer->B->Velocity.y += (springPointer->A->Position.y - springPointer->B->Position.y) * coefficient * deltaTime;
    
    //apply damping
    springPointer->B->Velocity.x *= damping;
    springPointer->B->Velocity.y *= damping;
    
    //update Simulation
    simulation.Update(deltaTime);
}

bool FinalAssignment::MouseIsOverAABB() {
    bool isInsideAABBHorizontally = mousePosition.x >= aabbPointer->LowerLeft.x && mousePosition.x <= aabbPointer->UpperRight.x;
    bool isInsideAABBVertically = mousePosition.y >= aabbPointer->LowerLeft.y && mousePosition.y <= aabbPointer->UpperRight.y;
    return isInsideAABBHorizontally && isInsideAABBVertically;
}

void FinalAssignment::Draw() {

    //"drag me"
    if(showDragMeHint)
        Draw::Text(aabbPointer->Position + glm::vec2(0.55, 0), "<-- Drag me!");

    //draw spring
    DrawSpring();
    
    //draw particles
    simulation.Draw();
}

void FinalAssignment::DrawSpring() {
    float width = 0.2f;
    int segments = 20;
    for (int i = 0; i < segments; ++i) {
        glm::vec2 lineStart;
        glm::vec2 lineEnd;

        if(i == 0) {
            lineStart = aabbPointer->Position;
        } else {
            auto distance = (ballPointer->Position - aabbPointer->Position);
            auto startPoint = distance * (1.0f / static_cast<float>(segments) * static_cast<float>(i));

            auto direction = ((startPoint + aabbPointer->Position) - aabbPointer->Position);
            auto offset = glm::vec2(direction.y, -direction.x);
            offset = glm::normalize(offset);
            offset *= width;
            
            startPoint += offset;
            lineStart = startPoint + aabbPointer->Position;
        }

        width *= -1.0f;
        
        if(i == segments - 1) {
            lineEnd = ballPointer->Position;
        } else {
            auto distance = (ballPointer->Position - aabbPointer->Position);
            auto endPoint = distance * (1.0f / static_cast<float>(segments) * static_cast<float>(i + 1));

            auto direction = ((endPoint + aabbPointer->Position) - aabbPointer->Position);
            auto offset = glm::vec2(direction.y, -direction.x);
            offset = glm::normalize(offset);
            offset *= width;
            
            endPoint += offset;
            lineEnd = endPoint + aabbPointer->Position;
        }
        
        Draw::Line(lineStart, lineEnd);
    }
}

void FinalAssignment::DrawGUI() {
    ImGui::Begin("Inspector");
    bool restart = ImGui::SmallButton("Restart");
    if(restart) {
        showDragMeHint = true;
        coefficient = 200.0f;
        OnDisable();
        OnEnable();
    }

    ImGui::DragFloat("Coefficient", &coefficient, 0.1f);
    ImGui::DragFloat("Ball Mass", &ballPointer->Mass, 0.1f);
    
    ImGui::End();
}