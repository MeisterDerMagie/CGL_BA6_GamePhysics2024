#pragma once
#include "Circle.h"
#include "HalfSpace.h"

class CollisionResolver {
public:

    //unknown types
    static void Resolve(const std::shared_ptr<Particle>& a, const std::shared_ptr<Particle>& b);
    
    //HalfSpace - HalfSpace
    static void Resolve(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<HalfSpace>& b);

    //HalfSpace - Circle
    static void Resolve(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<Circle>& b);
    static void Resolve(const std::shared_ptr<Circle>& a, const std::shared_ptr<HalfSpace>& b);
    
    //Circle - Circle
    static void Resolve(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b);
};
