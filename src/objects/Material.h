#pragma once

class Material {
public:
    Material(float damping_factor, float coefficient_of_restitution)
        : DampingFactor(damping_factor),
          CoefficientOfRestitution(coefficient_of_restitution) {
    }

    float DampingFactor;
    float CoefficientOfRestitution; //bounciness / elasticity
};
