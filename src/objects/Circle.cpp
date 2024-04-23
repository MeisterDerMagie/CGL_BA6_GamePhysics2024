#include "Circle.h"

Circle::Circle(glm::vec2 position, float radius, float mass)
    : Position(position), Radius(radius), Mass(mass), Velocity(0, 0),
      TotalForce(0, 0), IsColliding(false) {
}

void Circle::ResetTotalForce() {
    TotalForce = glm::vec2(0,0);
}

void Circle::AddForce(glm::vec2 force)
{
    TotalForce += force * Mass;
}

void Circle::AddImpulse(glm::vec2 impulse) {
    //impulses modify velocity directly instead of adding a force
    Velocity += impulse / Mass;
}
