#include "CollisionUtils.h"

Vector3 CollisionUtils::Obb::ObbOnObb(const Vector3& pOther) const
{
    return Vector3();
}

Vector3 CollisionUtils::Obb::GetClosestFromPoint(const Vector3& pPoint) const
{
    const Vector3 distance = pPoint - Center;
    Vector3 closest = Center;

    const float dot = Vector3::Dot(distance, Axis1);
    closest += Axis1 * MathUtils::Clamp(dot, -HalfSize.x, HalfSize.x);
    
    closest += Axis2 * MathUtils::Clamp(Vector3::Dot(distance, Axis2), -HalfSize.y, HalfSize.y);
    closest += Axis3 * MathUtils::Clamp(Vector3::Dot(distance, Axis3), -HalfSize.z, HalfSize.z);
    return closest;
}

CollisionUtils::Sphere CollisionUtils::Obb::AsSphere() const
{
    return Sphere{Center, HalfSize.Length()};
}

Vector3 CollisionUtils::Sphere::SphereOnSphere(const Sphere& pOther) const
{
    const Vector3 distance = pOther.Center - Center;
    const float radiusSum = pOther.Radius + Radius;

    if (distance.LengthSq() < radiusSum * radiusSum)
    {
        const float overlapLength = distance.Length() - radiusSum;
        return distance.Normalized() * overlapLength;
    }

    return Vector3::zero;
}

Vector3 CollisionUtils::Sphere::PointOnSphere(const Vector3& pPoint) const
{
    const Vector3 distance = pPoint - Center;

    if (distance.LengthSq() < Radius * Radius * Radius)
    {
        const float overlapLength = distance.Length() - Radius;
        return distance.Normalized() * overlapLength;
    }

    return Vector3::zero;
}
