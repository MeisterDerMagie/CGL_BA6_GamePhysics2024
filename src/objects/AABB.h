#pragma once
#include <glm/common.hpp>

#include "Particle.h"

class AABB : public Particle {
public:
    AABB(glm::vec2 lowerLeft, glm::vec2 upperRight, const Material& materialRef, bool drawDiagonal = true, bool useCenterForCollisionNormal = false, const std::string& tag = "")
        : Particle(glm::mix(lowerLeft, upperRight, 0.5f), 0, materialRef, Particle::AABB, tag),
          LowerLeft(lowerLeft),
          UpperRight(upperRight),
          DrawDiagonal(drawDiagonal),
          UseCenterForCollisionNormal(useCenterForCollisionNormal) {
    }

    glm::vec2 LowerLeft, UpperRight;
    bool DrawDiagonal;
    bool UseCenterForCollisionNormal;

    void SetPosition(glm::vec2 newPosition);
    
    void Draw() override;
};