#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "Event.hpp"
#include "Material.h"
#include "Particle.h"
#include "core/Colors.h"

class Spring {
public:
    virtual ~Spring() = default;

    Spring(float coefficient, std::shared_ptr<Particle> aRef, std::shared_ptr<Particle> bRef) :
        Coefficient(coefficient), A(std::move(aRef)), B(std::move(bRef)) {}

    
    float Coefficient;
    std::shared_ptr<Particle> A;
    std::shared_ptr<Particle> B;
};
