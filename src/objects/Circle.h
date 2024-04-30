#pragma once
#include <glm/vec2.hpp>
#include "objects/Particle.h"

class Circle : public Particle {
public:
    Circle::Circle(glm::vec2 position, float radius, float mass, float coefficientOfRestitution);

    float Radius;

    bool IsColliding;

    void Draw() override;
};
