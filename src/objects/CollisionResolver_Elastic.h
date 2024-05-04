#pragma once
#include "AABB.h"
#include "Circle.h"
#include "HalfSpace.h"
#include "ICollisionResolver.h"

class CollisionResolver_Elastic : public ICollisionResolver {
public:

private:
    //concrete implementations

    //HalfSpace - Circle
    void Resolve_HalfSpace_Circle(const std::shared_ptr<HalfSpace>& halfSpace, const std::shared_ptr<Circle>& circle) override;
    
    //Circle - Circle
    void Resolve_Circle_Circle(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) override;

    //AABB - Circle
    void Resolve_AABB_Circle(const std::shared_ptr<AABB>& aabb, const std::shared_ptr<Circle>& circle) override;
};