#include "PoolObjectBall.h"

#include "Circle.h"

#include "core/Colors.h"
#include "core/Draw.h"

PoolObjectBall::PoolObjectBall(ImColor color, int number, glm::vec2 position, float radius, float mass, const Material& materialRef, const std::string& tag)
    : Circle(position, radius, mass, materialRef, tag), _number(number) {
    Color = color;
    isStriped = number > 8;
}

void PoolObjectBall::Draw() {
    Draw::Circle(Position, Radius, true);

    Draw::SetColor(ImColor(0.9f, 0.9f, 0.9f, 1.0f));
    Draw::Circle(Position, 0.3f, true);
    
    if(isStriped)
        Draw::AABB(glm::vec2(Position.x - 0.45f, Position.y - 0.15f), glm::vec2(Position.x + 0.45f, Position.y + 0.15f), true);
    
    Draw::SetColor(ImColor(0.0f, 0.0f, 0.0f, 1.0f));
    //if(_number == 8)
    //    Draw::SetColor(ImColor(1.0f, 1.0f, 1.0f, 1.0f));
    Draw::Text(Position + glm::vec2(-0.175f, 0.25f), std::to_string(_number).c_str());
}
