#pragma once

#include "Vector3.h"
#include <vector>

class ColliderComponent;
class GameActor;

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

        [[nodiscard]] static Vector3 ObbOnObb(const Obb& pA, const Obb& pB);
        
        [[nodiscard]] Vector3 GetClosestFromPoint(const Vector3& pPoint) const;
        [[nodiscard]] std::vector<Vector3> GetCorners() const;

        [[nodiscard]] Sphere AsSphere() const;
    };

    struct Sphere
    {
        Vector3 Center = Vector3(0, 0, 0);
        float Radius = 0;

        [[nodiscard]] static Vector3 SphereOnSphere(const Sphere& pA, const Sphere& pB); // return the overlap
        [[nodiscard]] static Vector3 PointOnSphere(const Sphere& pSphere,const Vector3& pPoint);
    };

    struct Line
    {
        Vector3 Start = Vector3(0, 0, 0);
        Vector3 End = Vector3(0, 0, 1);
        Vector3 Direction = Vector3(0, 0, 1);
        float Length = 0;

        Line(const Vector3& pStart, const Vector3& pEnd);

        [[nodiscard]] static float LineOnSphere(const Line& pLine, const Sphere& pSphere); // return length on the Line
        [[nodiscard]] static float LineOnAABB(const Line& pLine, const Obb& pObb);

        bool operator==(const Line& pLine) const { return Start == pLine.Start && End == pLine.End; }
    };
    
    struct Hit
    {
        bool Collided = false;
        Vector3 Point = Vector3(0, 0, 0);
        Vector3 LineDirection = Vector3(0, 0, 0);
        Line Linetrace = Line(Vector3(0, 0, 0), Vector3(0, 0, 0));
        float Distance = 0.0f;
        GameActor* OtherActor = nullptr;
        ColliderComponent* OtherCollider = nullptr;

        explicit operator bool() const { return Collided; }
    };
    
    float OverlapOnAxis(const std::vector<Vector3>& pA, const std::vector<Vector3>& pB, const Vector3& pAxis);
    
};
