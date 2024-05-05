#pragma once
#include <glm/vec2.hpp>

#include "Circle.h"
#include "objects/Particle.h"

class PoolObjectBall : public Circle {
public:
    PoolObjectBall(ImColor color, int number, glm::vec2 position, float radius, float mass, const Material& materialRef, const std::string& tag = "");

    void Draw() override;

private:
    int _number;
    bool isStriped;
};
