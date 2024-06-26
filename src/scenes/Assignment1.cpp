#include "Assignment1.h"

#include "core/Draw.h"
#include "core/Colors.h"
#include "imgui.h"
#include <iostream>


Assignment1::Assignment1() : circlePosition(0, 2), circleRadius(1), velocity(0, 0), acceleration(0, -9.81f){}

Assignment1::~Assignment1() = default;

void Assignment1::OnEnable() {}

void Assignment1::OnDisable() {}

void Assignment1::Update(float deltaTime)
{
    //Semi-implicite Euler integration
    velocity = velocity + acceleration * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime;

    //check collision with line (if y-distance is smaller than radius)
    bool collidedWithLine = circlePosition.y < circleRadius;
    if (collidedWithLine)
    {
        //set above line
        circlePosition.y = circleRadius;

        //invert velocity on y axis
        velocity.y *= -1;
    }
}

void Assignment1::Draw()
{
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
}

void Assignment1::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    if (ImGui::Button("Click me")) {
        //std::count << "test" << std : endl;
    }
    ImGui::End();
}