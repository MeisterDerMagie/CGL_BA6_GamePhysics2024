#pragma once
#include "AABB.h"
#include "Circle.h"
#include "HalfSpace.h"

class CollisionResolver {
public:

    //generic resolve
    static void Resolve(const std::shared_ptr<Particle>& a, const std::shared_ptr<Particle>& b);

private:
    //concrete implementations
    
    //HalfSpace - HalfSpace
    static void Resolve(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<HalfSpace>& b);

    //HalfSpace - Circle
    static void Resolve(const std::shared_ptr<HalfSpace>& halfSpace, const std::shared_ptr<Circle>& circle);
    static void Resolve(const std::shared_ptr<Circle>& a, const std::shared_ptr<HalfSpace>& b);
    
    //Circle - Circle
    static void Resolve(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b);

    //AABB - AABB
    static void Resolve(const std::shared_ptr<AABB>& a, const std::shared_ptr<AABB>& b);

    //AABB - HalfSpace
    static void Resolve(const std::shared_ptr<AABB>& a, const std::shared_ptr<HalfSpace>& b);
    static void Resolve(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<AABB>& b);

    //AABB - Circle
    static void Resolve(const std::shared_ptr<AABB>& aabb, const std::shared_ptr<Circle>& circle);
    static void Resolve(const std::shared_ptr<Circle>& circle, const std::shared_ptr<AABB>& aabb);
};
