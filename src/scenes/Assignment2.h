#pragma once

#include <vector>
#include "core/Simple2DScene.h"

class Assignment2 : public Simple2DScene {
public:
    Assignment2();
    ~Assignment2();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment2"; };

private:
    glm::vec2 circlePosition;
    float circleRadius;
    float circleMass;
    glm::vec2 velocity;
    glm::vec2 gravity;
    glm::vec2 mousePosition;
    glm::vec2 totalForce;
    bool drawArrow;
    bool drawAdvancedTrajectory;

    bool MouseIsOverCircle(glm::vec2 mousePos,
                           glm::vec2 circlePos,
                           float circleRadius);
    
    void AddForce(glm::vec2 force);
    void AddImpulse(glm::vec2 impulse);
    //void DrawTrajectoryAdvanced(float previewTime, int steps, glm::vec2 additionalImpulse);
    void DrawTrajectorySimple(float previewTime, int steps, glm::vec2 additionalImpulse);
};
