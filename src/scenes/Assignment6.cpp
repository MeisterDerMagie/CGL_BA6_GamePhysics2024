#include "Assignment6.h"

#include "imgui.h"
#include "core/Draw.h"
#include "objects/AABB.h"
#include "objects/Circle.h"
#include "objects/Simulation.h"

Assignment6::Assignment6()
    : simulation(Simulation(glm::vec2(0, -9.81f))),
      playableAreaWidth(14),
      paddleWidth(2),
      respawnCooldown(0) {
}

void Assignment6::SpawnNewBall() {
    Circle circle = Circle(glm::vec2(0, 4), 0.5f, 0, 0.5f, "Ball");
    Ball = std::make_shared<Circle>(circle);
    simulation.SpawnParticle(Ball);

    //set respawn cooldown
    respawnCooldown = 1.0f;
    
    //accelerate ball on each paddle hit
    auto OnPaddleHit = [this](const std::shared_ptr<Particle>& ball, const std::shared_ptr<Particle>& other) 
    {
        if(other->Tag == "Paddle") {
            ball->AddImpulse(glm::vec2(0.0f, 0.25f));
        }
    };
    Ball->OnCollision.Subscribe("OnPaddleHit", OnPaddleHit);
}

void Assignment6::DestroyBall() {
    simulation.DestroyParticle(Ball);
}

void Assignment6::OnEnable() {

    //create simulation
    simulation = Simulation(glm::vec2(0, -9.81f));

    //reset state
    gameIsOver = false;    
    
    //create ball
    SpawnNewBall();
    
    //create paddle
    AABB paddle = AABB(glm::vec2(-paddleWidth / 2.0f, 0), glm::vec2(paddleWidth / 2.0f, 0.4f), false, true, "Paddle");
    Paddle = std::make_shared<AABB>(paddle);
    simulation.SpawnParticle(Paddle);

    //create left wall
    AABB leftWall = AABB(glm::vec2(-100.0f, -100.0), glm::vec2(-playableAreaWidth / 2.0f, 100.0f), false, true, "LeftWall");
    std::shared_ptr<AABB> leftWallPointer = std::make_shared<AABB>(leftWall);
    simulation.SpawnParticle(leftWallPointer);

    //create right wall
    AABB rightWall = AABB(glm::vec2(playableAreaWidth / 2.0f, -100.0), glm::vec2(100.0f, 100.0f), false, true, "RightWall");
    std::shared_ptr<AABB> rightWallPointer = std::make_shared<AABB>(rightWall);
    simulation.SpawnParticle(rightWallPointer);

    //create death zone
    AABB deathZone = AABB(glm::vec2(-playableAreaWidth / 2.0f, -100.0), glm::vec2(playableAreaWidth / 2.0f, -2.0f), false, true, "DeathZone");
    std::shared_ptr<AABB> deathZonePointer = std::make_shared<AABB>(deathZone);
    auto OnDeathZoneCollision = [this](const std::shared_ptr<Particle>& deathZone, const std::shared_ptr<Particle>& other) 
    {
        if(other->Tag == "Ball") {
            DestroyBall();
            SpawnNewBall();
        }
    };
    deathZonePointer->OnCollision.Subscribe("OnDeathZoneCollision", OnDeathZoneCollision);
    deathZonePointer->Color = Colors::red;
    simulation.SpawnParticle(deathZonePointer);

    //create bricks
    const int brickRows = 4;
    const int bricksPerRow = 10;
    const float bricksDistance = 0.25f;
    const float bricksHeight = 0.5f;
    const float lowestBricksPosition = 6.9f;

    float topWallYPos = 0.0f;
    aliveBricksCount = brickRows * bricksPerRow;

    for (int i = 0; i < brickRows; ++i) {
        const float brickWidth = (playableAreaWidth - (static_cast<float>(bricksPerRow) + 1.0f) * bricksDistance) / static_cast<float>(bricksPerRow);
        for (int j = 0; j < bricksPerRow; ++j) {
            //create brick
            std::string brickTag = "Brick_" + (i + j);
            auto lowerLeft = glm::vec2(-playableAreaWidth / 2.0f + (static_cast<float>((j+1)) * bricksDistance + static_cast<float>(j) * brickWidth), lowestBricksPosition + static_cast<float>(i) * bricksHeight + static_cast<float>(i) * bricksDistance);
            auto upperRight = glm::vec2(lowerLeft.x + brickWidth, lowerLeft.y + bricksHeight);
            topWallYPos = upperRight.y + bricksDistance;
            AABB brick = AABB(lowerLeft, upperRight, false, false, brickTag);
            std::shared_ptr<AABB> brickPointer = std::make_shared<AABB>(brick);
            auto OnBrickCollision = [this](const std::shared_ptr<Particle>& brick, const std::shared_ptr<Particle>& other) 
            {
                //if the ball hits a brick:
                if(other->Tag == "Ball") {
                    //destroy the brick ...
                    simulation.DestroyParticle(brick);

                    //... decrease the alive bricks count ...
                    aliveBricksCount -= 1;

                    //... check for game over
                    if(aliveBricksCount <= 0) {
                        gameIsOver = true;
                        DestroyBall();
                    }
                }
            };
            brickPointer->OnCollision.Subscribe("OnBrickCollision", OnBrickCollision);
            brickPointer->Color = Colors::blue;
            simulation.SpawnParticle(brickPointer);
        }
    }

    //create top wall
    AABB topWall = AABB(glm::vec2(-playableAreaWidth / 2.0f, topWallYPos), glm::vec2(playableAreaWidth / 2.0f, 100.0f), false, false, "TopWall");
    std::shared_ptr<AABB> topWallPointer = std::make_shared<AABB>(topWall);
    simulation.SpawnParticle(topWallPointer);

    //set initial camera view
    cameraCenter = glm::vec2(0, 3.2f);
    orthographicSize = 13.0f;
}

void Assignment6::OnDisable() {

    //How to properly delete the simulation?
    //simulation.~Simulation();
}

void Assignment6::Update(float deltaTime) {
    // get mouse position
    glm::vec2 mousePosition = Input::GetMousePos();

    // make ball non-static when respawn cooldown ran off
    bool isOnCooldown = respawnCooldown > 0.0f;
    respawnCooldown -= deltaTime;
    if(isOnCooldown && respawnCooldown <= 0.0f) {
        Ball->SetMass(1.0f);
        
        //initial velocity
        Ball->Velocity = glm::vec2(0, -14.0f);
    }

    //set paddle position
    float clampedXPos = glm::clamp(mousePosition.x, -playableAreaWidth / 2.0f + paddleWidth / 2.0f, playableAreaWidth / 2.0f - paddleWidth / 2.0f);
    Paddle->SetPosition(glm::vec2(clampedXPos, Paddle->Position.y));

    //update simulation
    simulation.Update(deltaTime);
}

void Assignment6::Draw() {
    simulation.Draw();

    if(gameIsOver)
        Draw::Text(glm::vec2(-0.8f, 4.5f), "You win!");
}

void Assignment6::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}
