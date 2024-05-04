#pragma once
#include "ICollisionResolver.h"

class CollisionResolver_Inelastic : public ICollisionResolver {

private:
    void Resolve_HalfSpace_Circle(const std::shared_ptr<HalfSpace>& halfSpace, const std::shared_ptr<Circle>& circle) override;
    void Resolve_Circle_Circle(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) override;
    void Resolve_AABB_Circle(const std::shared_ptr<AABB>& aabb, const std::shared_ptr<Circle>& circle) override;
    
};
