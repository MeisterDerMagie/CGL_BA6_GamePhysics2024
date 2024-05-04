#pragma once

class Material {
public:
    Material(float damping_factor, float coefficient_of_restitution)
        : _dampingFactor(damping_factor),
          _coefficientOfRestitution(coefficient_of_restitution) {
    }

    const float& DampingFactor = _dampingFactor;
    const float& CoefficientOfRestitution = _coefficientOfRestitution;

    void SetDampingFactor(float dampingFactor);
    

private:
    float _dampingFactor;
    float _coefficientOfRestitution; //bounciness / elasticity
};
