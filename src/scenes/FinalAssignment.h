#pragma once

#include <vector>
#include "core/Simple2DScene.h"
#include "objects/CollisionResolver_Inelastic.h"
#include "objects/Simulation.h"
#include "objects/Spring.h"

class FinalAssignment : public Simple2DScene {
public:
    explicit FinalAssignment()
        : simulation(Simulation(glm::vec2(0, -1200.0f), new CollisionResolver_Inelastic())),
          coefficient(200) {
    }

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "FinalAssignment"; }
    
    bool MouseIsOverAABB();
    void DrawSpring();

private:
    Simulation simulation;
    float coefficient;
    float damping = 0.999f;
    glm::vec2 mousePosition = glm::vec2(0, 0);
    glm::vec2 lastMousePosition = glm::vec2(0, 0);
};