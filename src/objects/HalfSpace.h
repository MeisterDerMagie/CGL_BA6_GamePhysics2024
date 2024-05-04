#pragma once
#include "Particle.h"

class HalfSpace : public Particle {
public:
    HalfSpace(glm::vec2 halfSpaceEndPoint, const Material& materialRef, const std::string& tag = "")
    : Particle(glm::vec2(0, 0), 0, materialRef, Particle::HalfSpace, tag),
      HalfSpaceEndPoint(halfSpaceEndPoint),
      HalfSpaceOrigin(0, 0) {
    }

    glm::vec2 HalfSpaceEndPoint;
    glm::vec2 HalfSpaceOrigin;

    void Draw() override;
};
