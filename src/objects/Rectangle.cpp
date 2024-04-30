#include "Rectangle.h"

Rectangle::Rectangle(glm::vec2 position,
                     float mass,
                     float coefficientOfRestitution,
                     glm::vec2 bottomLeft,
                     glm::vec2 topRight) : Particle(position, mass, coefficientOfRestitution, Particle::AABB), BottomLeft(bottomLeft), TopRight(TopRight) {}

Rectangle::~Rectangle() {}
