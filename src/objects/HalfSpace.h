#pragma once
#include "Particle.h"

class HalfSpace : public Particle {
public:
    HalfSpace(glm::vec2 halfSpaceEndPoint, const std::string& tag = "");

    glm::vec2 HalfSpaceEndPoint;
    glm::vec2 HalfSpaceOrigin;

    void Draw() override;
};
