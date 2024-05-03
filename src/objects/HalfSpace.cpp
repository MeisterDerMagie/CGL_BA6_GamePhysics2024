#include "HalfSpace.h"

#include "core/Colors.h"
#include "core/Draw.h"

HalfSpace::HalfSpace(glm::vec2 halfSpaceEndPoint, const std::string& tag)
    : Particle(glm::vec2(0, 0), 0, 0.5f, Particle::HalfSpace, tag),
      HalfSpaceEndPoint(halfSpaceEndPoint),
      HalfSpaceOrigin(0, 0) {
}

void HalfSpace::Draw() {
    
    //draw an "infinitly" long line
    glm::vec2 hs = HalfSpaceEndPoint - HalfSpaceOrigin;
    glm::vec2 hsOrigin = hs * -10000.0f;
    glm::vec2 hsEnd = hs * 10000.0f;

    Draw::Line(hsOrigin, hsEnd);
    
    //Draw::Line(HalfSpaceOrigin, HalfSpaceEndPoint);
}
