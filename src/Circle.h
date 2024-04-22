#pragma once
#include <glm/vec2.hpp>

class Circle {
public:
    Circle(glm::vec2 position, float radius, float mass);
    void ResetTotalForce();

    glm::vec2 Position;
    float Radius;
    float Mass;

    glm::vec2 Velocity;
    glm::vec2 TotalForce;

    bool IsColliding;

    void AddForce(glm::vec2 force);
    void AddImpulse(glm::vec2 impulse);
};
