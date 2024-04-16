#pragma once

#include <vector>
#include "core/Simple2DScene.h"

class Assignment3 : public Simple2DScene {
public:
    Assignment3();
    ~Assignment3();
    
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment3"; };

private:
    glm::vec2 circlePosition;
    float circleRadius;
    float circleMass;
    glm::vec2 velocity;
    glm::vec2 gravity;
    glm::vec2 mousePosition;
    glm::vec2 totalForce;
    glm::vec2 halfSpaceOrigin;
    glm::vec2 halfSpaceEndPoint;
    glm::vec2 halfSpaceNormal;
    bool isCollidingWithHalfSpace;
    int currentSelectionIndex;

    void AddForce(glm::vec2 force);
};
