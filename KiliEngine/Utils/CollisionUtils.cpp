#include "CollisionUtils.h"

#include <filesystem>

Vector3 CollisionUtils::Obb::ObbOnObb(const Obb& pA, const Obb& pB) // project corners on each axis
{
    if (const Vector3 firstTest = Sphere::SphereOnSphere(pA.AsSphere(),pB.AsSphere()); firstTest == Vector3::zero) 
        return Vector3::zero;

    std::vector<Vector3> axes {
        pA.Axis1, pA.Axis2, pA.Axis3,
        pB.Axis1, pB.Axis2, pB.Axis3
    };

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Vector3 crossAxis = Vector3::Cross(axes[i], axes[3 + j]);
            if (crossAxis.LengthSq() < 0.01f) continue;
            axes.push_back(crossAxis);
        }
    }

    const std::vector<Vector3> a = pA.GetCorners();
    const std::vector<Vector3> b = pB.GetCorners();

    float minOverlap = MathUtils::INFINITY_POS;
    Vector3 minOverlapAxis;
    
    for (auto axe : axes)
    {
        const float overlap = OverlapOnAxis(a, b, axe);

        if (overlap < 0.0f) return Vector3::zero;
        
        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            minOverlapAxis = axe;
        }
    }
    
    Vector3 distance = pA.Center - pB.Center;

    if (Vector3::Dot(distance, minOverlapAxis) < 0.0f)
    {
        minOverlapAxis = -minOverlapAxis;
    }
    
    return minOverlapAxis * minOverlap;
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

std::vector<Vector3> CollisionUtils::Obb::GetCorners() const
{
    const Vector3 x = Axis1 * HalfSize.x;
    const Vector3 y = Axis2 * HalfSize.y;
    const Vector3 z = Axis3 * HalfSize.z;
        
    return {
        Center + x + y + z,
        Center + x + y - z,
        Center + x - y + z,
        Center + x - y - z,
        Center - x + y + z,
        Center - x + y - z,
        Center - x - y + z,
        Center - x - y - z,
    };
}

CollisionUtils::Sphere CollisionUtils::Obb::AsSphere() const
{
    return Sphere{Center, HalfSize.Length()};
}

Vector3 CollisionUtils::Sphere::SphereOnSphere(const Sphere& pA, const Sphere& pB)
{
    const Vector3 distance = pB.Center - pA.Center;
    const float radiusSum = pB.Radius + pA.Radius;

    if (distance.LengthSq() < radiusSum * radiusSum)
    {
        const float overlapLength = radiusSum - distance.Length();
        return distance.Normalized() * overlapLength;
    }

    return Vector3::zero;
}

Vector3 CollisionUtils::Sphere::PointOnSphere(const Sphere& pSphere,const Vector3& pPoint)
{
    const Vector3 distance = pPoint - pSphere.Center;

    if (distance.LengthSq() < pSphere.Radius * pSphere.Radius)
    {
        const float overlapLength = pSphere.Radius - distance.Length();
        return distance.Normalized() * overlapLength;
    }

    return Vector3::zero;
}

CollisionUtils::Line::Line(const Vector3& pStart, const Vector3& pEnd):
    Start(pStart), End(pEnd)
{
    Direction = (End - Start).Normalized();
    Length = (End - Start).Length();
}

float CollisionUtils::Line::LineOnSphere(const Line& pLine, const Sphere& pSphere)
{
    const Vector3 distance = pSphere.Center - pLine.Start;

    const float t = Vector3::Dot(distance, pLine.Direction); // project sphere center onto line
    const float squareDistance = distance.LengthSq() - t*t;
    const float squareRad = pSphere.Radius * pSphere.Radius;

    if (squareDistance > squareRad) return -1.0f;

    const float halfChord = sqrtf(squareRad - squareDistance);    // half-chord length
    const float tIn  = t - halfChord;

    const float result = tIn >= 0.0f ? tIn : t + halfChord;

    if (result <= 0.0f || result >= pLine.Length) return -1.0f;

    return result;
}

float CollisionUtils::Line::LineOnAABB(const Line& pLine, const Obb& pObb, Vector3& normal)
{
    float tMin = 0.0f;
    float tMax = pLine.Length;

    const std::vector<float> localOrigin {pLine.Start.x, pLine.Start.y, pLine.Start.z};
    const std::vector<float> localDir {pLine.Direction.x, pLine.Direction.y, pLine.Direction.z};
    const std::vector<float> halfExtents {pObb.HalfSize.x, pObb.HalfSize.y, pObb.HalfSize.z};

    char hitAxis = 0;
    bool hitSign = false;
    
    // --- slab test on each axis ---
    for (char i = 0; i < 3; ++i)
    {
        const float origin = localOrigin[i];
        const float dir    = localDir[i];
        const float half   = halfExtents[i];

        if (fabsf(dir) < 1e-8f)
        {
            if (origin < -half || origin > half) return -1.0f;
        }
        else
        {
            float invD = 1.0f / dir;
            float t0   = (-half - origin) * invD;   // entry
            float t1   = ( half - origin) * invD;   // exit

            bool sign = false;
            if (t0 > t1)
            {
                std::swap(t0, t1);
                sign = true;
            }
            
            if (t0 > tMin)
            {
                tMin = t0;
                hitAxis = i;
                hitSign = sign;
            }
            tMax = std::min(tMax, t1);

            if (tMin > tMax) return -1.0f;           // slabs don't overlap
        }
    }

    switch (hitAxis)
    {
    case 0: normal.x = hitSign ? 1.0f : -1.0f; break;
    case 1: normal.y = hitSign ? 1.0f : -1.0f; break;
    case 2: normal.z = hitSign ? 1.0f : -1.0f; break;
    default: break;
    }

    return tMin;
}

float CollisionUtils::OverlapOnAxis(const std::vector<Vector3>& pA, const std::vector<Vector3>& pB, const Vector3& pAxis)
{
    float aMin = FLT_MAX, aMax = -FLT_MAX;
    float bMin = FLT_MAX, bMax = -FLT_MAX;

    for (const auto& point : pA)
    {
        float projection = Vector3::Dot(point,pAxis);
        aMin = MathUtils::Min(projection, aMin);
        aMax = MathUtils::Max(projection, aMax);
    }

    for (const auto& point : pB)
    {
        float projection = Vector3::Dot(point,pAxis);
        bMin = MathUtils::Min(projection, bMin);
        bMax = MathUtils::Max(projection, bMax);
    }

    return MathUtils::Min(aMax, bMax) - MathUtils::Max(aMin, bMin);
}
