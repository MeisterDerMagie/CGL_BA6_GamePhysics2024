#pragma once
#include <glm/vec2.hpp>
#include "objects/Particle.h"

class Circle : public Particle {
public:
    Circle(glm::vec2 position, float radius, float mass);

    float Radius;

    bool IsColliding;
};
