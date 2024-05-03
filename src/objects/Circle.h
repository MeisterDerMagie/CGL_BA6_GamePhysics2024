﻿#pragma once
#include <glm/vec2.hpp>
#include "objects/Particle.h"

class Circle : public Particle {
public:
    Circle(glm::vec2 position, float radius, float mass, float coefficientOfRestitution, const std::string& tag = "");

    float Radius;

    bool IsColliding;

    void Draw() override;
};
