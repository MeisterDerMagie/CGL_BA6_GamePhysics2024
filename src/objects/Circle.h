#pragma once
#include <glm/vec2.hpp>
#include "objects/Particle.h"

class Circle : public Particle {
public:
    Circle(glm::vec2 position, float radius, float mass, const Material& materialRef, const std::string& tag = "");

    float Radius;

    void Draw() override;
};
