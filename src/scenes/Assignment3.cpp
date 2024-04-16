#include "Assignment3.h"

#include "imgui.h"
#include "core/Colors.h"
#include "core/Draw.h"

Assignment3::Assignment3()
    : circlePosition(0, 2),
      circleRadius(1),
      circleMass(0.5f),
      velocity(0, 0),
      gravity(0, -9.81f),
      mousePosition(),
      totalForce(0, 0),
      halfSpaceOrigin(0, 0),
      halfSpaceEndPoint(2, 2),
      halfSpaceNormal(),
      isCollidingWithHalfSpace(false),
      currentSelectionIndex(0)
//technicaly the half space doesn't have an end point, it's infinite. But we somehow need to define the line.
{
}

void Assignment3::OnEnable() {}

void Assignment3::OnDisable() {}

void Assignment3::Update(float deltaTime)
{
    //reset total force
    totalForce = glm::vec2(0, 0);

    //gravity
    AddForce(gravity);

    //normalize line
    glm::vec2 lineNormal = normalize(halfSpaceEndPoint);

    //rotate normal of line by 90 degrees to get the normal of the half space
    halfSpaceNormal = glm::vec2(lineNormal.y * -1.0f, lineNormal.x);

    //calculate projected distance
    float projectedDistance = glm::dot(halfSpaceNormal, circlePosition);

    //if projected distance is smaller than the radius, we're colliding with the half space
    isCollidingWithHalfSpace = projectedDistance < circleRadius;

    //if we're colliding, move the cirlce out of the half space
    if(isCollidingWithHalfSpace)
    {
        float collisionDepth = circleRadius - projectedDistance;
        glm::vec2 moveDirectionAndDistance = halfSpaceNormal * collisionDepth;
        circlePosition += moveDirectionAndDistance;

        //then reflect the velocity to create bounce (we could also just use glm::reflect())
        //glm::vec2 reflectedVelocity = velocity - 2.0f * (velocity * halfSpaceNormal) * halfSpaceNormal;
        glm::vec2 reflectedVelocity = glm::reflect(velocity, halfSpaceNormal);
        velocity = reflectedVelocity;
    }
    
    // Semi-implicite Euler integration
    velocity = velocity + totalForce * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime;
}

void Assignment3::Draw()
{
    //draw circle
    if(isCollidingWithHalfSpace)
        Draw::SetColor(Colors::red);
    Draw::Circle(circlePosition, circleRadius);

    if(currentSelectionIndex == 2)
        Draw::PositionHandle(circlePosition);
    
    //draw half space
    Draw::SetColor(Colors::white);
    if(currentSelectionIndex == 1)
        Draw::PositionHandle(halfSpaceEndPoint);
    Draw::Line(halfSpaceOrigin, halfSpaceEndPoint);

    //draw half space normal
    Draw::SetColor(Colors::blue);
    Draw::Arrow(halfSpaceOrigin, halfSpaceNormal);
    Draw::SetColor(Colors::white);
}

void Assignment3::DrawGUI() {
    ImGui::Begin("Inspector");

    //selection for position handle
    const char* selectItems[3] = { "None", "Line", "Circle" };
    ImGui::ListBox("Select", &currentSelectionIndex, selectItems, 3);

    //reset circle button
    if(ImGui::SmallButton("Reset Circle")) {
        circlePosition = glm::vec2(0, 2);
        velocity = glm::vec2(0,0);
    }
    ImGui::End();
}

void Assignment3::AddForce(glm::vec2 force) {
    totalForce += force * circleMass;
}
