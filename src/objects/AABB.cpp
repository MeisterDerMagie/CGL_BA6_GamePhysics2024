#include "AABB.h"

#include "core/Draw.h"

void AABB::SetPosition(glm::vec2 newPosition) {
    auto posDifference = newPosition - Position;
    Position = newPosition;
    LowerLeft += posDifference;
    UpperRight += posDifference;
}

void AABB::Draw() {
    //draw box
    Draw::AABB(LowerLeft, UpperRight);

    //draw diagonal
    if(DrawDiagonal)
        Draw::Line(LowerLeft, UpperRight);
}
