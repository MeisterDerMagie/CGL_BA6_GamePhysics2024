#pragma once

#include <vector>
#include "core/Simple2DScene.h"

class ExampleScene2 : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Example-2"; };
};
