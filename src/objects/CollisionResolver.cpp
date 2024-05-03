#include "CollisionResolver.h"
#include "HalfSpace.h"
#include "Circle.h"

#include <iostream>
#include <glm/detail/func_geometric.inl>


void CollisionResolver::Resolve(const std::shared_ptr<Particle>& a, const std::shared_ptr<Particle>& b) {
    
    if (a->Type == Particle::HalfSpace) {
        const std::shared_ptr<HalfSpace> a_HalfSpace = std::dynamic_pointer_cast<HalfSpace>(a);

        // HalfSpace - HalfSpace
        if (b->Type == Particle::HalfSpace) {
            const std::shared_ptr<HalfSpace> b_HalfSpace = std::dynamic_pointer_cast<HalfSpace>(b);
            Resolve(a_HalfSpace, b_HalfSpace);
            return;
        }

        // HalfSpace - Circle
        if (b->Type == Particle::Circle) {
            const std::shared_ptr<Circle> b_Circle = std::dynamic_pointer_cast<Circle>(b);
            Resolve(a_HalfSpace, b_Circle);
            return;
        }

        /*// HalfSpace - Line
        if (b->Type == Particle::Line) {
            const std::shared_ptr<Line> b_Line = std::dynamic_pointer_cast<Line>(b);
            Resolve(a_HalfSpace, b_Line);
            return;
        }

        // HalfSpace - AABB
        if (b->Type == Particle::AABB) {
            const std::shared_ptr<AABB> b_AABB = std::dynamic_pointer_cast<AABB>(b);
            Resolve(a_HalfSpace, b_AABB);
            return;
        }*/
    }

    if (a->Type == Particle::Circle) {
        const std::shared_ptr<Circle> a_Circle = std::dynamic_pointer_cast<Circle>(a);

        // Circle - Circle
        if (b->Type == Particle::Circle) {
            const std::shared_ptr<Circle> b_Circle = std::dynamic_pointer_cast<Circle>(b);
            Resolve(a_Circle, b_Circle);
            return;
        }

        // Circle - HalfSpace
        if (b->Type == Particle::HalfSpace) {
            const std::shared_ptr<HalfSpace> b_HalfSpace =
                std::dynamic_pointer_cast<HalfSpace>(b);
            Resolve(a_Circle, b_HalfSpace);
            return;
        }

        /*
        // Circle - Line
        if (b->Type == Particle::Line) {
            const std::shared_ptr<Line> b_Line = std::dynamic_pointer_cast<Line>(b);
            Resolve(a_Circle, b_Line);
            return;
        }

        // Circle - AABB
        if (b->Type == Particle::AABB) {
            const std::shared_ptr<AABB> b_AABB = std::dynamic_pointer_cast<AABB>(b);
            Resolve(a_Circle, b_AABB);
            return;
        }
        */
    }

    /*if (a->Type == Particle::Line) {
        const std::shared_ptr<Line> a_Line = std::dynamic_pointer_cast<Line>(a);

        // Line - Line
        if (b->Type == Particle::Line) {
            const std::shared_ptr<Line> b_Line = std::dynamic_pointer_cast<Line>(b);
            Resolve(a_Line, b_Line);
            return;
        }

        // Line - HalfSpace
        if (b->Type == Particle::HalfSpace) {
            const std::shared_ptr<HalfSpace> b_HalfSpace = std::dynamic_pointer_cast<HalfSpace>(b);
            Resolve(a_Line, b_HalfSpace);
            return;
        }

        // Line - Circle
        if (b->Type == Particle::Circle) {
            const std::shared_ptr<Circle> b_Circle = std::dynamic_pointer_cast<Circle>(b);
            Resolve(a_Line, b_Circle);
            return;
        }

        // Line - AABB
        if (b->Type == Particle::AABB) {
            const std::shared_ptr<AABB> b_AABB = std::dynamic_pointer_cast<AABB>(b);
            Resolve(a_Line, b_AABB);
            return;
        }
    }

    if (a->Type == Particle::AABB) {
        const std::shared_ptr<AABB> a_AABB = std::dynamic_pointer_cast<AABB>(a);

        // AABB - AABB
        if (b->Type == Particle::AABB) {
            const std::shared_ptr<AABB> b_AABB = std::dynamic_pointer_cast<AABB>(b);
            Resolve(a_AABB, b_AABB);
            return;
        }

        // AABB - HalfSpace
        if (b->Type == Particle::HalfSpace) {
            const std::shared_ptr<HalfSpace> b_HalfSpace = std::dynamic_pointer_cast<HalfSpace>(b);
            Resolve(a_AABB, b_HalfSpace);
            return;
        }

        // AABB - Circle
        if (b->Type == Particle::Circle) {
            const std::shared_ptr<Circle> b_Circle = std::dynamic_pointer_cast<Circle>(b);
            Resolve(a_AABB, b_Circle);
            return;
        }

        // AABB - Line
        if (b->Type == Particle::Line) {
            const std::shared_ptr<Line> b_Line = std::dynamic_pointer_cast<Line>(b);
            Resolve(a_AABB, b_Line);
            return;
        }
    }*/

    std::cerr << "Unsupported collision: " << a->Type << " - " << b->Type;
}

void CollisionResolver::Resolve(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<HalfSpace>& b) {
    //colliding half spaces have no effect on eachother
    return;
}


void CollisionResolver::Resolve(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<Circle>& b) {
    //normalize line
    glm::vec2 lineNormal = glm::normalize(a->HalfSpaceEndPoint);

    //rotate normal of line by 90 degrees to get the normal of the half space
    auto halfSpaceNormal = glm::vec2(lineNormal.y * -1.0f, lineNormal.x);

    //calculate projected distance
    float projectedDistance = glm::dot(halfSpaceNormal, b->Position);

    //if projected distance is smaller than the radius, we're colliding with the half space
    bool isCollidingWithHalfSpace = projectedDistance < b->Radius;

    //if we're colliding, move the circle out of the half space
    if (isCollidingWithHalfSpace) {        
        float intersectionDepth = b->Radius - projectedDistance;
        glm::vec2 moveDirectionAndDistance = halfSpaceNormal * intersectionDepth;
        b->Position += moveDirectionAndDistance;

        //then reflect the velocity to create bounce        
        glm::vec2 reflectedVelocity =
            glm::reflect(b->Velocity, halfSpaceNormal);
        b->Velocity = reflectedVelocity;

        //finally call collision event
        a->OnCollision(a, b);
        b->OnCollision(b, a);
    }
}

void CollisionResolver::Resolve(const std::shared_ptr<Circle>& a, const std::shared_ptr<HalfSpace>& b) {
    Resolve(b, a);
}

void CollisionResolver::Resolve(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
    //if distance between circles
    const float distanceBetweenCircles = glm::distance(a->Position, b->Position);

    //collision normal
    auto collisionNormal = normalize(glm::vec2(a->Position - b->Position));

    //intersection depth
    const float intersectionDepth =
        (a->Radius + b->Radius) - distanceBetweenCircles;

    //if no collision is happening, do nothing
    if (intersectionDepth <= 0.0f)
        return;

    //otherwise, resolve the collision
    //calculate how far each circle needs to be moved. depends on the mass
    const float massCalc = 1.0f / (a->Mass + b->Mass);
    float moveDistanceA = intersectionDepth * (a->Mass * massCalc);
    float moveDistanceB = intersectionDepth * (b->Mass * massCalc);

    //set positions so that the circles don't overlap anymore
    a->Position += collisionNormal * moveDistanceA;
    b->Position -= collisionNormal * moveDistanceB;

    //mirror velocity along the collision normal
    a->Velocity = glm::reflect(a->Velocity, collisionNormal);
    b->Velocity = glm::reflect(b->Velocity, -collisionNormal);

    //finally call collision event
    //finally call collision event
    a->OnCollision(a, b);
    b->OnCollision(b, a);
}
