#pragma once

#include <vector>
#include "core/Simple2DScene.h"
#include "objects/CollisionResolver_Inelastic.h"
#include "objects/Simulation.h"

class Assignment7 : public Simple2DScene {
public:
    Assignment7()
        : simulation(Simulation(glm::vec2(0,0), new CollisionResolver_Inelastic())) {
    }
    ~Assignment7();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment7"; }

private:
    Simulation simulation;
};
