#pragma once

#include <vector>
#include "core/Simple2DScene.h"
#include "objects/Simulation.h"

class Assignment5 : public Simple2DScene {
public:
    Assignment5();
    ~Assignment5();
    
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment5"; };

private:
    Simulation simulation;
};
