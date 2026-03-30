#include "PhysicManager.h"
#include "Camera.h"
#include "Assets/AssetManager.h"
#include "Tools/GameTime.h"

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

Hit PhysicManager::Collide(Line pLine, SphereCollider* pSphere)
{
    Hit result;

    const Sphere sp = SphereToSphere(pSphere);

    const float distance = Line::LineOnSphere(pLine, sp);
    if (distance >= 0)
    {
        result = { true,
            pLine.Start + pLine.Direction * distance,
            pLine.Direction, distance,
            pSphere->GetOwner(), pSphere
        };
    }

    return result;
}

Hit PhysicManager::Collide(Line pLine, BoxCollider* pBox)
{
    Hit result;

    const Obb obb = BoxToObb(pBox);
    Line line = pLine;

    Quaternion inverse = pBox->GetWorldTransform().GetRotation().Conjugated();

    line.Start = Vector3::Transform(pLine.Start  - obb.Center, inverse);
    line.Direction = Vector3::Transform(pLine.Direction, inverse);
    line.End = pLine.Start + pLine.Direction * pLine.Length;

    const float distance = Line::LineOnAABB(line, obb);
    if (distance >= 0)
    {
        result = { true,
            pLine.Start + pLine.Direction * distance,
            pLine.Direction, distance,
            pBox->GetOwner(), pBox
        };
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

Hit PhysicManager::Linetrace(const Vector3& pStart, const Vector3& pEnd, const GameActor* pSelf, float pDebugTime)
{
    Line lineTrace = Line(pStart, pEnd);

    Hit bestHit;
    bestHit.Distance = MathUtils::INFINITY_POS;

    for (const auto& sphereCollider : mSphereColliders)
    {
        if (sphereCollider->GetOwner() == pSelf) continue;
        if (const Hit hit = Collide(lineTrace, sphereCollider))
        {
            if (hit.Distance < bestHit.Distance) bestHit = hit;
        }
    }

    for (const auto& boxCollider : mBoxColliders)
    {
        if (boxCollider->GetOwner() == pSelf) continue;
        if (const Hit hit = Collide(lineTrace, boxCollider))
        {
            if (hit.Distance < bestHit.Distance) bestHit = hit;
        }
    }

    if (pDebugTime > 0.0f) mLineTraceWraps.push_back({lineTrace, pDebugTime, bestHit.Collided});

    return bestHit;
}

#ifdef _DEBUG

std::vector<PhysicManager::LineTraceWrap> PhysicManager::mLineTraceWraps = {};

void PhysicManager::DrawDebug(const Camera* pCam)
{
    for (auto& lineTrace : mLineTraceWraps)
    {
        if (lineTrace.TimeRemaining <= 0.0f)
        {
            auto it = std::find(mLineTraceWraps.begin(), mLineTraceWraps.end(), lineTrace);
            if (it != mLineTraceWraps.end())
            {
                std::iter_swap(it, mLineTraceWraps.end() - 1);
                mLineTraceWraps.pop_back();
            }
            continue;
        }
        
        Matrix4Row worldTransform = Matrix4Row::CreateScale(0.01f, 0.01f, lineTrace.Trace.Length / 2);

        worldTransform *= Matrix4Row::CreateFromQuaternion(Quaternion::QuaternionFromDirection(lineTrace.Trace.Direction));
        
        worldTransform *= Matrix4Row::CreateTranslation((lineTrace.Trace.End + lineTrace.Trace.Start) * 0.5f);
	
        AssetManager::GetMaterial("Collider")->SetMatrix4Row("uViewProj", pCam->GetViewProjMatrix());
        AssetManager::GetMaterial("Collider")->SetMatrix4Row("uWorldTransform", worldTransform);

        const Vector4 color = lineTrace.Collided ? Vector4(1,0,0,1) : Vector4(0,1,0,1);
        AssetManager::GetMaterial("Collider")->SetVec4("color", color.x,color.y,color.z,color.w);
	
        AssetManager::GetMesh("cube")->GetVertexArray()->SetActive();
	
        glDrawArrays(GL_TRIANGLES, 0, AssetManager::GetMesh("cube")->GetVertexArray()->GetVerticeCount());

        lineTrace.TimeRemaining -= GameTime::DeltaTime;
    }
}

#endif