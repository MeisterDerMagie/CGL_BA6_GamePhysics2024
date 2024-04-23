#pragma once
#include <glm/vec2.hpp>
#include "objects/Particle.h"

class Rectangle : public Particle {
public:
    Rectangle(glm::vec2 position,
              float mass,
              glm::vec2 bottomLeft,
              glm::vec2 topRight);
    ~Rectangle();

    glm::vec2 BottomLeft;
    glm::vec2 TopRight;
};
