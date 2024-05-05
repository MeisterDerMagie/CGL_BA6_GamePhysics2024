#include "Assignment8.h"

#include <iostream>

#include "imgui.h"
#include "core/Draw.h"
#include "objects/PoolObjectBall.h"

void Assignment8::OnEnable() {
    
    auto staticMaterial = Material(0, 0);
    auto ballMaterial = Material(0.8f, 0.9f);
    float ballMass = 0.5f;

    //holes
    float holeRadius = 0.275f;
    std::vector<glm::vec2> holePositions;
    holePositions.emplace_back(-9.6f, -4.6f);
    holePositions.emplace_back(-9.6f, 4.6f);
    holePositions.emplace_back(0.0f, 4.8f);
    holePositions.emplace_back(9.6f, 4.6f);
    holePositions.emplace_back(9.6f, -4.6f);
    holePositions.emplace_back(0.0f, -4.8f);
    for (int i = 0; i < 6; ++i) {
        auto hole = Circle(holePositions[i], holeRadius, 0, staticMaterial, "Hole_" + std::to_string(i));
        hole.Color = ImColor(1.0f, 0.0f, 0.0f, 0.0f);
        hole.IsTrigger = true;
        auto holePtr = std::make_shared<Circle>(hole);
        simulation.SpawnParticle(holePtr);

        auto OnHoleTrigger = [this, ballMass, ballMaterial](const std::shared_ptr<Particle>& hole, const std::shared_ptr<Particle>& other) 
        {
            if(other->Tag == "ObjectBall" || other->Tag == "CueBall")
                simulation.DestroyParticle(other);

            if(other->Tag == "CueBall")
                SpawnCueBall(ballMass, ballMaterial);
        };

        holePtr->OnCollision.Subscribe("OnHoleTrigger" + std::to_string(i), OnHoleTrigger);
    }
    
    //table borders
    ImColor woodColor = ImColor(0.396f, 0.215f, 0.117f, 1.0f);
    auto left = AABB(glm::vec2(-100, -100), glm::vec2(-10, 100), staticMaterial, false, false, "Wall");
    left.Color = woodColor;
    left.DrawFilled = true;
    auto leftPointer = std::make_shared<AABB>(left);
    simulation.SpawnParticle(leftPointer);

    auto right = AABB(glm::vec2(10, -100), glm::vec2(100, 100), staticMaterial, false, false, "Wall");
    right.Color = woodColor;
    right.DrawFilled = true;
    auto rightPointer = std::make_shared<AABB>(right);
    simulation.SpawnParticle(rightPointer);

    auto top = AABB(glm::vec2(-100, 5), glm::vec2(100, 100), staticMaterial, false, false, "Wall");
    top.Color = woodColor;
    top.DrawFilled = true;
    auto topPointer = std::make_shared<AABB>(top);
    simulation.SpawnParticle(topPointer);

    auto bottom = AABB(glm::vec2(-100, -100), glm::vec2(100, -5), staticMaterial, false, false, "Wall");
    bottom.Color = woodColor;
    bottom.DrawFilled = true;
    auto bottomPointer = std::make_shared<AABB>(bottom);
    simulation.SpawnParticle(bottomPointer);
    
    //cue ball
    SpawnCueBall(ballMass, ballMaterial);

    //object balls colors and numbers
    std::vector<ImColor> colors;
    std::vector<int> ballNumbers;
    colors.emplace_back(0.988f, 0.866f, 0.035f, 1.0f); //1 (yellow)
    ballNumbers.push_back(1);
    colors.emplace_back(0.075f, 0.431f, 0.863f, 1.0f); //10 (blue)
    ballNumbers.push_back(10);
    colors.emplace_back(0.345f, 0.016f, 0.596f, 1.0f); //4 (purple)
    ballNumbers.push_back(4);
    colors.emplace_back(0.847f, 0.027f, 0.027f, 1.0f); //3 (red)
    ballNumbers.push_back(3);
    colors.emplace_back(0.100f, 0.100f, 0.100f, 1.0f); //8 (black)
    ballNumbers.push_back(8);
    colors.emplace_back(0.345f, 0.016f, 0.596f, 1.0f); //12 (purple)
    ballNumbers.push_back(12);
    colors.emplace_back(0.572f, 0.149f, 0.102f, 1.0f); //15 (maroon)
    ballNumbers.push_back(15);
    colors.emplace_back(0.243f, 0.556f, 0.066f, 1.0f); //6 (green)
    ballNumbers.push_back(6);
    colors.emplace_back(0.847f, 0.027f, 0.027f, 1.0f); //11 (red)
    ballNumbers.push_back(11);
    colors.emplace_back(0.945f, 0.502f, 0.063f, 1.0f); //5 (orange)
    ballNumbers.push_back(5);
    colors.emplace_back(0.075f, 0.431f, 0.863f, 1.0f); //2 (blue)
    ballNumbers.push_back(2);
    colors.emplace_back(0.945f, 0.502f, 0.063f, 1.0f); //13 (orange)
    ballNumbers.push_back(13);
    colors.emplace_back(0.988f, 0.866f, 0.035f, 1.0f); //9 (yellow)
    ballNumbers.push_back(9);
    colors.emplace_back(0.572f, 0.149f, 0.102f, 1.0f); //7 (maroon)
    ballNumbers.push_back(7);
    colors.emplace_back(0.243f, 0.556f, 0.066f, 1.0f); //14 (green)
    ballNumbers.push_back(14);

    //instantiate object balls
    auto positionOffset = glm::vec2(-2, 0);
    int index = 0;
    for (int row = 0; row < 5; ++row) {
        for (int ball = 0; ball < row + 1; ++ball) {

            auto objectBall = PoolObjectBall(colors[index], ballNumbers[index], glm::vec2(-0.87f * static_cast<float>(row), 0.5f * static_cast<float>(row) - static_cast<float>(ball)) + positionOffset, 0.5f, ballMass, ballMaterial, "ObjectBall");
            auto objectBallPtr = std::make_shared<PoolObjectBall>(objectBall);
            simulation.SpawnParticle(objectBallPtr);
            index++;
        }
    }
    
    //set initial camera view
    orthographicSize = 11.0f;
}

void Assignment8::OnDisable() {
    simulation.DestroyAllParticles();
}

bool MouseIsOverCircle(glm::vec2 mousePos, glm::vec2 circlePos, float circleRadius) {
    float mouseCircleDistance = glm::distance(mousePos, circlePos);
    bool mouseIsOverCircle = mouseCircleDistance < circleRadius;
    return mouseIsOverCircle;
}

void Assignment8::Update(float deltaTime) {

    //- Shoot cue ball -
    // get mouse position
    auto mousePosition = Input::GetMousePos();

    // check if mouse is clicked
    bool leftMouseButtonClick = Input::IsMouseClicked(0);
    bool leftMouseButtonDown = Input::IsMouseDown(0);
    // 0: left click, 1: right click

    bool clickBeganOverCircle = leftMouseButtonClick && MouseIsOverCircle(mousePosition, _cueBall->Position, _cueBall->Radius);

    if (clickBeganOverCircle) {
        _isAiming = true;
    }
    if (Input::IsMouseReleased(0)) {
        //add velocity when mouse is released
        if (_isAiming) {
            _cueBall->AddImpulse((mousePosition - _cueBall->Position) * -1.0f * 2.0f);
            _isAiming = false;
        }
    }

    //update Simulation
    simulation.Update(deltaTime);
}

void DrawTrajectory(std::shared_ptr<Circle> ball, float previewTime, int steps, glm::vec2 additionalImpulse = glm::vec2(0, 0))
{
    //respect mass
    additionalImpulse /= ball->Mass;
    
    //calculate trajectory
    for (int i = 0; i < steps; ++i)
    {
        float t = previewTime / steps * i;

        float tPowerTo2 = glm::pow(t, 2);
        glm::vec2 positionAtT = ball->Position + ((ball->Velocity + additionalImpulse) * t) + ((ball->TotalForce * tPowerTo2) / 2.0f);

        Draw::Circle(positionAtT, ball->Radius);
    }
}

void Assignment8::Draw() {
    //draw background
    Draw::SetColor(ImColor(0.266f, 0.376f, 0.157f, 1.0f));
    Draw::AABB(glm::vec2(-10, -5), glm::vec2(10, 5), true);

    //draw holes
    Draw::SetColor(ImColor(0.0f, 0.0f, 0.0f, 1.0f));
    Draw::Circle(glm::vec2(-9.6f, -4.6f), 0.8f, true);
    Draw::Circle(glm::vec2(-9.6f, 4.6f), 0.8f, true);
    Draw::Circle(glm::vec2(0.0f, 4.8f), 0.8f, true);
    Draw::Circle(glm::vec2(9.6f, 4.6f), 0.8f, true);
    Draw::Circle(glm::vec2(9.6f, -4.6f), 0.8f, true);
    Draw::Circle(glm::vec2(0.0f, -4.8f), 0.8f, true);
        
    //draw particles
    simulation.Draw();

    //draw trajectory
    if(_isAiming) {
        Draw::SetColor(ImColor(1.0f, 1.0f, 1.0f, 1.0f));
        DrawTrajectory(_cueBall, 0.5f, 8, (Input::GetMousePos() - _cueBall->Position) * -1.0f * 2.0f);
    }
}

void Assignment8::DrawGUI() {
    ImGui::Begin("Inspector");
    bool restart = ImGui::SmallButton("Restart");
    if(restart) {
        OnDisable();
        OnEnable();
    }
    ImGui::End();
}

void Assignment8::SpawnCueBall(float ballMass, const Material& ballMaterial) {
    auto cueBall = Circle(glm::vec2(5, 0), 0.5f, ballMass, ballMaterial, "CueBall");
    cueBall.DrawFilled = true;
    cueBall.Color = ImColor(0.8f, 0.8f, 0.8f, 1.0f);
    _cueBall = std::make_shared<Circle>(cueBall);
    simulation.SpawnParticle(_cueBall);
}
