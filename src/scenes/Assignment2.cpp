#include "Assignment2.h"
#include "Assignment2.h"
#include "Assignment2.h"

#include "core/Draw.h"
#include "core/Colors.h"
#include "imgui.h"
#include <iostream>

Assignment2::Assignment2()
    : circlePosition(0, 2),
      circleRadius(1),
      circleMass(1),
      velocity(0, 0),
      gravity(0, -9.81f),
      mousePosition(),
      totalForce(0, 0),
      drawArrow(false),
      drawAdvancedTrajectory(false) {
}

Assignment2::~Assignment2() = default;

void Assignment2::OnEnable() {
}

void Assignment2::OnDisable() {
}

void Assignment2::Update(float deltaTime) {
    //reset total force
    totalForce = glm::vec2(0, 0);

    //gravity
    AddForce(gravity);

    // get mouse position
    mousePosition = Input::GetMousePos();

    // check if mouse is clicked
    bool leftMouseButtonClick = Input::IsMouseClicked(0);
    bool leftMouseButtonDown = Input::IsMouseDown(0);
    // 0: left click, 1: right click
    //drawArrow = leftMouseButtonDown;

    bool clickBeganOverCircle =
        leftMouseButtonClick && Assignment2::MouseIsOverCircle(
            mousePosition, circlePosition, circleRadius);

    if (clickBeganOverCircle) {
        drawArrow = true;
    }
    if (Input::IsMouseReleased(0)) {
        //add velocity when mouse is released
        if (drawArrow) {
            AddImpulse(mousePosition - circlePosition);
            drawArrow = false;
        }
    }
    
    // Semi-implicite Euler integration
    velocity = velocity + totalForce * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime;

    //check collision with line (if y-distance is smaller than radius)
    bool collidedWithLine = circlePosition.y < circleRadius;
    if (collidedWithLine) {
        //set above line
        circlePosition.y = circleRadius;

        //invert velocity on y axis
        velocity.y *= -1;
    }
}

bool Assignment2::MouseIsOverCircle(glm::vec2 mousePos,
                                    glm::vec2 circlePos,
                                    float circleRadius) {
    float mouseCircleDistance = glm::distance(mousePos, circlePos);
    bool mouseIsOverCircle = mouseCircleDistance < circleRadius;
    return mouseIsOverCircle;
}

void Assignment2::AddForce(glm::vec2 force)
{
    totalForce += force * circleMass;
}

void Assignment2::AddImpulse(glm::vec2 impulse) {
    //impulses modify velocity directly instead of adding a force
    velocity += impulse / circleMass;
}

void Assignment2::DrawTrajectorySimple(float previewTime, int steps, glm::vec2 additionalImpulse = glm::vec2(0, 0))
{
    //respect mass
    additionalImpulse /= circleMass;
    
    //calculate trajectory
    for (int i = 0; i < steps; ++i)
    {
        float t = previewTime / steps * i;

        float tPowerTo2 = glm::pow(t, 2);
        glm::vec2 positionAtT = circlePosition + ((velocity + additionalImpulse) * t) + ((totalForce * tPowerTo2) / 2.0f);

        if (positionAtT.y > 0.0f)
        {
            Draw::Circle(positionAtT, circleRadius);
        }
    }
}

//doesn't work, there is somewhere an error
/*void Assignment2::DrawTrajectoryAdvanced(float previewTime, int steps, glm::vec2 additionalImpulse = glm::vec2(0, 0))
{
    glm::vec2 trajectoryVelocity = velocity + additionalImpulse;
    glm::vec2 trajectoryCirclePosition = circlePosition;
    float t = 0.0f;
    
    for (int i = 0; i < steps; ++i)
    {
        t += previewTime / steps;

        float tPowerTo2 = glm::pow(t, 2);
        trajectoryCirclePosition = trajectoryCirclePosition + (trajectoryVelocity * t) + ((totalForce * tPowerTo2) / 2.0f);

        if (trajectoryCirclePosition.y < 0.0f)
        {
            trajectoryCirclePosition.y = 0.0f;
            trajectoryVelocity.y *= -1.0f;
        }
        
        Draw::Circle(trajectoryCirclePosition, circleRadius);
    }
}*/

void Assignment2::Draw() {
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));

    if (drawArrow) {
        Draw::Arrow(circlePosition, mousePosition);
        // if(drawAdvancedTrajectory)
            //DrawTrajectoryAdvanced(2.0f, 10, (mousePosition - circlePosition));
        //else
            DrawTrajectorySimple(2.0f, 10, (mousePosition - circlePosition));
    }
}

void Assignment2::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::DragFloat("Circle Mass", &circleMass);
    if (ImGui::SmallButton("Reset"))
    {
        velocity = glm::vec2(0,0);
        circlePosition = glm::vec2(0,0);
    }
    //ImGui::Checkbox("Draw advanced trajectory", &drawAdvancedTrajectory);
    ImGui::End();
}
