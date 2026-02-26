#include "BoxCollider.h"

#include <glew.h>

#include "AssetManager.h"
#include "Inputs.h"
#include "Log.h"
#include "PhysicManager.h"

std::vector<Vector3> BoxCollider::GetCorners()
{
    std::vector<Vector3> corners = {
        Vector3( mHalfSize.x,  mHalfSize.y,  mHalfSize.z),
        Vector3(-mHalfSize.x,  mHalfSize.y,  mHalfSize.z),
        Vector3(-mHalfSize.x, -mHalfSize.y,  mHalfSize.z),
        Vector3(-mHalfSize.x, -mHalfSize.y, -mHalfSize.z),
        Vector3(-mHalfSize.x,  mHalfSize.y, -mHalfSize.z),
        Vector3( mHalfSize.x, -mHalfSize.y,  mHalfSize.z),
        Vector3( mHalfSize.x, -mHalfSize.y, -mHalfSize.z),
        Vector3( mHalfSize.x,  mHalfSize.y, -mHalfSize.z)
    };

    for (auto& corner : corners)
    {
        corner = GetWorldTransform().GetWorldTransformMatrix().TransformVector3(corner);
    }

    return corners;
}

BoxCollider::BoxCollider(GameActor* pOwner, const Transform& pTransform, const Vector3& pHalfSize, const short pUpdateOrder) :
    ColliderComponent(pOwner, pTransform, pUpdateOrder),
    mHalfSize(pHalfSize), mRadius(0.0f)
{
    PhysicManager::AddBoxCollider(this);
    
    mRadius = mHalfSize.Length();
#ifdef _DEBUG
    mMesh = AssetManager::GetMesh("cube");    
#endif
}

BoxCollider::~BoxCollider()
{
    PhysicManager::RemoveBoxCollider(this);
}

#ifdef _DEBUG
void BoxCollider::Draw(const Matrix4Row& pViewProj)
{
    const Matrix4Row worldTransform = Matrix4Row::CreateScale(mHalfSize) * GetWorldTransform().GetWorldTransformMatrix();
	
    AssetManager::GetShader("Collider")->SetMatrix4Row("uViewProj", pViewProj);
    AssetManager::GetShader("Collider")->SetMatrix4Row("uWorldTransform", worldTransform);

    const Vector4 color = mCollided ? Vector4(1,0,0,1) : Vector4(0,1,0,1);
    AssetManager::GetShader("Collider")->SetVec4("color", color.x,color.y,color.z,color.w);
    mCollided = false;
	
    mMesh->GetVertexArray()->SetActive();
	
    glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount());
}
#endif
