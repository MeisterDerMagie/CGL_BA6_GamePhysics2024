#pragma once

#include <vector>

#include "Circle.h"
#include "core/Simple2DScene.h"

class Assignment4 : public Simple2DScene {
public:
    Assignment4();
    ~Assignment4();
    
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment4"; };

private:
    std::vector<Circle> circles;
    glm::vec2 gravity;
};
