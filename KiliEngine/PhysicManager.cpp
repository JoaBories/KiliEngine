#include "PhysicManager.h"

std::vector<BoxCollider*> PhysicManager::mBoxColliders = {};
std::vector<SphereCollider*> PhysicManager::mSphereColliders = {};

Collision PhysicManager::Collide(BoxCollider* pBox1, BoxCollider* pBox2)
{
    Collision result;
    
    const Obb obb1 = BoxToObb(pBox1);
    const Obb obb2 = BoxToObb(pBox2);
    
    const Vector3 overlap = Obb::ObbOnObb(obb1,obb2);
    if (overlap != Vector3::zero)
    {
        result.Collided = true;
        result.OverlapLength = overlap.Length();
        result.OverlapDir = overlap / result.OverlapLength;
    }
    
    return result;
}

Collision PhysicManager::Collide(BoxCollider* pBox, SphereCollider* pSphere)
{
    Collision result;
    
    const Obb obb = BoxToObb(pBox);
    const Sphere sp = SphereToSphere(pSphere);

    const Vector3 overlap = Sphere::PointOnSphere(sp, obb.GetClosestFromPoint(sp.Center));
    if (overlap != Vector3::zero)
    {
        result.Collided = true;
        result.OverlapLength = overlap.Length();
        result.OverlapDir = overlap / result.OverlapLength;
    }

    return result;
}

Collision PhysicManager::Collide(SphereCollider* pSphere1, SphereCollider* pSphere2)
{
    Collision result;

    const Sphere sp1 = SphereToSphere(pSphere1);
    const Sphere sp2 = SphereToSphere(pSphere2);
    
    const Vector3 overlap = -Sphere::SphereOnSphere(sp1,sp2);
    if (overlap != Vector3::zero)
    {
        result.Collided = true;
        result.OverlapLength = overlap.Length();
        result.OverlapDir = overlap / result.OverlapLength;
    }
    
    return result;
}

Obb PhysicManager::BoxToObb(BoxCollider* pBox)
{
    const Transform boxTransform = pBox->GetWorldTransform().GetTransform();
    
    return {
        boxTransform.GetPosition(), 
        pBox->GetHalfSize() * boxTransform.GetScale(), 
        boxTransform.GetForwardVector(), 
        boxTransform.GetRightVector(), 
        boxTransform.GetUpVector()
    };
}

Sphere PhysicManager::SphereToSphere(SphereCollider* pSphere)
{
    return {pSphere->GetWorldTransform().GetPosition(), pSphere->GetRadius()};
}

void PhysicManager::Update()
{
    for (size_t b1 = 0; b1 < mBoxColliders.size(); b1++)
    {
        for (size_t b2 = b1 + 1; b2 < mBoxColliders.size(); b2++)
        {
            if (const Collision coll = Collide(mBoxColliders[b1], mBoxColliders[b2]))
            {
                mBoxColliders[b1]->OnCollide(coll, mBoxColliders[b2]);
                mBoxColliders[b2]->OnCollide(coll.Inverse(), mBoxColliders[b1]);
            }
        }

        for (size_t s1 = 0; s1 < mSphereColliders.size(); s1++)
        {
            if (const Collision coll = Collide(mBoxColliders[b1], mSphereColliders[s1]))
            {
                mBoxColliders[b1]->OnCollide(coll, mSphereColliders[s1]);
                mSphereColliders[s1]->OnCollide(coll.Inverse(), mBoxColliders[b1]);
            }
        }
    }

    for (size_t s1 = 0; s1 < mSphereColliders.size(); s1++)
    {
        for (size_t s2 = s1+1; s2 < mSphereColliders.size(); s2++)
        {
            if (const Collision coll = Collide(mSphereColliders[s1], mSphereColliders[s2]))
            {
                mSphereColliders[s1]->OnCollide(coll, mSphereColliders[s2]);
                mSphereColliders[s2]->OnCollide(coll.Inverse(), mSphereColliders[s1]);
            }
        }
    }
}

#pragma region AddRemove

void PhysicManager::AddBoxCollider(BoxCollider* pCollider)
{
    if (std::find(mBoxColliders.begin(), mBoxColliders.end(), pCollider) == mBoxColliders.end())
    {
        mBoxColliders.push_back(pCollider);
    }
}

void PhysicManager::RemoveBoxCollider(BoxCollider* pCollider)
{
    const auto it = std::find(mBoxColliders.begin(), mBoxColliders.end(), pCollider);
    if (it != mBoxColliders.end())
    {
        mBoxColliders.erase(it);
    }
}

void PhysicManager::AddSphereCollider(SphereCollider* pCollider)
{
    if (std::find(mSphereColliders.begin(), mSphereColliders.end(), pCollider) == mSphereColliders.end())
    {
        mSphereColliders.push_back(pCollider);
    }
}

void PhysicManager::RemoveSphereCollider(SphereCollider* pCollider)
{
    const auto it = std::find(mSphereColliders.begin(), mSphereColliders.end(), pCollider);
    if (it != mSphereColliders.end())
    {
        mSphereColliders.erase(it);
    }
}

#pragma endregion