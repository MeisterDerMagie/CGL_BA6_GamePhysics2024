#pragma once

#include <vector>
#include "core/Simple2DScene.h"
#include "objects/CollisionResolver_Inelastic.h"
#include "objects/Simulation.h"

class Assignment8 : public Simple2DScene {
public:
    explicit Assignment8()
        : simulation(Simulation(glm::vec2(0, 0), new CollisionResolver_Inelastic())),
          _isAiming(false) {
    }

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment8"; }

private:
    Simulation simulation;
    bool _isAiming;
    std::shared_ptr<Circle> _cueBall;

    void SpawnCueBall(float ballMass, const Material& ballMaterial);
};
