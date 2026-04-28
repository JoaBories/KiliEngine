#include "CollisionUtils.h"

#include <filesystem>

Vector3 CollisionUtils::Obb::ObbOnObb(const Obb& pA, const Obb& pB) // project corners on each axis
{
    Vector3 axes[15];
    int axisCount = 0;

    axes[axisCount++] = pA.Axis1;
    axes[axisCount++] = pA.Axis2;
    axes[axisCount++] = pA.Axis3;
    axes[axisCount++] = pB.Axis1;
    axes[axisCount++] = pB.Axis2;
    axes[axisCount++] = pB.Axis3;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Vector3 crossAxis = Vector3::Cross(axes[i], axes[3 + j]);
            if (crossAxis.LengthSq() < 0.01f) continue;
            axes[axisCount++] = crossAxis;
        }
    }

    Vector3 cornersA[8], cornersB[8];
    pA.GetCorners(cornersA);
    pB.GetCorners(cornersB);

    float minOverlap = MathUtils::INFINITY_POS;
    Vector3 minOverlapAxis;
    
    for (int i = 0; i < axisCount; ++i)
    {
        const float overlap = OverlapOnAxis(cornersA, 8, cornersB, 8, axes[i]);

        if (overlap < 0.0f) return Vector3::zero;
        
        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            minOverlapAxis = axes[i];
        }
    }

    if (Vector3::Dot(pA.Center - pB.Center, minOverlapAxis) < 0.0f)
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

void CollisionUtils::Obb::GetCorners(Vector3 pOut[8]) const
{
    const Vector3 x = Axis1 * HalfSize.x;
    const Vector3 y = Axis2 * HalfSize.y;
    const Vector3 z = Axis3 * HalfSize.z;
    
    pOut[0] = Center + x + y + z;
    pOut[1] = Center + x + y - z;
    pOut[2] = Center + x - y + z;
    pOut[3] = Center + x - y - z;
    pOut[4] = Center - x + y + z;
    pOut[5] = Center - x + y - z;
    pOut[6] = Center - x - y + z;
    pOut[7] = Center - x - y - z;
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

float CollisionUtils::Line::LineOnAABB(const Line& pLine, const Obb& pObb, Vector3& pNormal)
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
    case 0: pNormal.x = hitSign ? 1.0f : -1.0f; break;
    case 1: pNormal.y = hitSign ? 1.0f : -1.0f; break;
    case 2: pNormal.z = hitSign ? 1.0f : -1.0f; break;
    default: break;
    }

    return tMin;
}

float CollisionUtils::OverlapOnAxis(const Vector3* pA, const size_t pACount, const Vector3* pB, const size_t pBCount, const Vector3& pAxis)
{
    float aMin = FLT_MAX, aMax = -FLT_MAX;
    float bMin = FLT_MAX, bMax = -FLT_MAX;

    for (size_t i = 0; i < pACount; i++)
    {
        const float p = Vector3::Dot(pA[i],pAxis);
        if (p < aMin) aMin = p;
        if (p > aMax) aMax = p;
    }

    for (size_t i = 0; i < pBCount; i++)
    {
        const float p = Vector3::Dot(pB[i],pAxis);
        if (p < bMin) bMin = p;
        if (p > bMax) bMax = p;
    }

    return MathUtils::Min(aMax, bMax) - MathUtils::Max(aMin, bMin);
}
