#include "Circle.h"

#include "core/Colors.h"
#include "core/Draw.h"

Circle::Circle(glm::vec2 position, float radius, float mass, float coefficientOfRestitution, const std::string& tag)
    : Particle(position, mass, coefficientOfRestitution, Particle::Circle, tag),
    Radius(radius),
    IsColliding(false) {
}

void Circle::Draw() {
    //Draw::SetColor(Color);
    Draw::Circle(Position, Radius);
}