#include "CollisionResolver_Elastic.h"
#include "HalfSpace.h"
#include "Circle.h"
#include "AABB.h"

#include <iostream>
#include <glm/detail/func_geometric.inl>


void CollisionResolver_Elastic::Resolve_HalfSpace_Circle(const std::shared_ptr<HalfSpace>& halfSpace, const std::shared_ptr<Circle>& circle) {
    //normalize line
    glm::vec2 lineNormal = glm::normalize(halfSpace->HalfSpaceEndPoint);

    //rotate normal of line by 90 degrees to get the normal of the half space
    auto halfSpaceNormal = glm::vec2(lineNormal.y * -1.0f, lineNormal.x);

    //calculate projected distance
    float projectedDistance = glm::dot(halfSpaceNormal, circle->Position);

    //if projected distance is smaller than the radius, we're colliding with the half space
    bool isCollidingWithHalfSpace = projectedDistance < circle->Radius;

    //if we're colliding, move the circle out of the half space
    if (isCollidingWithHalfSpace) {        
        float intersectionDepth = circle->Radius - projectedDistance;
        glm::vec2 moveDirectionAndDistance = halfSpaceNormal * intersectionDepth;
        circle->Position += moveDirectionAndDistance;

        //then reflect the velocity to create bounce        
        glm::vec2 reflectedVelocity =
            glm::reflect(circle->Velocity, halfSpaceNormal);
        circle->Velocity = reflectedVelocity;

        //finally call collision event
        halfSpace->OnCollision.Invoke(halfSpace, circle);
        circle->OnCollision.Invoke(circle, halfSpace);
    }
}

void CollisionResolver_Elastic::Resolve_Circle_Circle(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
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
    a->OnCollision.Invoke(a, b);
    b->OnCollision.Invoke(b, a);
}

void CollisionResolver_Elastic::Resolve_AABB_Circle(const std::shared_ptr<AABB>& aabb, const std::shared_ptr<Circle>& circle) {
    glm::vec2 closestPointOnAABBToCircle = glm::clamp(circle->Position, aabb->LowerLeft, aabb->UpperRight);
    
    float intersectionDepth = -distance(closestPointOnAABBToCircle, circle->Position) + circle->Radius;

    //if no collision is happening, do nothing
    if(intersectionDepth <= 0.0f)
        return;

    //otherwise, resolve the collision
    glm::vec2 collisionNormal;
    if(aabb->UseCenterForCollisionNormal)
        collisionNormal = normalize((circle->Position - closestPointOnAABBToCircle));
    else
        collisionNormal = normalize((circle->Position - aabb->Position));
    
    circle->Position += collisionNormal * intersectionDepth;

    //reflect velocity
    circle->Velocity = glm::reflect(circle->Velocity, collisionNormal);

    //finally call collision event
    aabb->OnCollision.Invoke(aabb, circle);
    circle->OnCollision.Invoke(circle, aabb);
}