#include "SphereCollider.h"
#include "AssetManager.h"

SphereCollider::SphereCollider(GameActor* pOwner, const Transform& pTransform, const float pRadius, const short pUpdateOrder) :
    ColliderComponent(pOwner, pTransform, pUpdateOrder),
    mRadius(pRadius)
{
#ifdef _DEBUG
    mMesh = AssetManager::GetMesh("sphere");    
#endif
}

Vector3 SphereCollider::Collide(SphereCollider* pOther)
{
    Vector3 overlap = Vector3::zero;
    // todo implement collision between obb
    return overlap;
}

#ifdef _DEBUG
void SphereCollider::Draw(const Matrix4Row& pViewProj)
{
    const Matrix4Row worldTransform = Matrix4Row::CreateScale(mRadius) * GetWorldTransform().GetWorldTransformMatrix();
	
    AssetManager::GetShader("Basic")->SetMatrix4Row("uViewProj", pViewProj);
    AssetManager::GetShader("Basic")->SetMatrix4Row("uWorldTransform", worldTransform);

    AssetManager::GetTexture("rock")->SetActive();
	
    mMesh->GetVertexArray()->SetActive();
	
    glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount());
}
#endif
