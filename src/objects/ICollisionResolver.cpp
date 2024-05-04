#include "ICollisionResolver.h"

#include <iostream>
#include <ostream>

void ICollisionResolver::Resolve(const std::shared_ptr<Particle>& a, const std::shared_ptr<Particle>& b) {
    if (a->Type == Particle::HalfSpace) {
        const std::shared_ptr<HalfSpace> a_HalfSpace = std::dynamic_pointer_cast<HalfSpace>(a);

        // HalfSpace - HalfSpace
        if (b->Type == Particle::HalfSpace) {
            const std::shared_ptr<HalfSpace> b_HalfSpace = std::dynamic_pointer_cast<HalfSpace>(b);
            Resolve_HalfSpace_HalfSpace(a_HalfSpace, b_HalfSpace);
            return;
        }

        // HalfSpace - Circle
        if (b->Type == Particle::Circle) {
            const std::shared_ptr<Circle> b_Circle = std::dynamic_pointer_cast<Circle>(b);
            Resolve_HalfSpace_Circle(a_HalfSpace, b_Circle);
            return;
        }

        /*// HalfSpace - Line
        if (b->Type == Particle::Line) {
            const std::shared_ptr<Line> b_Line = std::dynamic_pointer_cast<Line>(b);
            Resolve(a_HalfSpace, b_Line);
            return;
        }*/

        // HalfSpace - AABB
        if (b->Type == Particle::AABB) {
            const std::shared_ptr<AABB> b_AABB = std::dynamic_pointer_cast<AABB>(b);
            Resolve_HalfSpace_AABB(a_HalfSpace, b_AABB);
            return;
        }
    }

    if (a->Type == Particle::Circle) {
        const std::shared_ptr<Circle> a_Circle = std::dynamic_pointer_cast<Circle>(a);

        // Circle - Circle
        if (b->Type == Particle::Circle) {
            const std::shared_ptr<Circle> b_Circle = std::dynamic_pointer_cast<Circle>(b);
            Resolve_Circle_Circle(a_Circle, b_Circle);
            return;
        }

        // Circle - HalfSpace
        if (b->Type == Particle::HalfSpace) {
            const std::shared_ptr<HalfSpace> b_HalfSpace =
                std::dynamic_pointer_cast<HalfSpace>(b);
            Resolve_Circle_HalfSpace(a_Circle, b_HalfSpace);
            return;
        }

        /*
        // Circle - Line
        if (b->Type == Particle::Line) {
            const std::shared_ptr<Line> b_Line = std::dynamic_pointer_cast<Line>(b);
            Resolve(a_Circle, b_Line);
            return;
        }*/

        // Circle - AABB
        if (b->Type == Particle::AABB) {
            const std::shared_ptr<AABB> b_AABB = std::dynamic_pointer_cast<AABB>(b);
            Resolve_Circle_AABB(a_Circle, b_AABB);
            return;
        }
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
    }*/

    if (a->Type == Particle::AABB) {
        const std::shared_ptr<AABB> a_AABB = std::dynamic_pointer_cast<AABB>(a);

        // AABB - AABB
        if (b->Type == Particle::AABB) {
            const std::shared_ptr<AABB> b_AABB = std::dynamic_pointer_cast<AABB>(b);
            Resolve_AABB_AABB(a_AABB, b_AABB);
            return;
        }

        // AABB - HalfSpace
        if (b->Type == Particle::HalfSpace) {
            const std::shared_ptr<HalfSpace> b_HalfSpace = std::dynamic_pointer_cast<HalfSpace>(b);
            Resolve_AABB_HalfSpace(a_AABB, b_HalfSpace);
            return;
        }

        // AABB - Circle
        if (b->Type == Particle::Circle) {
            const std::shared_ptr<Circle> b_Circle = std::dynamic_pointer_cast<Circle>(b);
            Resolve_AABB_Circle(a_AABB, b_Circle);
            return;
        }

        // AABB - Line
        /*if (b->Type == Particle::Line) {
            const std::shared_ptr<Line> b_Line = std::dynamic_pointer_cast<Line>(b);
            Resolve(a_AABB, b_Line);
            return;
        }*/
    }

    std::cerr << "Unsupported collision: " << a->Type << " - " << b->Type << std::endl;
}

void ICollisionResolver::Resolve_HalfSpace_HalfSpace(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<HalfSpace>& b) {
    //colliding half spaces have no effect on each other
    return;
}

void ICollisionResolver::Resolve_Circle_HalfSpace(const std::shared_ptr<Circle>& a, const std::shared_ptr<HalfSpace>& b) {
    Resolve_HalfSpace_Circle(b, a);
}

void ICollisionResolver::Resolve_AABB_AABB(const std::shared_ptr<AABB>& a, const std::shared_ptr<AABB>& b) {
    //colliding AABBs have no effect on each other
    return;
}

void ICollisionResolver::Resolve_AABB_HalfSpace(const std::shared_ptr<AABB>& a, const std::shared_ptr<HalfSpace>& b) {
    //colliding AABBs and half spaces have no effect on each other
    return;
}

void ICollisionResolver::Resolve_HalfSpace_AABB(const std::shared_ptr<HalfSpace>& a, const std::shared_ptr<AABB>& b) {
    //colliding AABBs and half spaces have no effect on each other
    return;
}

void ICollisionResolver::Resolve_Circle_AABB( const std::shared_ptr<Circle>& circle, const std::shared_ptr<AABB>& aabb) {
    Resolve_AABB_Circle(aabb, circle);
}
