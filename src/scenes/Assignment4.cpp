#include "Assignment4.h"

#include "imgui.h"
#include "objects/Circle.h"
#include "core/Colors.h"
#include "core/Draw.h"

Assignment4::Assignment4() : gravity(0, -9.81f)
{}

Assignment4::~Assignment4() = default;

void Assignment4::OnEnable() {
    auto circle1 = Circle(glm::vec2(1,1), 1, 1);
    circles.push_back(circle1);
    
    auto circle2 = Circle(glm::vec2(3.0f,3.0f), 2, 2);
    circles.push_back(circle2);
}

void Assignment4::OnDisable() {}

void Assignment4::Update(float deltaTime) {

    //simulate physics for all circles
    for (Circle circle : circles) {
        //reset total force
        circle.TotalForce = glm::vec2(0, 0);

        //gravity
        circle.AddForce(gravity);

        // Semi-implicite Euler integration
        circle.Velocity = circle.Velocity + circle.TotalForce * deltaTime;
        circle.Position = circle.Position + circle.Velocity * deltaTime;
    }

    for (Circle circle : circles) {
        //check collision with other circles
        circle.IsColliding = false;

        for(Circle other : circles) {
            Circle* circleAddress = &circle;
            Circle* otherAddress = &other;

            //don't collide with yourself
            if(circleAddress == otherAddress)
                continue;
            
            float distanceBetweenCircles = glm::distance(circle.Position, other.Position);
            if(distanceBetweenCircles < circle.Radius || distanceBetweenCircles < other.Radius) {
                //collision is happening
                circle.IsColliding = true;
                other.IsColliding = true;
            }
        }
    }
}

void Assignment4::Draw() {
    //draw all circles
    for (auto circle : circles) {

        if(circle.IsColliding) {
            Draw::SetColor(Colors::red);
        } else {
            Draw::SetColor(Colors::white);
        }

        
        Draw::Circle(circle.Position, circle.Radius);
    }
}

void Assignment4::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}