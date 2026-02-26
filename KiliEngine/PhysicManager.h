#pragma once

#include "SphereCollider.h"
#include "BoxCollider.h"
#include "RigidBody.h"

class PhysicManager
{
private:
    static std::vector<BoxCollider*> mBoxColliders;
    static std::vector<SphereCollider*> mSphereColliders;

    static Collision Collide(BoxCollider* pBox1, BoxCollider* pBox2);
    static Collision Collide(BoxCollider* pBox, SphereCollider* pSphere);
    static Collision Collide(SphereCollider* pSphere1, SphereCollider* pSphere2);
    
public:
    static void Update();

    static void AddBoxCollider(BoxCollider* pCollider);
    static void RemoveBoxCollider(BoxCollider* pCollider);

    static void AddSphereCollider(SphereCollider* pCollider);
    static void RemoveSphereCollider(SphereCollider* pCollider);
    
};
