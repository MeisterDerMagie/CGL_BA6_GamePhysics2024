#pragma once
#include "AABB.h"
#include "Circle.h"
#include "HalfSpace.h"
#include "Particle.h"

class ICollisionResolver {
public:
    virtual ~ICollisionResolver() {}
    void Resolve(const std::shared_ptr<Particle>& a, const std::shared_ptr<Particle>& b);

private:
    //HalfSpace - HalfSpace
    void Resolve_HalfSpace_HalfSpace(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<HalfSpace>& b);

    //HalfSpace - Circle
    virtual void Resolve_HalfSpace_Circle(const std::shared_ptr<HalfSpace>& halfSpace, const std::shared_ptr<Circle>& circle) = 0;
    void Resolve_Circle_HalfSpace(const std::shared_ptr<Circle>& a, const std::shared_ptr<HalfSpace>& b);
    
    //Circle - Circle
    virtual void Resolve_Circle_Circle(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) = 0;

    //AABB - AABB
    void Resolve_AABB_AABB(const std::shared_ptr<AABB>& a, const std::shared_ptr<AABB>& b);

    //AABB - HalfSpace
    void Resolve_AABB_HalfSpace(const std::shared_ptr<AABB>& a, const std::shared_ptr<HalfSpace>& b);
    void Resolve_HalfSpace_AABB(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<AABB>& b);

    //AABB - Circle
    virtual void Resolve_AABB_Circle(const std::shared_ptr<AABB>& aabb, const std::shared_ptr<Circle>& circle) = 0;
    void Resolve_Circle_AABB(const std::shared_ptr<Circle>& circle, const std::shared_ptr<AABB>& aabb);
};
