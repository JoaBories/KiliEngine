#pragma once

#include "Vector3.h"

namespace CollisionUtils
{    
    struct Collision
    {
        bool Collided = false;
        Vector3 OverlapDir = Vector3(0, 0, 0);
        float OverlapLength = 0;

        explicit operator bool() const { return Collided; }
        [[nodiscard]] Vector3 Overlap() const { return OverlapDir * OverlapLength; }
    };

    struct OBB
    {
        Vector3 Center = Vector3(0, 0, 0);
        Vector3 HalfSize = Vector3(0, 0, 0);
        Vector3 Axis1 = Vector3(0, 0, 1);
        Vector3 Axis2 = Vector3(0, 1, 0);
        Vector3 Axis3 = Vector3(1, 0, 0);

        Vector3 GetClosestPoint(const Vector3& pOint);
    };
};
