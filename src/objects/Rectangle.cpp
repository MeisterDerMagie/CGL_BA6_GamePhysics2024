#include "Rectangle.h"

Rectangle::Rectangle(glm::vec2 position,
                     float mass,
                     glm::vec2 bottomLeft,
                     glm::vec2 topRight) : Particle(position, mass), BottomLeft(bottomLeft), TopRight(TopRight) {}

Rectangle::~Rectangle() {}
