#include "CollisionResolver_Inelastic.h"

#include <glm/geometric.hpp>

void CollisionResolver_Inelastic::Resolve_HalfSpace_Circle(const std::shared_ptr<HalfSpace>& halfSpace, const std::shared_ptr<Circle>& circle) {
    
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

        //if one particle is trigger, only call OnCollision and do nothing more
        if(halfSpace->IsTrigger || circle->IsTrigger) {
            halfSpace->OnCollision.Invoke(halfSpace, circle);
            circle->OnCollision.Invoke(circle, halfSpace);
            return;
        }
        
        float intersectionDepth = circle->Radius - projectedDistance;
        glm::vec2 moveDirectionAndDistance = halfSpaceNormal * intersectionDepth;
        circle->Position += moveDirectionAndDistance;
        
        //calculate inelastic collision resolution
        float circleImpulseMagnitude = (-(1.0f + circle->material->CoefficientOfRestitution) * glm::dot((circle->Velocity - 0.0f), halfSpaceNormal)) / (circle->InverseMass + 0);
        auto impulse = halfSpaceNormal * circleImpulseMagnitude;
        circle->AddImpulse(impulse);

        //finally call collision event
        halfSpace->OnCollision.Invoke(halfSpace, circle);
        circle->OnCollision.Invoke(circle, halfSpace);
    }
}

void CollisionResolver_Inelastic::Resolve_Circle_Circle(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
        
    //distance between circles
    const float distanceBetweenCircles = glm::distance(a->Position, b->Position);

    //collision normal
    auto collisionNormal = normalize(glm::vec2(a->Position - b->Position));

    //intersection depth
    const float intersectionDepth =
        (a->Radius + b->Radius) - distanceBetweenCircles;

    //if no collision is happening, do nothing
    if (intersectionDepth <= 0.0f)
        return;

    //if one particle is trigger, only call OnCollision and do nothing more
    if(a->IsTrigger || b->IsTrigger) {
        a->OnCollision.Invoke(a, b);
        b->OnCollision.Invoke(b, a);
        return;
    }

    //otherwise, resolve the collision
    //calculate how far each circle needs to be moved. depends on the mass
    const float massCalc = 1.0f / (a->Mass + b->Mass);
    float moveDistanceA = intersectionDepth * (a->Mass * massCalc);
    float moveDistanceB = intersectionDepth * (b->Mass * massCalc);

    //set positions so that the circles don't overlap anymore
    a->Position += collisionNormal * moveDistanceA;
    b->Position -= collisionNormal * moveDistanceB;

    //calculate inelastic collision resolution
    float circleAImpulseMagnitude = (-(1.0f + a->material->CoefficientOfRestitution) * glm::dot((a->Velocity - b->Velocity), collisionNormal)) / (a->InverseMass + b->InverseMass);
    float circleBImpulseMagnitude = (-(1.0f + b->material->CoefficientOfRestitution) * glm::dot((b->Velocity - a->Velocity), collisionNormal)) / (b->InverseMass + a->InverseMass);
    auto impulseA = collisionNormal * circleAImpulseMagnitude;
    auto impulseB = collisionNormal * circleBImpulseMagnitude;
    a->AddImpulse(impulseA);
    b->AddImpulse(impulseB);

    //finally call collision event
    a->OnCollision.Invoke(a, b);
    b->OnCollision.Invoke(b, a);
}

void CollisionResolver_Inelastic::Resolve_AABB_Circle(const std::shared_ptr<AABB>& aabb, const std::shared_ptr<Circle>& circle) {
    
    glm::vec2 closestPointOnAABBToCircle = glm::clamp(circle->Position, aabb->LowerLeft, aabb->UpperRight);
    
    float intersectionDepth = -distance(closestPointOnAABBToCircle, circle->Position) + circle->Radius;

    //if no collision is happening, do nothing
    if(intersectionDepth <= 0.0f)
        return;

    //if one particle is trigger, only call OnCollision and do nothing more
    if(aabb->IsTrigger || circle->IsTrigger) {
        aabb->OnCollision.Invoke(aabb, circle);
        circle->OnCollision.Invoke(circle, aabb);
        return;
    }
    
    //otherwise, resolve the collision
    glm::vec2 collisionNormal;
    if(aabb->UseCenterForCollisionNormal)
        collisionNormal = normalize((circle->Position - closestPointOnAABBToCircle));
    else
        collisionNormal = normalize((circle->Position - aabb->Position));
    
    circle->Position += collisionNormal * intersectionDepth;

    //calculate inelastic collision resolution
    float circleImpulseMagnitude = (-(1.0f + circle->material->CoefficientOfRestitution) * glm::dot((circle->Velocity - 0.0f), collisionNormal)) / (circle->InverseMass + 0);
    auto impulse = collisionNormal * circleImpulseMagnitude;
    circle->AddImpulse(impulse);

    //finally call collision event
    aabb->OnCollision.Invoke(aabb, circle);
    circle->OnCollision.Invoke(circle, aabb);
}