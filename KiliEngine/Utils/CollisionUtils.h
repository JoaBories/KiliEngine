#pragma once

#include "Vector3.h"

namespace CollisionUtils
{

    struct Sphere;
    
    struct Collision
    {
        bool Collided = false;
        Vector3 OverlapDir = Vector3(0, 0, 0);
        float OverlapLength = 0;

        explicit operator bool() const { return Collided; }
        [[nodiscard]] Vector3 Overlap() const { return OverlapDir * OverlapLength; }

        [[nodiscard]] Collision Inverse() const { return {Collided, -OverlapDir, OverlapLength}; }
    };

    struct Obb
    {
        Vector3 Center = Vector3(0, 0, 0);
        Vector3 HalfSize = Vector3(0, 0, 0);
        Vector3 Axis1 = Vector3(0, 0, 1);
        Vector3 Axis2 = Vector3(0, 1, 0);
        Vector3 Axis3 = Vector3(1, 0, 0);

        [[nodiscard]] Vector3 ObbOnObb(const Vector3& pOther) const;
        [[nodiscard]] Vector3 GetClosestFromPoint(const Vector3& pPoint) const;

        [[nodiscard]] Sphere AsSphere() const;
    };

    struct Sphere
    {
        Vector3 Center = Vector3(0, 0, 0);
        float Radius = 0;

        [[nodiscard]] Vector3 SphereOnSphere(const Sphere& pOther) const; // return the overlap
        [[nodiscard]] Vector3 PointOnSphere(const Vector3& pPoint) const;
    };
    
};
