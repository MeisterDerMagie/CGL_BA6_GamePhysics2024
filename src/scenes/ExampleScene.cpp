#include "ExampleScene.h"

#include "imgui.h"
#include <core/Draw.h>

void ExampleScene::OnEnable() {}

void ExampleScene::OnDisable() {}

void ExampleScene::Update(float deltaTime)
{
    Draw::Circle(glm::vec2(0, 1), 0.5f);
}

void ExampleScene::Draw() {}

void ExampleScene::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}
