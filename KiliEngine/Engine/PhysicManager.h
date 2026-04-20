#pragma once

#include "Components/SphereCollider.h"
#include "Components/BoxCollider.h"
#include "Components/RigidBody.h"

class Camera;

class PhysicManager
{
private:
    static std::vector<BoxCollider*> mBoxColliders;
    static std::vector<SphereCollider*> mSphereColliders;

    static Collision Collide(BoxCollider* pBox1, BoxCollider* pBox2);
    static Collision Collide(BoxCollider* pBox, SphereCollider* pSphere);
    static Collision Collide(SphereCollider* pSphere1, SphereCollider* pSphere2);

    static Hit Collide(const Line& pLine, SphereCollider* pSphere);
    static Hit Collide(const Line& pLine, BoxCollider* pBox);
    
    static Obb BoxToObb(BoxCollider* pBox);
    static Sphere SphereToSphere(SphereCollider* pSphere);
    
public:
    static void Update();

    static void AddBoxCollider(BoxCollider* pCollider);
    static void RemoveBoxCollider(BoxCollider* pCollider);

    static void AddSphereCollider(SphereCollider* pCollider);
    static void RemoveSphereCollider(SphereCollider* pCollider);

    static Hit Linetrace(const Vector3& pStart, const Vector3& pEnd, const GameActor* pSelf, float pDebugTime = 0.0f);

#ifdef _DEBUG

struct LineTraceWrap
{
    Line Trace;
    float TimeRemaining;
    bool Collided;

    bool operator==(const LineTraceWrap& pOther) const {
        return Trace == pOther.Trace && MathUtils::NearlyEqual(TimeRemaining, pOther.TimeRemaining) && Collided == pOther.Collided;
    }
};

private :
    static std::vector<LineTraceWrap> mLineTraceWraps;

public :
    static void DrawDebug(const Camera* pCam);
    
#endif
    
};
