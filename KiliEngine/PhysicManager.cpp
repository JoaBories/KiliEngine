#include "PhysicManager.h"

std::vector<BoxCollider*> PhysicManager::mBoxColliders = {};
std::vector<SphereCollider*> PhysicManager::mSphereColliders = {};

Collision PhysicManager::Collide(BoxCollider* pBox1, BoxCollider* pBox2)
{
    return {};
}

Collision PhysicManager::Collide(BoxCollider* pBox, SphereCollider* pSphere)
{
    return {};
}

Collision PhysicManager::Collide(SphereCollider* pSphere1, SphereCollider* pSphere2)
{
    Collision result;

    const Vector3 distance= pSphere1->GetWorldTransform().GetPosition() - pSphere2->GetWorldTransform().GetPosition();

    if (distance.LengthSq() < pSphere1->GetRadius() * pSphere1->GetRadius() + pSphere2->GetRadius() * pSphere1->GetRadius())
    {
        result.Collided = true;
        result.OverlapLength = distance.Length();
        result.OverlapDir = distance / result.OverlapLength;
    }
    
    return result;
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
                mBoxColliders[b2]->OnCollide(coll, mBoxColliders[b1]);
            }
        }

        for (size_t s1 = 0; s1 < mSphereColliders.size(); s1++)
        {
            if (const Collision coll = Collide(mBoxColliders[b1], mSphereColliders[s1]))
            {
                mBoxColliders[b1]->OnCollide(coll, mSphereColliders[s1]);
                mSphereColliders[s1]->OnCollide(coll, mBoxColliders[b1]);
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
                mSphereColliders[s2]->OnCollide(coll, mSphereColliders[s1]);
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