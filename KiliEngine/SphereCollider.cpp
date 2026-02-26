#include "SphereCollider.h"
#include "AssetManager.h"
#include "PhysicManager.h"

SphereCollider::SphereCollider(GameActor* pOwner, const Transform& pTransform, const float pRadius, const short pUpdateOrder) :
    ColliderComponent(pOwner, pTransform, pUpdateOrder),
    mRadius(pRadius)
{
    PhysicManager::AddSphereCollider(this);
    
#ifdef _DEBUG
    mMesh = AssetManager::GetMesh("sphere");    
#endif
}

SphereCollider::~SphereCollider()
{
    PhysicManager::RemoveSphereCollider(this);
}

#ifdef _DEBUG
void SphereCollider::Draw(const Matrix4Row& pViewProj)
{
    const Matrix4Row worldTransform = Matrix4Row::CreateScale(mRadius) * GetWorldTransform().GetWorldTransformMatrix();
	
    AssetManager::GetShader("Collider")->SetMatrix4Row("uViewProj", pViewProj);
    AssetManager::GetShader("Collider")->SetMatrix4Row("uWorldTransform", worldTransform);

    const Vector4 color = mCollided ? Vector4(1,0,0,1) : Vector4(0,1,0,1);
    AssetManager::GetShader("Collider")->SetVec4("color", color.x,color.y,color.z,color.w);
    mCollided = false;

    mMesh->GetVertexArray()->SetActive();
	
    glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount());
}
#endif
