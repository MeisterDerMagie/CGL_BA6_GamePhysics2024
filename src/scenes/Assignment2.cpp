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
      acceleration(0, -9.81f),
      totalForce(0, 0) {
}

Assignment2::~Assignment2() = default;

void Assignment2::OnEnable() {
}

void Assignment2::OnDisable() {
}

void Assignment2::Update(float deltaTime) {
    totalForce = glm::vec2(0, 0);

    // Semi-implicite Euler integration
    velocity = velocity + acceleration * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime;

    // get mouse position
    mousePosition = Input::GetMousePos();

    // check if mouse is clicked
    bool leftMouseButtonClick = Input::IsMouseClicked(0);
    bool leftMouseButtonDown = Input::IsMouseDown(0); // 0: left click, 1: right click
    //drawArrow = leftMouseButtonDown;

    bool clickBeganOverCircle =
        leftMouseButtonClick && Assignment2::MouseIsOverCircle(
            mousePosition, circlePosition, circleRadius);

    if (clickBeganOverCircle) {
        drawArrow = true;
    }
    if (Input::IsMouseReleased(0)){
        drawArrow = false;
    }
}

bool Assignment2::MouseIsOverCircle(glm::vec2 mousePos,
                                    glm::vec2 circlePos,
                                    float circleRadius)
{
    float mouseCircleDistance = glm::distance(mousePos, circlePos);
    bool mouseIsOverCircle = mouseCircleDistance < circleRadius;
    return mouseIsOverCircle;
}

glm::vec2 Assignment2::TrajectoryPoint(float time,
                                       glm::vec2 currentPos,
                                       glm::vec2 currentVelocity,
                                       glm::vec2 currentAcceleration)
{
    return glm::vec2(0, 0);
    //return currentPos + (velocity * time) + ((acceleration * time) / )
}

void Assignment2::AddImpulse(glm::vec2 impulse)
{
    velocity += impulse / circleMass;
}

void Assignment2::Draw()
{
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));

    if (drawArrow)
        Draw::Arrow(circlePosition, mousePosition);
}

void Assignment2::DrawGUI()
{
    ImGui::Begin("Inspector");
    ImGui::End();
}
