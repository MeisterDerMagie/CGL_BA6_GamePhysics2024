#include "Circle.h"

#include "core/Colors.h"
#include "core/Draw.h"

Circle::Circle(glm::vec2 position, float radius, float mass, const Material& materialRef, const std::string& tag)
    : Particle(position, mass, materialRef, Particle::Circle, tag),
    Radius(radius) {
}

void Circle::Draw() {
    Draw::Circle(Position, Radius, DrawFilled);
}