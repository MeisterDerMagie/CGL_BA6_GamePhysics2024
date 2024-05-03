#pragma once

#include <vector>
#include "core/Simple2DScene.h"
#include "objects/AABB.h"
#include "objects/Circle.h"
#include "objects/Simulation.h"

class Assignment6 : public Simple2DScene {
public:
    Assignment6();
    ~Assignment6();
    
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment6"; }

    void SpawnNewBall();
    void DestroyBall();
    std::shared_ptr<Circle> Ball;
    std::shared_ptr<AABB> Paddle;

private:
    Simulation simulation;
    float playableAreaWidth;
    float paddleWidth;
    int aliveBricksCount = -1;
    bool gameIsOver = false;
};
