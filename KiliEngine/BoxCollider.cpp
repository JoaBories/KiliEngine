#include "BoxCollider.h"

#include <glew.h>

#include "AssetManager.h"
#include "Inputs.h"
#include "Log.h"

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
    mRadius = mHalfSize.Length();
#ifdef _DEBUG
    mMesh = AssetManager::GetMesh("cube");    
#endif
}

Vector3 BoxCollider::Collide(BoxCollider* pOther)
{
    Vector3 overlap = Vector3::zero;
    // todo implement collision between obb
    return overlap;
}

#ifdef _DEBUG
void BoxCollider::Draw(const Matrix4Row& pViewProj)
{
    const Matrix4Row worldTransform = Matrix4Row::CreateScale(mHalfSize) * GetWorldTransform().GetWorldTransformMatrix();
	
    AssetManager::GetShader("Basic")->SetMatrix4Row("uViewProj", pViewProj);
    AssetManager::GetShader("Basic")->SetMatrix4Row("uWorldTransform", worldTransform);

    AssetManager::GetTexture("rock")->SetActive();
	
    mMesh->GetVertexArray()->SetActive();
	
    glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount());
}
#endif
