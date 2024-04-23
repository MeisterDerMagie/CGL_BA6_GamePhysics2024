#include "Circle.h"

Circle::Circle(glm::vec2 position, float radius, float mass)
    : Particle(position, mass), Radius(radius), IsColliding(false) {
}


